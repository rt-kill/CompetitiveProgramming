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

int n;
vi g, res, proc;

void solve() {
    cin >> n;
    g.rsz(n+1);
    FOR(i, 1, n+1) cin >> g[i];

    res = vi(n+1, -1), proc = vi(n+1, 0);
    FOR(i, 1, n+1) {
        if ( res[i] > 0 ) continue;

        int c=0, j=i;
        while(res[j] < 0) {
            res[j] = c++;
            j = g[j];
        }

        int dij = c;

        // we know our cycle begins at j, which is c distance from i
        if (!proc[j]) {
            int cl = c - res[j];
            dij -= cl;
            for(int k=j; !proc[k]; k = g[k]) {
                proc[k] = 1;
                res[k] = cl;
            }
        }

        for(int k=i; k != j; k = g[k]) {
            proc[k] = 1;
            res[k] = dij + res[j];
            dij--;
        }
    }

    FOR(i, 1, n+1) cout << res[i] << ' ';
    cout << '\n';
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
