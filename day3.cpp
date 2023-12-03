#include <bits/stdc++.h>

using namespace std;

bool isChar(char c) {
	return ((c < '0' || c > '9' ) && c != '.');
}

bool isWithinBounds(int x, int y, int rows, int cols) {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

int isValid(vector<string> &mat, int x, int y) {
    int rows = mat.size();
    int cols = mat[0].length();

    if (!isWithinBounds(x, y, rows, cols)) {
        return 0;
    }

    for (int i = x - 1; i <= x + 1; ++i) {
        for (int j = y - 1; j <= y + 1; ++j) {
            if (i == x && j == y) continue;

            if (isWithinBounds(i, j, rows, cols)) {
            	if(mat[i][j] == '*')
            		return 2;
                if (isChar(mat[i][j])) {
                    return 1;
                }
            }
        }
    }

    return 0;
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
	cout << endl;

	for(int i=0; i<n; i++) {
		int prev = -1;
		string temp = "";

		for(int j=0; j < mat[i].size(); j++){

			if(mat[i][j] >= '0' && mat[i][j] <= '9') {
				if(prev == -1)
					prev = j;

				if(isValid(mat, i, j)) {

					for(int k = prev; k<mat[i].length(); k++) {
						if(mat[i][k] >= '0' && mat[i][k] <= '9'){
							temp += mat[i][k];
						}
						else {
							prev = -1;
							j = k;
							break;
						}
					}

					// cout << temp << " ";
					ans += stoi(temp);
					temp = "";
				}
			}
			else {
				prev = -1;
			}
		}
		// cout << endl;
	}

	cout << ans << endl;
}