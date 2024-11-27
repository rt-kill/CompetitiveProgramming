#include <bits/stdc++.h>
using namespace std;

using l = long;

const int MAXR = 998244353;

int N, D[int(3e5) + 9];
l M;
l sums[int(3e5) + 9] = {};

int bs(int data) {
    auto it = lower_bound(sums + 1, sums + 1 + N, data);
    if (it == sums + 1 + N || *it != data) {
        return -1;
    } else {
        size_t index = distance(sums + 1, it);
        return index;
    }
}

int main() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        cin >> D[i];
        sums[i+1] = 4*l(D[i]) + sums[i];
    }

    l circ = sums[N + 1]/4;

    vector<int> parts;

    int ddist; set<int> seen;
    for (int cur = 1; cur <= N; cur++) {
        /* cout << cur << ' ' << sums[cur] << '\n'; */
        if (seen.count(cur)) continue;

        int count = 0;
        for (int m = 0; m < 4; m++) {
            ddist = (sums[cur] + m*circ) % (4*circ);

            int i = bs(ddist);
            /* cout << "CURT: "<< cur << ' ' << ddist << ' ' << i << '\n'; */
            if (i != -1) {
                count += 1;
                seen.insert(i + 1);
            }
        }

        parts.push_back(count);
    }

    l res = 1;
    for (int part : parts) {
        cout << part << '\n';
        if (part < 3) {
            res *= part*M;
        } else if (part == 3) {
            // (3 choose 2) * (k * (k-1)) + k * k-1 * k-2
            res *= 3*M*(M-1) + M*(M-1)*(M-2);
        } else {
            // 0 ways where at least 3 nodes have the same color
            // (4 choose 2) * (k * (k-1)) ways where we have 2 colors
            // (4 choose 2)*(2 choose 1) * (k * (k-1) * (k-2)) ways where we have 3 colors
            // k(k-1)(k-2)(k-3) ways where we have 4 colors
            res *= 6*M*(M-1) + 12*M*(M-1)*(M-2) + M*(M-1)*(M-2)*(M-3);
        }

        res %= MAXR;
    }

    cout << res << '\n';

    return 0;
}
