#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, m;
vector<ll> x;

// sum, res, maxprefix, maxsuffix
vector<array<ll, 4>> seg;

ll update(int k, int u) {
    ll t = max(u, 0);
    x[k] = u, seg[k+n] = {u, t, t, t};

    for(int i=(k+n)/2; i>0; i/=2) {
        auto lc = seg[2*i], rc = seg[2*i+1];

        seg[i] = {
            lc[0] + rc[0],
            max({ lc[1], rc[1], lc[3] + rc[2] }),
            max({ lc[2], lc[0] + rc[2] }),
            max({ rc[3], rc[0] + lc[3] }),
        };
    }

    return seg[1][1];
}

void solve() {
    cin >> n >> m;

    int t = n;
    while(t > (t & -t)) t += (t & -t);
    swap(n, t);

    x = vector<ll>(n, 0);
    seg = vector<array<ll, 4>>(2*n, {0, 0, 0, 0});

    int tmp;
    for(int i=0; i<t; i++) {
        cin >> tmp;
        update(i, tmp);
    }

    int k, u;
    while(m--) {
        cin >> k >> u;
        ll res = update(k-1, u);
        cout << res << '\n';
    }
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
