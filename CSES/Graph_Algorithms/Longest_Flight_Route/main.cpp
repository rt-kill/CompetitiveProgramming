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
#define re(a) resize(a)
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

int n, m;
vvi g;

vi memo, nc;
int dfs(int r=1) {
    if ( r == n ) return 0;
    if ( memo[r] >= -1 ) return memo[r];

    int res = -1;
    for(auto c : g[r]) {
        int sub = dfs(c);
        if (sub >= 0 && sub+1 > res) {
            res = sub+1;
            nc[r] = c;
        }
    }

    memo[r] = res;
    return memo[r];
}

void solve() {
    cin >> n >> m;
    g.re(n+1);
    rep(m) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
    }

    memo = vi(n+1, -2);
    nc.resize(n+1);

    int res = dfs();
    if (res == -1)
        cout << "IMPOSSIBLE" << '\n';
    else {
        vi mout;

        int cc = 1;
        while(cc != 0) {
            mout.pb(cc);
            cc = nc[cc];
        }

        cout << mout.size() << '\n';
        each(v, mout) cout << v << ' ';
        cout << '\n';
    }
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
