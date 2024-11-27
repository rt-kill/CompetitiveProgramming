#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, q;
vector<int> x;
vector<int> diffs;

vector<ll> bit;

void update_query(int k, ll u) {
    for(int i=k; i<=n; i += (i & -i))
        bit[i] += u;
}

ll sum_query(int a) {
    ll res = 0;
    for(int i=a; i>0; i-=(i&-i))
        res += bit[i];
    return res;
}

void init_bit() {
    bit = vector<ll>(n+1, 0);
    for(int i=1; i<=n; i++)
        update_query(i, diffs[i]);
}

void solve() {
    cin >> n >> q;

    x.resize(n+1), diffs.resize(n+1);

    x[0] = 0, diffs[0] = 0;
    for(int i=1; i<=n; ++i) {
        cin >> x[i];
        diffs[i] = x[i] - x[i-1];
    }

    init_bit();

    while(q--) {
        int t; cin >> t;
        switch(t) {
            case 1:
                int a, b, u; cin >> a >> b >> u;
                update_query(a, u);
                update_query(b + 1, -u);
                break;
            case 2:
                int k; cin >> k;
                cout << sum_query(k) << '\n';
                break;
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
