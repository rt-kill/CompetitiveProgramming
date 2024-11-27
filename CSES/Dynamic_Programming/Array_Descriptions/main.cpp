#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, m;
vector<int> x;
int const M = 1e9 + 7;

void solve() {
    cin >> n >> m;
    x.resize(n);
    for(int i=0; i<n; ++i)
        cin >> x[i];

    vector<array<ll, 102>> dp;
    dp.resize(n);

    if (x[0] == 0)
        for(int i=1; i<=m; ++i)
            dp[0][i]=1;
    else
        dp[0][x[0]]=1;

    for (int i=1; i<n; ++i) {
        if (x[i] == 0)
            for(int j=1; j<=m; ++j)
                dp[i][j] = (dp[i-1][j-1] + dp[i-1][j] + dp[i-1][j+1]) % M;
        else
            dp[i][x[i]] = (dp[i-1][x[i]-1] + dp[i-1][x[i]] + dp[i-1][x[i]+1]) % M;
    }

    ll res = 0;
    if (x[n-1] == 0)
        for(int j=1; j<=m; ++j)
            res = (res + dp[n-1][j]) % M;
    else
        res = dp[n-1][x[n-1]];

    cout << res << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
