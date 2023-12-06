#include <bits/stdc++.h>

using namespace std;


vector<int> splitInt() {

	string s;
	getline(std::cin, s);
	int x = 0;
	for(x=0; x < s.length(); x++) {
		if(s[x] == ':') {
			x += 2;
			break;
		}
	}
	s = s.substr(x);

	stringstream ss(s);
    vector<int> numbers;

    for(int i = 0; ss >> i; ) {
        numbers.push_back(i);
    }

    return numbers;
}


int main() {
	int ans = 1;
	long t = 0, d = 0;

	vector<int> time = splitInt();
	vector<int> dist = splitInt();
	vector<int> wins;


	string temp = "";
	for(int i: time) {
		temp += to_string(i);
	}
	t = stol(temp);
	temp = "";
	for(int i: dist) {
		temp += to_string(i);
	}
	d = stol(temp);

	int win = 0;
	for(int i=1; i<t; i++) {
		if((i * (t - i)) > d){
			win++;
		}
	}

// part 1 code
	// for(int i=0; i<n; i++) {
	// 	int win = 0;
	// 	for(int j=1; j<time[i]; j++) {
	// 		if((j * (time[i] - j)) > dist[i]){
	// 			win++;
	// 		}
	// 	}
	// 	wins.push_back(win);
	// }

	cout << endl;
	for(int i: wins)
		ans *= i;

	cout << win << endl;
}