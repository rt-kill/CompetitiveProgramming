#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, q;
vector<int> x;

// l[0] is the number of iota updates, l[1] is the number to add;
vector<array<ll, 2>> lazy;
vector<ll> seg, leaves;

void seg_init() {
    lazy.resize(2*n), seg.resize(2*n), leaves.resize(2*n);

    for(int i=0; i<n; ++i) {
        seg[i+n] = x[i];
        leaves[i+n] = 1;
    }
    for(int k=n-1; k>0; --k) {
        seg[k] = seg[2*k] + seg[2*k+1];
        leaves[k] = leaves[2*k] + leaves[2*k+1];
    }
}

ll get_value(int k) {
    auto [ ic, sc ] = lazy[k];
    ll vpi = (leaves[k] * (leaves[k] + 1))/2;
    return seg[k] + ic * vpi + leaves[k] * sc;
}

void update_lazy(ll ic, ll sc, int k) {
    auto [ lic, lsc ] = lazy[k];
    lazy[k] = { lic + ic, lsc + sc };
}

void propagate_lazy(int k) {
    if (k < n) {
        auto [ ic, sc ] = lazy[k];
        ll rsc = sc + ic*(leaves[k]/2);

        update_lazy(ic, sc, 2*k);
        update_lazy(ic, rsc, 2*k+1);
    }

    seg[k] = get_value(k);
    lazy[k] = { 0, 0 };
}

void update(int a, int b, int l=0, int r=n-1, int k=1) {
    propagate_lazy(k);

    if (r < a || b < l) return;
    if (a <= l && r <= b) {
        ll sc = (l - a);
        update_lazy(1, sc, k);
        return;
    }

    int m = (l + r)/2;
    update(a, b, l, m, 2*k);
    update(a, b, m+1, r, 2*k+1);

    seg[k] = get_value(2*k) + get_value(2*k+1);
}

ll query(int a, int b, int l=0, int r=n-1, int k=1) {
    propagate_lazy(k);

    if (r < a || b < l) return 0;
    if (a <= l && r <= b) return seg[k];

    int m = (l + r)/2;
    ll ql = query(a, b, l, m, 2*k);
    ll qr = query(a, b, m+1, r, 2*k+1);
    return ql + qr;
}

void print_seg() {
    cout << '\n';
    cout << "SEGGG" << '\n';
    for(int k=1; k<2*n;) {
        do {
            cout << seg[k] << ' ';
            ++k;
        } while (k != (k&-k) );

        cout << '\n';
    }
    cout << '\n';
}

void print_lazy() {
    cout << '\n';
    cout << "LAZYYY" << '\n';
    for(int k=1; k<2*n;) {
        do {
            cout << "(" << lazy[k][0] << ", " << lazy[k][1] << ")" << ' ';
            ++k;
        } while (k != (k&-k) );

        cout << '\n';
    }
    cout << '\n';
}


void solve() {
    cin >> n >> q;

    int tn = n;
    while (tn > (tn & -tn)) tn += (tn & -tn);
    swap(n, tn);

    x.resize(n);
    for(int i=0; i<tn; ++i)
        cin >> x[i];

    seg_init();
    /* print_seg(); */
    /* print_lazy(); */

    while(q--) {
        int t, a, b;
        cin >> t >> a >> b;
        --a, --b;

        if (t == 1) {
            update(a, b);
            /* print_seg(); */
            /* print_lazy(); */
        }
        if (t == 2) cout << query(a, b) << '\n';
    }
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
