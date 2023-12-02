#include <bits/stdc++.h>

using namespace std;

vector<string> splitCh(string s, char c) {

	stringstream test(s);
	string segment;
	vector<string> seglist;

	while(getline(test, segment, c))
	{
	   seglist.push_back(segment);
	}

	return seglist;
}

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

int main() {

	int n, ans = 0, ans2 = 0;
	string s;
	cin >> n;

	for(int i=0; i<n; i++) {
		
		getline(std::cin, s);

		int x = 0;

		for(x=0; x < s.length(); x++) {
			if(s[x] == ':') {
				x += 2;
				break;
			}
		}
		s = s.substr(x);

		vector<string> games = split(s, "; ");
		bool flag = true;

		unordered_map<string, int> maxColor;
		maxColor["red"] = 0;
		maxColor["green"] = 0;
		maxColor["blue"] = 0;

		for(string set: games) {
			unordered_map<string, int> colours;
			colours["red"] = 0;
			colours["green"] = 0;
			colours["blue"] = 0;

			vector<string> items  = split(set, ", ");

			for(string item: items) {
				vector<string> cx = splitCh(item, ' ');
				if(!cx.empty()) {
					colours[cx[1]] += stoi(cx[0]);
					maxColor[cx[1]] = max(maxColor[cx[1]], stoi(cx[0]));
				}
			}

// part 1

			// if(colours["red"] > 12 || colours["green"] > 13 || colours["blue"] > 14){
			// 	flag = false;
			// 	break;
			// }
		}

		// if(flag)
		// 	ans += i;

		ans2 += (maxColor["red"] * maxColor["green"] * maxColor["blue"]);
	}
	cout << ans2 << endl;
}