#include <bits/stdc++.h>
using namespace std;

/* Macros {{{ */
using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using vi = vector<int>;
using vii = vector<ii>;
using vvi = vector<vi>;

#define arr array
#define ve vector
#define pb push_back
#define rsz(a) resize(a)
#define mp make_pair
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define sz size()

#define FOR(i, a, b) for(int i=a; i<b; ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for(int i = ( b )-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define rep(a) F0R(_, a)
#define each(a, x) for (auto &a : x)
/* }}} */

int const MN = 2e5;
int const MK = 1e9;
int const l2MK = 29;

int n, q;

int ri=0, res[MN];

int sparse[MN+1][l2MK+1] = {};
void query_sparse(int x, int k) {
    for(int i=1, e=0; i<=k; i<<=1, ++e)
        if (i & k) x = sparse[x][e];
    res[ri++] = x;
}


void solve() {
    cin >> n >> q;

    FOR(i, 1, n+1) cin >> sparse[i][0];
    FOR(e, 1, log2(MK))
        FOR(i, 1, n+1)
            sparse[i][e] = sparse[sparse[i][e-1]][e-1];


    rep(q) {
        int x, k;
        cin >> x >> k;
        query_sparse(x, k);
    }

    F0R(i, q) cout << res[i] << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
    // you should actually read the stuff at the bottom
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
