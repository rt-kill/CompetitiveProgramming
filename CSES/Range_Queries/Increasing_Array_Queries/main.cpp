#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, q;
vector<ll> x;
vector<ll> pfx;

vector<vector<pair<int, int>>> queries;
vector<ll> res;


vector<ll> store;
vector<ll> seg;

void update(int k, ll u) {
    store[k] += u;
    for(int i=k; i<=n; i+=(i&-i))
        seg[i] += u;
}

ll aux_query(int a) {
    ll res = 0;
    for(int i=a; i>0; i-=(i&-i))
        res += seg[i];
    return res;
}

ll query(int a, int b) {
    ll res = aux_query(b) - aux_query(a-1);
    return res;
}


void solve() {
    cin >> n >> q;

    x.resize(n+1);
    for(int i=1; i<=n; i++)
        cin >> x[i];

    pfx.resize(n+1);
    for(int i=1; i<=n; i++)
        pfx[i] = pfx[i-1] + ll(x[i]);

    queries.resize(n+1);
    res.resize(q);

    int a, b;
    for(int i=0; i<q; i++) {
        cin >> a >> b;
        queries[a].push_back({ b, i });
    }

    store.resize(n+1), seg.resize(n+1);
    deque<array<int, 3>> stak;
    stak.push_front({ INT_MAX, -1, n+1 });

    for(int a=n; a>0; a--) {
        int v = x[a], c=0;
        while(v >= stak.front()[0]) {
            auto [ tv, tc, ti ] = stak.front();
            c += tc + 1;
            update(ti, -store[ti]);
            stak.pop_front();
        }

        update(a, v*ll(c+1));
        stak.push_front({ v, c, a });

        for(auto [ b, i ] : queries[a]) {
            ll tsum = query(a, b);

            auto [ fv, fc, fi ] = * lower_bound(stak.rbegin(), stak.rend(), b,
                [](auto l, auto r) { return l[2] > r; }
            );
            auto [ sv, sc, si ] = * lower_bound(stak.begin(), stak.end(), b+1,
                [](auto l, auto r) { return l[2] < r; }
            );

            // b will appear in the interval [fi, si)
            // tsum includes [b+1, si)
            ll osum = fv * ll(si - (b + 1));

            ll sum = tsum - osum;

            ll pre_sum = pfx[b] - pfx[a-1];

            res[i] = sum - pre_sum;
        }
    }

    for(auto v : res)
        cout << v << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
