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
/* }}} */

int n, m;
vi k;
vvi g, rg;

vi order, s1;
void dfs1(int u) {
    if (s1[u]) return;
    s1[u] = 1;
    for(auto v : g[u]) dfs1(v);
    order.pb(u);
}

vi comp;
void dfs2(int u, int c) {
    comp[u] = c;
    for(auto v : rg[u]) {
        if (comp[v] >= 0) continue;
        dfs2(v, c);
    }
}

ve<ll> cv;
vvi cg;

ve<ll> best;
ll dfs3(int u) {
    if (best[u] == 0) {
        ll res = 0;
        for(auto v : cg[u])
            res = max(res, dfs3(v));
        res += cv[u];
        best[u] = res;
    }

    return best[u];
}

void solve() {
    cin >> n >> m;

    k.rsz(n);
    For(i, 0, n) cin >> k[i];

    g.rsz(n), rg.rsz(n);
    rep(m) {
        int a, b;
        cin >> a >> b;
        a--,b--;
        g[a].pb(b);
        rg[b].pb(a);
    }

    s1.rsz(n);
    For(i, 0, n) dfs1(i);
    comp.assign(n, -1);
    int nc=0;
    Rof(i, 0, n) if (comp[order[i]] < 0) dfs2(order[i], nc++);

    cv.resize(nc);
    For(u, 0, n) cv[comp[u]] += k[u];

    cg.resize(nc);
    For(u, 0, n) {
        each(v, g[u]) {
            if (comp[u] != comp[v]) {
                cg[comp[u]].pb(comp[v]);
            }
        }
    }

    best.rsz(nc);
    For(u, 0, nc) dfs3(u);
    ll res = *max_element(all(best));
    cout << res << '\n';
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
