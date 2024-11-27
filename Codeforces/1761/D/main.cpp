#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int M = 1e9 + 7;
int n, k;



void solve() {
    cin >> n >> k;

    // dp[n][k][0] = number of (a,b) with length n for which [ g(a) + g(b) - g(a+b) = k ]
    // dp[n][k][1] = number of (a,b) with length n for which [ g(a::1) + g(b::1) - g(a::1+b::1) = k ]

    // dp[n][k][0] = 3*dp[n-1][ k ][0] + dp[n-1][ k ][1]
    // dp[n][k][1] = 3*dp[n-1][k-1][1] + dp[n-1][k-1][0]

    // dp[n][k][0] = sum of weights of strings with n chars and k ones
    //  w(s) := 3^t for t number of adjacent equal chars
    //

}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
