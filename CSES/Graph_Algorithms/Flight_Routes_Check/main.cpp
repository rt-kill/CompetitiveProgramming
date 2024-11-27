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

int n, m;
vvi g, rg;
vi c1, c2;

void dfs1(int r=1) {
    if ( c1[r] ) return;
    c1[r] = 1;
    for(auto child : g[r])
        dfs1(child);
}

void dfs2(int r=1) {
    if ( c2[r] ) return;
    c2[r] = 1;
    for(auto child : rg[r])
        dfs2(child);
}


void solve() {
    cin >> n >> m;
    g.rsz(n+1), rg.rsz(n+1);
    rep(m) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b), rg[b].pb(a);
    }

    c1.rsz(n+1), c2.rsz(n+1);
    dfs1();
    dfs2();

    bool res = accumulate(c1.begin() + 1, c1.end(), 1, logical_and{}) && accumulate(c2.begin() + 1, c2.end(), 1, logical_and{});
    if (res) cout << "YES" << '\n';
    else {
        cout << "NO" << '\n';
        int i = find(c1.begin() + 1, c1.end(), 0) - c1.begin();
        if (i <= n) cout << 1 << ' ' << i << '\n';
        else {
            i = find(c2.begin() + 1, c2.end(), 0) - c2.begin();
            cout << i << ' ' << 1 << '\n';
        }
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
