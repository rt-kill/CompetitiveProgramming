#include <bits/stdc++.h>
using namespace std;

using ll = long long;
ll const M = 1e9 + 7;

int n, t;
vector<int> qs;


ll dp[(int) 1e6+1];
ll pfx[(int) 1e6+1];

void solve() {
    cin >> t;
    for(int i=0; i<t; ++i) {
        cin >> n;
        qs.push_back(n);
    }

    int mv = *max_element(qs.begin(), qs.end());
    dp[0] = 1, dp[1] = 2, pfx[0] = 1, pfx[1] = 3;
    for(int i=2; i<=mv; ++i) {
        ll res = (5ll*dp[i-1] - 2ll*pfx[i-2]) % M;
        res += (res < 0) ? M : 0;
        dp[i] = res;
        pfx[i] = (pfx[i-1] + res) % M;
    }

    for(auto q : qs)
        cout << dp[q] << '\n';
}

int main() {
    solve();

    return 0;
}
