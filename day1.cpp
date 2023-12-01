#include <bits/stdc++.h>

using namespace std;


int main() {
	string spelling[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

	long long ans = 0;
	int n;
	cin >>n;
	string s;

	for(int i=0; i<n; i++) {
		cin >> s;
		int temp = 0;
		
		int front = INT_MAX, back = INT_MIN;
		int f = -1, b = -1;

		for(int j=0; j<10; j++) {
			int fp = s.find(spelling[j]);
			int bp = s.rfind(spelling[j]);

			if(fp != string::npos) {
				if(front > fp) {
					front = fp;
					f = j;
				}
			}
			if(bp != string::npos) {
				if(back < bp) {
					back = bp;
					b = j;
				}
			}
		}

		int j = -1;
		for(j=0; j<s.length(); j++) {
			if(s[j] >= '0' && s[j] <= '9'){
				break;
			}
		}

		if(j < front && j != -1)
			temp += (s[j] - '0') * 10;
		else
			temp += f * 10;

		for(j=s.length()-1; j>=-1; j--) {
			if(j == -1)
				break;
			if(s[j] >= '0' && s[j] <= '9'){
				break;
			}
		}
	
		if(j > back && j != -1)
			temp += (s[j] - '0');
		else
			temp += b;

		ans += temp;
	}

	cout << ans << endl;
}