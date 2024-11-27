#include <bits/stdc++.h>
using namespace std;

int n, k;

// dp[i][j] = number of ways to reach i in j moves

// dp[i][0] = 0 for all i
// dp[i][j] = 0 for all i < k, and all j
// dp[i][j] = dp[i - (k + j - 1)][j] + dp[i - (k + j - 1)][j-1]

int MM = 998244353;
int dp[int(2e5) + 9][2] = {};
int res[int(2e5) + 9] = {};

int main() {
    cin >> n >> k;

    dp[0][1] = 1;
    for (int m = 1; m < 635; m++) {
        for (int i = 0; i < min(n + 1, (k + m - 1)); i++) {
            dp[i][0] = dp[i][1]; dp[i][1] = 0;
        }
        for (int i = (k + m - 1); i <= n; i++) {
            // dp[i - *][0] = dp[...][m-1], ...
            dp[i][0] = dp[i][1];
            dp[i][1] = (dp[i - (k + m - 1)][0] + dp[i - (k + m - 1)][1]) % MM;

            res[i] = (res[i] + dp[i][1]) % MM;
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << res[i] << ' ';
    }
    cout << '\n';

    return 0;
}

// map<int, int> dp[int(2e5) + 1];
// auto my_lambda = [](const int previous, const auto& element) {
//     return (previous + element.second) % MM;
// };
//
// int main() {
//     cin >> n >> k;
//
//     int MAXM = ceil(sqrt(2*n)) + 5;
//
//     dp[0][0] = 1;
//
//     for (int m = 1; m < MAXM; m++)
//         for (int i = (k + m - 1); i <= n; i++) {
//             dp[i][m] = 0;
//             if (dp[i - (k + m - 1)].count(m))
//                 dp[i][m] = (dp[i][m] + dp[i - (k + m - 1)][m]) % MM;
//             if (dp[i - (k + m - 1)].count(m-1))
//                 dp[i][m] = (dp[i][m] + dp[i - (k + m - 1)][m-1]) % MM;
//         }
//
//     for (int i = 1; i <= n; i++) {
//         int res = accumulate(begin(dp[i]), end(dp[i]), 0, my_lambda);
//         cout << res << ' ';
//     }
//     cout << '\n';
//
//     return 0;
// }
