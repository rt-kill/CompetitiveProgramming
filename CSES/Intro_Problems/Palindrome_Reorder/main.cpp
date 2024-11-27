#include <bits/stdc++.h>
using namespace std;

using ll = long long;

string s;
vector<int> cc('Z' - 'A' + 1);

void solve() {
    cin >> s;
    for(auto c : s) ++cc[c - 'A'];
    int oc = transform_reduce(cc.begin(), cc.end(), 0l, plus{}, [](auto v){ return v&1; });

    if (oc > 1) cout << "NO SOLUTION" << '\n';
    else {
        deque<char> res;
        for(int i=0; i<cc.size(); ++i) {
            int c = cc[i];
            if (c&1) res.push_back(i + 'A');
        }

        for(int i=0; i<cc.size(); ++i)
            for(int j=cc[i]; j>=2; j-=2)
                res.push_front(i + 'A'), res.push_back(i + 'A');

        for(auto c : res) cout << c;
        cout << '\n';
    }
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
