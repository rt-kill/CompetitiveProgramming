#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, q;
vector<int> x;

// We will assume n is a power of 2

// Suppose we have a segment tree where each node stores the max prefix, the sum, and the max suffix sum
// We have the following recurence for our query on [a, b]
//  res[a, b] = max(
//      sum(a, n) + res[n, b],
//      res[a, n]
//  )



// sum, max_prefix pairs
vector<pair<ll, ll>> seg;

void init_seg() {
    seg = vector<pair<ll, ll>>(2*n, {0, 0});
}

pair<ll, ll> query(int a, int b, int l=0, int r=n-1, int v=1) {
    if (r < a || b < l) return {0, 0};
    if (a <= l && r <= b) return seg[v];

    int m = (l+r)/2;
    pair<ll, ll> lh = query(a, b, l, m, v*2);
    pair<ll, ll> rh = query(a, b, m+1, r, v*2+1);

    return { lh.first + rh.first, max(lh.first + rh.second, lh.second) };
}

void update(int k, int u) {
    // positive prefix's are always used in values of right parents
    // negative prefix's are never used in values of right parents (prefix goes to 0)

    k += n;
    seg[k] = { u, max(u, 0) };

    for (int i = k>>1; i>0; i>>=1) {
        pair<ll, ll> lh = seg[2*i];
        pair<ll, ll> rh = seg[2*i + 1];
        pair<ll, ll> np = { lh.first + rh.first, max(lh.first + rh.second, lh.second) };
        seg[i] = np;
    }
}



void solve() {
    cin >> n >> q;

    int tmp = n;
    while(tmp > (tmp & -tmp)) tmp += (tmp & -tmp);
    x = vector<int>(tmp, 0);

    for (int i=0; i<n; i++)
        cin >> x[i];

    n = tmp;
    init_seg();
    for(int i=0; i<n; i++)
        if (x[i] != 0)
            update(i, x[i]);

    int t, f, s;
    while (q--) {
        cin >> t >> f >> s;
        switch(t) {
            case 1: {
                update(--f, s);
                break;
            }

            case 2: {
                auto [ _, res ] = query(--f, --s);
                cout << res << '\n';
                break;
            }
        }
    }
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
