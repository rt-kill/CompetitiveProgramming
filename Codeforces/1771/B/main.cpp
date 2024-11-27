#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll n, m;
vector<ll> min_v;
vector<ll> dp;

void solve() {
    min_v.clear(), dp.clear();

    cin >> n >> m;
    min_v.resize(n+1), dp.resize(n+1);
    fill(min_v.begin(), min_v.end(), n);

    ll x, y;
    for(int i=0; i<m; i++) {
        cin >> x >> y;
        if (x > y) swap(x, y);

        min_v[x] = min(min_v[x], y-1);
    }

    dp[n] = n;
    for (int i=n-1; i > 0; i--)
        dp[i] = min(dp[i+1], min_v[i]);

    ll res = 0;
    for (int i=1; i<=n; i++) {
        res += dp[i] - i + 1;
    }
    cout << res << '\n';
}

int main() {
    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
