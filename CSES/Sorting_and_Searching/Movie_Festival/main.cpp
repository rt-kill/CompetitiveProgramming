#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n;
vector<pair<int, int>> m;

void solve() {
    cin >> n;
    m.resize(n);
    for(int i=0; i<n; ++i)
        cin >> m[i].first >> m[i].second;

    sort(m.begin(), m.end());

    int me=0, res=0;
    for(auto [ s, e ] : m) {
        if (me <= s)
            me = e, ++res; // watch moveie with ending me
        else
            me = min(me, e); // update candidate movie
    }

    cout << res << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
