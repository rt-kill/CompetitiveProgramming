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
vi res, seen, active;
bool good;
void dfs(int r) {
    if (seen[r]) return;
    if (active[r]) {
        good=0;
        return;
    }
    active[r] = 1;

    for(auto c : g[r]) dfs(c);
    res.pb(r);

    active[r] = 0;
    seen[r] = 1;
}

void solve() {
    cin >> n >> m;
    g.re(n+1), seen.re(n+1), active.re(n+1);
    rep(m) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
    }

    good = 1;
    FOR(i, 1, n+1) dfs(i);
    if(good) {
        for_each(rall(res), [](auto v){cout << v << ' ';});
        cout << '\n';
    }
    else
        cout << "IMPOSSIBLE" << '\n';
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
