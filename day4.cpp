#include <bits/stdc++.h>

using namespace std;

vector<string> split(string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

vector<int> splitInt(string s) {

	stringstream ss(s);
    vector<int> numbers;

    for(int i = 0; ss >> i; ) {
        numbers.push_back(i);
    }

    return numbers;
}



int main() {

	int n = 220, ans = 0, ans2 = 0;
	string s;
	string ss[n];
	vector<int> copies(n, 1);
	vector<int> pointsList(n, 0);

	for(int i=0; i<n; i++) {
		getline(std::cin, ss[i]);
	}

	for(int i=0; i<n; i++) {
		s = ss[i];
		int x = 0;

		for(x=0; x < s.length(); x++) {
			if(s[x] == ':') {
				x += 2;	
				break;
			}
		}
		s = s.substr(x);

		vector<string> sets = split(s, " | ");


		vector<int> winner = splitInt(sets[0]);
		vector<int> numbers = splitInt(sets[1]);

		int points = 0, c = 0;
		for(int num: numbers) {
			if(find(winner.begin(), winner.end(), num) != winner.end()) {
				c++;
				if(points == 0)
					points += 1;
				else
					points *= 2;
			}
		}
		for(int j=1; j<=c; j++) {
			if(i + j < n) {
				copies[i + j] += copies[i];
			}
		}
		pointsList[i] = points;
		ans += points;
	}

	for(int i=0; i<n; i++) {
		ans2 += copies[i];
	}

	cout << ans2 << endl;
}