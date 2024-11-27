#include <bits/stdc++.h>
using namespace std;

int N, Q;
int L[int(1e5) + 9], R[int(1e5) + 9];
int W;

int dp[int(1e5) + 9] = {}; // Needed memory is much less than this
pair<int, int> S[int(4e5) + 100];

auto my_comp = [](const auto & l, const auto & r) -> bool {
    return (l.first < r.first);
};

int solve_aux(int e) {
    if (dp[e]) return dp[e];

    int m = 2 << e;

    for (int i = 0; i < N; i++) {
        if ((R[i] - L[i] + 1) >= m) {
            S[i] = pair<int, int>(0, 1);
            S[i + N] = pair<int, int>(0, 0);
            S[i + 2*N] = pair<int, int>(0, 0);
            S[i + 3*N] = pair<int, int>(0, 0);
        } else {
            int i1l = L[i] % m;
            int i1r = min(L[i] % m + (R[i] - L[i]) + 1, m);
            int i2l = 0;
            int i2r = ((R[i] % m) < (L[i] % m)) ? (R[i] % m) + 1 : 0;

            S[i] = pair<int, int>(i1l, 1);
            S[i + N] = pair<int, int>(i1r, -1);
            S[i + 2*N] = pair<int, int>(i2l, 1);
            S[i + 3*N] = pair<int, int>(i2r, -1);
        }
    }

    sort(S, S + 4*N, my_comp);

    int cur = 0; int res = 0; int i = 0;
    while (i < 4*N) {
        int tmp = S[i].first;
        while (i < 4*N && tmp == S[i].first)
            cur += S[i++].second;
        res = max(res, cur);
    }

    dp[e] = res;
    return dp[e];
}

int solve() {
    cin >> W;
    int e = 0;
    while ( !(W & 1) ) { e += 1; W /= 2; }
    return solve_aux(e);
}

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> L[i] >> R[i];
        L[i] -= 1; R[i] -= 1;
    }

    for (int e = 0; e < 30; e++)
        solve_aux(e);

    cin >> Q;
    for (int i = 0; i < Q; i++) // O(q) -> pow(10, 5)
        cout << solve() << '\n';
}
