#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, m;
vector<int> h;
vector<int> st;

int search_query(int r) {
    if (st[1] < r) return -1;

    int i=1;
    while (i < n)
        i = i*2 + (st[i*2] < r);

    return (i-n);
}

void update_query(int k, int u) {
    if (k < 0) return;

    h[k] = u, st[k+n] = u;
    for (int i = ((k+n) >> 1); i > 0; i >>= 1)
        st[i] = max(st[2*i], st[2*i + 1]);
}

void init_st() {
    st = vector<int>(2*n);
    for (int i=0; i<n; i++)
        update_query(i, h[i]);
}

void print_tree() {
    for(auto v : st)
        cout << v << ' ';
    cout << '\n';
}

void solve() {
    cin >> n >> m;

    int p2 = n;
    while (p2 > (p2 & -p2)) p2 += (p2 & -p2);

    h = vector<int>(p2, 0);
    for(int i=0; i<n; i++)
        cin >> h[i];
    n = p2;

    init_st();
    /* print_tree(); */

    int r;
    while(m--) {
        cin >> r;
        int i = search_query(r);
        update_query(i, h[i] - r);
        /* print_tree(); */
        cout << (i + 1) << ' ';
    }
    cout << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
