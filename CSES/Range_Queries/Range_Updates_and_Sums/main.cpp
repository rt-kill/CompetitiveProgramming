#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, q;
vector<ll> x;


// lazy [ 1, a ] means increase every leaf by a
// lazy [ 2, a ] means set evey leaf to have value a
vector<array<ll, 2>> lazy;
vector<ll> seg, leaves;

void init_seg() {
    seg.resize(2*n), leaves.resize(2*n), lazy.resize(2*n);

    for(int i=0; i<n; i++) seg[n+i] = x[i];
    for(int i=n-1; i>0; i--) seg[i] = seg[2*i] + seg[2*i + 1];

    for(int i=1, l=0; i<2*n; i++, l += (i == (i & -i)))
        leaves[i] = n>>l;
}


ll get_value(int k) {
    auto [ t, c ] = lazy[k];
    ll value = leaves[k] * c;
    if (t <= 1) value += seg[k];
    return value;
}

pair<ll, ll> combine_lazy(ll t1, ll c1, ll t2, ll c2) {
    if (t1 == 0) return { t2, c2 }; // note this case is actually not nessesary, but adds clarity
    else if (t2 == 0) return { t1, c1 };
    else if (t2 == 1) return { max(t1, t2), c1 + c2 };
    else if (t2 == 2) return { t2, c2 };
    return { -1, -1 };
}

void update_lazy(ll t, ll c, int k) {
    auto [ lt, lc ] = lazy[k];
    auto [ nt, nc ] = combine_lazy(lt, lc, t, c);
    lazy[k] = { nt, nc };
}

void prop_lazy(int k) {
    if (k < n) {
        auto [ lt, lc ] = lazy[k];
        update_lazy(lt, lc, 2*k), update_lazy(lt, lc, 2*k+1);
    }

    seg[k] = get_value(k);
    lazy[k] = { 0, 0 };
}


ll query(int a, int b, int l=0, int r=n-1, int k=1) {
    prop_lazy(k);

    if (b < l || r < a) return 0;
    if (a <= l && r <= b) return seg[k];

    int m = (l + r)/2;
    ll ql = query(a, b, l, m, 2*k);
    ll qr = query(a, b, m+1, r, 2*k+1);
    return ql + qr;
}

void update(ll t, ll c, int a, int b, int l=0, int r=n-1, int k=1) {
    prop_lazy(k);

    if (b < l || r < a) return;

    if (a <= l && r <= b) {
        update_lazy(t, c, k);
        return;
    }

    int m = (l + r)/2;
    update(t, c, a, b, l, m, 2*k);
    update(t, c, a, b, m+1, r, 2*k+1);

    seg[k] = get_value(2*k) + get_value(2*k+1);
    lazy[k] = { 0, 0 };
}

void solve() {
    cin >> n >> q;

    int tmp = n;
    while(tmp > (tmp & -tmp)) tmp += (tmp & -tmp);
    swap(tmp, n);

    x.resize(n);
    for(int i=0; i<tmp; i++)
        cin >> x[i];

    init_seg();

    while(q--) {
        int t, a, b; cin >> t >> a >> b; a--, b--;

        if (t < 3) {
            int c; cin >> c;
            update(t, c, a, b);
        } else {
            ll res = query(a, b);
            cout << res << '\n';
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
