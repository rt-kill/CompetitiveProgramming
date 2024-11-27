#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, q;
vector<int> x;

vector<vector<int>> sm;
vector<int> lp2_leq;

void init_sm() {
    lp2_leq = vector<int>(n+1), lp2_leq[0] = 0;
    for(int i=1, cur=1, e=0; i<=n; i++) {
        e += ((cur << 1) <= i);
        cur <<= ((cur << 1) <= i);
        lp2_leq[i] = e;
    }
    int e = lp2_leq[n];

    sm = vector<vector<int>>(n, vector<int>(e+1));
    for(int i=0; i<n; i++)
        sm[i][0] = x[i];
    for(int i=0; i<e; i++)
        for(int j=0; j<n; j++)
            sm[j][i+1] = min(sm[j][i], sm[min(n-1, j + (1<<i))][i]);

}

int min_query(int a, int b) {
    int diff = lp2_leq[b - a + 1];
    int res = min(sm[a][diff], sm[b - (1<<diff) + 1][diff]);
    return res;
}


void solve() {
    cin >> n >> q;

    x.resize(n);
    for(int i=0; i<n; i++)
        cin >> x[i];

    init_sm();

    int a, b;
    while(q--) {
        cin >> a >> b;
        cout << min_query(a-1, b-1) << '\n';
    }
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
