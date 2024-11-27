#include <bits/stdc++.h>
using namespace std;

using ll = long long;

string input;
void solve() {
		vector<string> inps;
		while(true) {
				getline(std::cin, input);
				if (input.empty())
						break;
				inps.push_back(input);
		}

		int res1=0;
		for (auto inp : inps) {
				set<int> vals;
				for(int i=0;i<inp.size()/2;i++)
						vals.insert(inp[i]);
				for(int i=inp.size()/2;i<inp.size();i++)
						if (vals.count(inp[i])) {
								if (inp[i] <= 'Z')
										res1 += inp[i] - 'A' + 27;
								else
										res1 += inp[i] - 'a' + 1;
								break;
						}
		}

		int res2=0;
		for (int i=0;i<inps.size();i+=3) {
				set<int> vals1, vals2;
				for(auto c : inps[i])
						vals1.insert(c);
				for(auto c : inps[i+1])
						vals2.insert(c);
				for(auto c : inps[i+2])
						if(vals1.count(c) && vals2.count(c)) {
								if (c <= 'Z') res2 += c - 'A' + 27; else res2 += c - 'a' + 1;
								break;
						}
		}

		cout << res1 << ' ' << res2;
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
