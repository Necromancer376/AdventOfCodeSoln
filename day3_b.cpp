#include <bits/stdc++.h>

using namespace std;


bool isWithinBounds(int x, int y, int rows, int cols) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

vector<int> getGear(vector<string> &mat, int x, int y) {
	vector<int> gears;
    int rows = mat.size();
    int cols = mat[0].length();

    if (!isWithinBounds(x, y, rows, cols)) {
        return gears;
    }

    for (int i = x - 1; i <= x + 1; ++i) {
        for (int j = y - 1; j <= y + 1; ++j) {
            if (i == x && j == y) continue;

            if (isWithinBounds(i, j, rows, cols)) {
                if(mat[i][j] >= '0' && mat[i][j] <= '9') {
                	string num = "";
                	int p = j, q = j;
                	while(mat[i][p] >= '0' && mat[i][p] <= '9') {
                		p--;
                	}
                	while(mat[i][q] >= '0' && mat[i][q] <= '9') {
                		q++;
                	}
                	p++;
                	q--;
                	for(int k = p; k<=q; k++){
                		num += mat[i][k];
                	}
                	gears.push_back(stoi(num));
                }
            }
        }
    }

    return gears;
}


int main() {
	int n, ans = 0;
	cin >> n;
	vector<string> mat;

	for(int i=0; i<n; i++) {
		string s;
		cin >> s;
		mat.push_back(s);
	}

	for(int i=0; i<n; i++) {
		for(int j=0; j<mat[i].length(); j++){
			if(mat[i][j] == '*') {
				vector<int> gears = getGear(mat, i, j);
				gears.erase( unique( gears.begin(), gears.end() ), gears.end());

				if(gears.size() == 1){
					for(auto x: gears)
						cout << x << " ";
					cout << endl;
				}

				if(gears.size() == 2) {
					ans += gears[0] * gears[1];
				}
			}
		}
	}

	cout << ans << endl;
}