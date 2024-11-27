#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, q;
int forest[1001][1001] = {};
int bit[1001][1001] = {};

void update(int r, int c) {
    int diff = (forest[r][c]) ? -1 : 1;
    forest[r][c] += diff;

    for(int i=r; i<=n; i+=(i&-i))
        for(int j=c; j<=n; j+=(j&-j))
            bit[i][j] += diff;
}

int aux_query(int r, int c) {
    int res = 0;
    for(int i=r; i>0; i-=(i&-i))
        for(int j=c; j>0; j-=(j&-j))
            res += bit[i][j];

    return res;
}

int query(int r1, int c1, int r2, int c2) {
    int res = aux_query(r2, c2) + aux_query(r1-1, c1-1) - aux_query(r1-1, c2) - aux_query(r2, c1-1);
    return res;
}


void solve() {
    cin >> n >> q;

    char tmp;
    for(int r=1; r<=n; r++) {
        for (int c=1; c<=n; c++) {
            cin >> tmp;
            if (tmp == '*') update(r, c);
        }
    }

    while(q--) {
        int t; cin >> t;
        if (t == 1) {
            int r, c; cin >> r >> c;
            update(r, c);
        } else {
            int r1, c1, r2, c2; cin >> r1 >> c1 >> r2 >> c2;
            if (r1 > r2) swap(r1, r2);
            if (c1 > c2) swap(c1, c2);

            int res = query(r1, c1, r2, c2);
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
