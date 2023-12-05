#include <iostream>
#include <vector>
#include <limits>
#include <cuda_runtime.h>

__device__ long getVal(const long* vec, long x, long size) {
    for (long i = 0; i < size; i += 3) {
        if (x >= vec[i + 1] && x < vec[i + 1] + vec[i + 2]) {
            return vec[i] + (x - vec[i + 1]);
        }
    }
    return x;
}

__global__ void computeKernel(const long* seeds, long n, const long* seed_soil, const long* soil_fert,
                              const long* fert_water, const long* water_light, const long* light_temp,
                              const long* temp_humd, const long* humd_loc, long* result) {
    long tid = blockIdx.x * blockDim.x + threadIdx.x;

    if (tid < n) {
        long ans = LONG_MAX;

        for (long j = 0; j < seeds[tid + 1]; j++) {
            long soil = getVal(seed_soil, seeds[tid] + j, 3 * seed_soil[0]);
            long fert = getVal(soil_fert, soil, 3 * soil_fert[0]);
            long water = getVal(fert_water, fert, 3 * fert_water[0]);
            long light = getVal(water_light, water, 3 * water_light[0]);
            long temp = getVal(light_temp, light, 3 * light_temp[0]);
            long humd = getVal(temp_humd, temp, 3 * temp_humd[0]);
            long loc = getVal(humd_loc, humd, 3 * humd_loc[0]);

            atomicMin(&ans, loc);
        }

        result[tid] = ans;
    }
}

int main() {
    long n;
    std::cin >> n;

    // Allocate and copy data to the device
    long *d_seeds, *d_seed_soil, *d_soil_fert, *d_fert_water, *d_water_light, *d_light_temp, *d_temp_humd, *d_humd_loc, *d_result;
    cudaMalloc((void**)&d_seeds, n * sizeof(long));
    cudaMalloc((void**)&d_seed_soil, 3 * sizeof(long) * seed_soil.size());
    cudaMalloc((void**)&d_soil_fert, 3 * sizeof(long) * soil_fert.size());
    cudaMalloc((void**)&d_fert_water, 3 * sizeof(long) * fert_water.size());
    cudaMalloc((void**)&d_water_light, 3 * sizeof(long) * water_light.size());
    cudaMalloc((void**)&d_light_temp, 3 * sizeof(long) * light_temp.size());
    cudaMalloc((void**)&d_temp_humd, 3 * sizeof(long) * temp_humd.size());
    cudaMalloc((void**)&d_humd_loc, 3 * sizeof(long) * humd_loc.size());
    cudaMalloc((void**)&d_result, n * sizeof(long));

    cudaMemcpy(d_seeds, seeds.data(), n * sizeof(long), cudaMemcpyHostToDevice);
    cudaMemcpy(d_seed_soil, seed_soil.data(), 3 * sizeof(long) * seed_soil.size(), cudaMemcpyHostToDevice);
    cudaMemcpy(d_soil_fert, soil_fert.data(), 3 * sizeof(long) * soil_fert.size(), cudaMemcpyHostToDevice);
    cudaMemcpy(d_fert_water, fert_water.data(), 3 * sizeof(long) * fert_water.size(), cudaMemcpyHostToDevice);
    cudaMemcpy(d_water_light, water_light.data(), 3 * sizeof(long) * water_light.size(), cudaMemcpyHostToDevice);
    cudaMemcpy(d_light_temp, light_temp.data(), 3 * sizeof(long) * light_temp.size(), cudaMemcpyHostToDevice);
    cudaMemcpy(d_temp_humd, temp_humd.data(), 3 * sizeof(long) * temp_humd.size(), cudaMemcpyHostToDevice);
    cudaMemcpy(d_humd_loc, humd_loc.data(), 3 * sizeof(long) * humd_loc.size(), cudaMemcpyHostToDevice);

    // Set up the grid and block dimensions
    int blockSize = 256;
    int gridSize = (n + blockSize - 1) / blockSize;

    // Launch the kernel
    computeKernel<<<gridSize, blockSize>>>(d_seeds, n, d_seed_soil, d_soil_fert, d_fert_water, d_water_light,
                                            d_light_temp, d_temp_humd, d_humd_loc, d_result);

    // Copy the result back to the host
    long* h_result = new long[n];
    cudaMemcpy(h_result, d_result, n * sizeof(long), cudaMemcpyDeviceToHost);

    // Find the minimum value from the results
    long ans = LONG_MAX;
    for (long i = 0; i < n; i++) {
        ans = std::min(ans, h_result[i]);
    }

    // 'ans' now contains the minimum value across all iterations
    std::cout << "Minimum value: " << ans << std::endl;

    // Clean up
    delete[] h_result;
    cudaFree(d_seeds);
    cudaFree(d_seed_soil);
    cudaFree(d_soil_fert);
    cudaFree(d_fert_water);
    cudaFree(d_water_light);
    cudaFree(d_light_temp);
    cudaFree(d_temp_humd);
    cudaFree(d_humd_loc);
    cudaFree(d_result);

    return 0;
}
