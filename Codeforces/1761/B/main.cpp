#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, a[200];

int dp[200][200];
int DP(int l, int r) {
    if (r - l <= 1) dp[l][r] = 0;
    else if (dp[l][r] == -1) {
        int res = 0; int tmp;

        for(int i=l+1;i<r;i++) {
            DP(l, i), DP(i, r);

            tmp = 0;
            if (a[i] != a[l] && a[i] != a[r]) tmp += 1;

            tmp += dp[l][i] + dp[i][r];
            res = max(res, tmp);
        }

        dp[l][r] = res;
    }

    return dp[l][r];
}

void solve() {
    cin >> n;
    for (int i=0;i<n;i++)
        cin >> a[i];
    for (int i=n;i<2*n;i++)
        a[i] = a[i-n];

    for (int i=0;i<2*n;i++)
        for (int j=0;j<2*n;j++)
            dp[i][j] = -1;

    int res=0;
    for (int i=0;i<n;i++)
        res=max(res,1 + DP(i, i+n)); // remove i last

    cout << res << '\n';

    // if no number is repeated, the solution is n
    // if a single number is repeated once, the solution is n
    // if a single number is repeated x times, the solution is n

    // suppose 1 is repeated once
    //  if 2 is repeated once,
    //      the solution could be 2 [1, 2, 1, 2, ...]
    //      the solution could be 3 [..., 1, 2, 1, 2, 3]
    //      the solution could be k [
}

int main() {
    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
