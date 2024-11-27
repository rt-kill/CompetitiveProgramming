#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, q;
int forest[1024][1024] = {};
int loc_map[1024][1024] = {};
int seg[2000000] = {};

void pop_loc_map(int r=0, int c=0, int d=n, int k=0) {
    if (d == 1) loc_map[r][c] = k;
    else {
        pop_loc_map(r, c, d/2, 4*k+1);
        pop_loc_map(r+d/2, c, d/2, 4*k+2);
        pop_loc_map(r, c+d/2, d/2, 4*k+3);
        pop_loc_map(r+d/2, c+d/2, d/2, 4*k+4);
    }
}

void update(int r, int c) {
    int diff = (forest[r][c]) ? -1 : 1;

    forest[r][c] += diff;
    for(int i=loc_map[r][c]; i>0; i = (i - 1)/4)
        seg[i] += diff;
    seg[0] += diff;
}


int query(int r1, int c1, int r2, int c2, int or1=0, int oc1=0, int or2=n-1, int oc2=n-1, int k=0) {
    if ( (or2 < r1 || r2 < or1) || (oc2 < c1 || c2 < oc1) ) return 0;
    if ( (r1 <= or1 && or2 <= r2) && (c1 <= oc1 && oc2 <= c2) ) return seg[k];

    int omr = (or1 + or2)/2, omc = (oc1 + oc2)/2;
    int q1 = query(r1, c1, r2, c2, or1, oc1, omr, omc, 4*k+1);
    int q2 = query(r1, c1, r2, c2, omr+1, oc1, or2, omc, 4*k+2);
    int q3 = query(r1, c1, r2, c2, or1, omc+1, omr, oc2, 4*k+3);
    int q4 = query(r1, c1, r2, c2, omr+1, omc+1, or2, oc2, 4*k+4);

    return q1 + q2 + q3 + q4;
}


void solve() {
    cin >> n >> q;

    int t=n;
    while(t>(t&-t)) t+=(t&-t);
    swap(t, n);

    pop_loc_map();

    char tmp;
    for(int r=0; r<t; r++) {
        for (int c=0; c<t; c++) {
            cin >> tmp;
            if (tmp == '*') update(r, c);
        }
    }

    while(q--) {
        int t; cin >> t;
        if (t == 1) {
            int r, c; cin >> r >> c;
            r--, c--;
            update(r, c);
        } else {
            int r1, c1, r2, c2; cin >> r1 >> c1 >> r2 >> c2;
            r1--, c1--, r2--, c2--;
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
