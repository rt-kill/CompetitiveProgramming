#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n;
vector<array<int, 3>> p;

void solve() {
    cin >> n;

    p.resize(n);
    for(int i=0; i<n; ++i)
        cin >> p[i][0] >> p[i][1] >> p[i][2];

    sort(p.begin(), p.end());

    vector<ll> dp(n+1);
    dp[n] = 0;

    for(int i=n-1; i>=0; --i) {
        auto [ sd, ed, v ] = p[i];
        int ni = upper_bound(p.begin(), p.end(), array<int, 3>({ed+1, -1, -1})) - p.begin();
        dp[i] = max(v + dp[ni], dp[i+1]);
    }

    cout << dp[0] << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
