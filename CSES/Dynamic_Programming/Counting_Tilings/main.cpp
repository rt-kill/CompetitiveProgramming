#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int const MM = 1e9+7;

int n, m, mm;

// check if a given permutation only has ones that are adjacent to each other
bool aux_memory[1024] = {};
bool aux_dp(int mask) {
    while (mask > 0) {
        if ((mask&1) && !(mask&2)) return 0;
        mask >>= 1 + (mask&1);
    }

    return true;
}

ll memory[1024][1000];
ll dp(int mask, int col) {
    if (col == m) return (mask == 0);

    if (memory[mask][col] == -1) {
        int next_mask = (~mask & (mm-1));
        ll res = 0;

        for (int i=0; i<mm; i++) {
            if (i & mask) continue;
            if (!aux_dp(i)) continue;
            res = (res + dp(i ^ next_mask, col+1)) % MM;
        }

        memory[mask][col] = res;
    }

    return memory[mask][col];
}

void solve() {
    cin >> n >> m;
    mm = 1<<n;
    for(int mask=0; mask<mm; mask++)
        fill(memory[mask], memory[mask]+m, -1);

    ll res = dp(0, 0);
    cout << res << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
