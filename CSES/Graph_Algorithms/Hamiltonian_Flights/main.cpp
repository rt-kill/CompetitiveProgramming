#include <bits/stdc++.h>
using namespace std;

/* Macros {{{ */
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ii = pair<int,int>;
using vi = vector<int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvii = vector<vii>;

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

#define For(i, a, b) for(int i=a; i<b; ++i)
#define Rof(i, a, b) for(int i = (b)-1; i >= (a); --i)
#define rep(a) For(_, 0, a)
#define each(a, x) for (auto &a : x)
#define reach(a, x) for (auto a = x.rbegin(); a != x.rend(); ++a)
/* }}} */

int const M = 1e9 + 7;
int const MC = 1048576;

int n, m;
vvi g;

ll memory[20][MC];
ll dp(int u = 0, int mask = 1) {
    if (u == n-1) return ( mask == (1 << n) - 1 );
    if (memory[u][mask] >= 0) return memory[u][mask];

    ll res = 0;
    for (auto v : g[u]) {
        if ((1<<v) & mask) continue;
        res = ( res + dp(v, mask ^ (1<<v)) ) % M;
    }

    memory[u][mask] = res;
    return res;
}

void solve() {
    cin >> n >> m;
    g.rsz(n);
    rep(m) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].pb(b);
    }

    For(i, 0, n) {
        For(j, 0, (1<<n)) {
            memory[i][j] = -1;
        }
    }

    cout << dp() << '\n';
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
