#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n;
vector<int> x, pfx;
vector<pair<int, int>> ps;

void solve() {
    cin >> n;
    x.resize(n);
    for(int i=0; i<n; ++i) cin >> x[i];

    for_each(x.begin(), x.end(), [](auto &v){ v = (v < 0) ? (v%n)+n : v%n; });

    pfx.resize(n+1);
    for(int i=1; i<=n; ++i)
        pfx[i] = (pfx[i-1] + x[i-1]) % n;

    map<int, int> counts;
    ll res = 0;
    for(int i=n-1; i>=0; --i) {
        ++counts[pfx[i+1]];

        int req = (n + pfx[i])%n;

        /* cout << pfx[i+1] << '\n'; */
        /* cout << pfx[i] << '\n'; */

        /* cout << i+1 << ' ' << counts[req] << '\n'; */
        res += counts[req];
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
