#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, q;
vector<ll> x;

vector<ll> ft;

void update_query(int k, int u) {
    ll diff = u - x[k];
    for(int i = k; i <= n; i += (i & -i))
        ft[i] += diff;
    x[k] = u;
}

ll aux_sum_query(int a) {
    ll res = 0;
    for (int i = a; i > 0; i -= (i & -i))
        res += ft[i];
    return res;
}

ll sum_query(int a, int b) {
    ll res = aux_sum_query(b) - aux_sum_query(a-1);
    return res;
}

void init_ft() {
    x = vector<ll>(n+1, 0);
    ft = vector<ll>(n+1, 0);

    ll tmp;
    for(int i=1; i<=n; i++) {
        cin >> tmp;
        update_query(i, tmp);
    }
}

void solve() {
    cin >> n >> q;
    init_ft();

    int t, f, s;
    while(q--) {
        cin >> t >> f >> s;
        switch(t) {
            case 1:
                update_query(f, s);
                break;
            case 2:
                cout << sum_query(f, s) << '\n';
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
