#include <bits/stdc++.h>

using namespace std;


void getMap(vector<vector<long>> &vec) {
	long n;
	cin >> n;
	for(long i=0; i<n; i++){
		long destination, source, range;
		cin >> destination >> source >> range;
		vector<long> mp = {destination, source, range};

		vec.push_back(mp);
	}
}

long getVal(vector<vector<long>> &vec, long x) {

	for(auto mp:vec){
		if(x >= mp[1] && x < mp[1] + mp[2]){
			return mp[0] + (x - mp[1]);
		}
	}

	return x;
}


int main() {
	long n, ans = INT_MAX;
	cin >> n;

	vector<long> seeds(n);
	for(long i=0; i<n; i++) {
		cin >> seeds[i];
	}

	vector<vector<long>> seed_soil;
	vector<vector<long>> soil_fert;
	vector<vector<long>> fert_water;
	vector<vector<long>> water_light;
	vector<vector<long>> light_temp;
	vector<vector<long>> temp_humd;
	vector<vector<long>> humd_loc;

	getMap(seed_soil);
	getMap(soil_fert);
	getMap(fert_water);
	getMap(water_light);
	getMap(light_temp);
	getMap(temp_humd);
	getMap(humd_loc);

	cout << endl;
	// for(long i=0; i<seeds.size(); i+=2) {
	for(long i: seeds) {
		// for(long j=0; j<seeds[i+1]; j++){
			// long soil = getVal(seed_soil, seeds[i]+j);
			long soil = getVal(seed_soil, i);
			long fert =  getVal(soil_fert,soil);
			long water = getVal(fert_water, fert);
			long light = getVal(water_light, water);
			long temp = getVal(light_temp, light);
			long humd = getVal(temp_humd, temp);
			long loc = getVal(humd_loc, humd);

			// printf("%ld %ld %ld %ld %ld %ld %ld %ld %ld\n", i, seeds[i]+j, soil, fert, water, light, temp, humd, loc);

			ans = min(ans, loc);
		// }
	}

	cout << endl << ans << endl;
}