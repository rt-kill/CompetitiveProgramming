#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, q;
vector<int> x;
vector<int> st;

void update_query(int k, int u) {
    st[n + k] = u;
    for (int i = (n + k)/2; i > 0; i /= 2)
        st[i] = min(st[2*i], st[2*i + 1]);
}

int min_query(int a, int b) {
    int res = INT_MAX;

    a += n, b += n;
    while(a <= b) {
        res = (a & 1) ? min(res, st[a++]) : res;
        res = !(b & 1) ? min(res, st[b--]) : res;
        a/=2, b/=2;
    }

    return res;
}

void init_st() {
    st = vector<int>(2*n, 0);
    for (int i=0; i<n; i++)
        update_query(i, x[i]);
}

void solve() {
    cin >> n >> q;

    x.resize(n);
    for(int i=0; i<n; i++)
        cin >> x[i];

    init_st();

    int t, f, s;
    while(q--) {
        cin >> t >> f >> s;
        switch(t) {
            case 1:
                update_query(--f, s);
                break;
            case 2:
                cout << min_query(--f, --s) << '\n';
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
