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
vvi g, rg;

vi seen;
vi post_order;
void dfs(int u) {
    if (seen[u]) return;
    seen[u] = 1;

    for(auto v : g[u]) dfs(v);
    post_order.pb(u);
}

vi uf, siz;
int gp(int a) {
    if (a != uf[a])
        uf[a] = gp(uf[a]);
    return uf[a];
}

void merge(int a, int b) {
    int l=gp(a), r=gp(b);
    if (l==r) return;
    if (siz[l] < siz[r]) {
        uf[l] = r;
        siz[r] += siz[l];
    } else {
        uf[r] = l;
        siz[l] += siz[r];
    }
}

int gs(int a) {
    return siz[gp(a)];
}

vi seen2;
void dfs2(int u) {
    if (seen2[u]) return;
    seen2[u] = 1;

    for(auto v : rg[u]) {
        if (!seen2[v]) {
            dfs2(v);
            merge(u, v);
        }
    }
}

void solve() {
    cin >> n >> m;
    g.rsz(n+1), rg.rsz(n+1);
    rep(m) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
        rg[b].pb(a);
    }

    uf.resize(n+1);
    iota(all(uf), 0);
    siz = vi(n+1, 1);

    seen.rsz(n+1);
    For(i, 1, n+1) dfs(i);
    seen2.rsz(n+1);
    Rof(i, 0, n) dfs2(post_order[i]);

    set<int> reps;
    vi mymap = vi(n+1, 0);
    For(i, 1, n+1) reps.insert(gp(i));
    int h=1;
    each(rep, reps) mymap[rep] = h++;
    cout << reps.size() << '\n';
    For(i, 1, n+1) cout << mymap[gp(i)] << ' ';
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
