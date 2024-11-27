#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, q;
int const M = 1e9 + 7;

vector<int> p, lseg, rseg;

void uql(int k, int u) {
    lseg[k+n] = u+k;
    for(int i=(k+n)/2; i>0; i/=2)
        lseg[i] = min(lseg[2*i], lseg[2*i + 1]);
}

int mql(int a, int b) {
    int l=a+n, r=b+n;

    int res = lseg[l];
    while(l <= r) {
        if (l & 1) res = min(res, lseg[l++]);
        if (!(r & 1)) res = min(res, lseg[r--]);
        l/=2, r/=2;
    }

    return res;
}

void uqr(int k, int u) {
    rseg[k+n] = u+n-k-1;
    for(int i=(k+n)/2; i>0; i/=2)
        rseg[i] = min(rseg[2*i], rseg[2*i + 1]);
}

int mqr(int a, int b) {
    int l=a+n, r=b+n;

    int res = rseg[l];
    while(l <= r) {
        if (l & 1) res = min(res, rseg[l++]);
        if (!(r & 1)) res = min(res, rseg[r--]);
        l/=2, r/=2;
    }

    return res;
}

void update(int k, int u) {
    p[k] = u;
    uql(k, u);
    uqr(k, u);
}

int query(int k) {
    int lh = mqr(0, k) + k - (n - 1);
    int rh = mql(k, n-1) - k;
    int res = min(lh, rh);
    return res;
}

void print_segs() {
    cout << "Left Segment Tree:" << '\n';
    for(auto v : lseg) cout << v << ' ';
    cout << endl;
    cout << "Right Segment Tree:" << '\n';
    for(auto v : rseg) cout << v << ' ';
    cout << endl;
}

void solve() {
    cin >> n >> q;

    p = vector<int>(n, 0), lseg = vector<int>(2*n), rseg = vector<int>(2*n);

    int tmp;
    for(int i=0; i<n; i++) {
        cin >> tmp;
        update(i, tmp);
    }

    /* print_segs(); */

    int t, k;
    while(q--) {
        cin >> t >> k;
        k--;

        switch(t) {
            case 1: {
                int u;
                cin >> u;

                update(k, u);
                break;
            }

            case 2: {
                int res = query(k);
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
