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

vi uf, siz;
int gp(int a) {
    if (uf[ uf[a] ] != uf[a])
        uf[a] = gp(uf[a]);
    return uf[a];
}

void merge(int a, int b) {
    int l=gp(a), r=gp(b);
    if (l == r) return;
    if (siz[l] < siz[r]) {
        uf[l] = r;
        siz[r] += siz[l];
    } else {
        uf[r] = l;
        siz[l] += siz[r];
    }
}

vi post, s1;
void dfs1(int u) {
    if (s1[u]) return;
    s1[u] = 1;
    for(auto v : g[u]) dfs1(v);
    post.pb(u);
}

vi s2;
void dfs2(int u) {
    if (s2[u]) return;
    s2[u] = 1;

    for(auto v : rg[u]) {
        if (s2[v]) continue;
        dfs2(v);
        merge(u, v);
    }
}

ve<set<int>> ng;
void init_ng() {
    For(u, 0, 2*m) {
        each(v, g[u]) {
            if (gp(u) != gp(v))
                ng[gp(u)].insert(gp(v));
        }
    }
}

vi res;
void dfs3(int u) {
    int rep = gp(u);
    if (res[rep] >= 0) return;

    int setting = 1;
    each(v, ng[rep]) {
        dfs3(v);
        setting = setting && res[gp(v)];
    }

    int nrep = ( rep + m )%m;
    int repnrep = gp(nrep);

    if (res[repnrep] >= 0) {
        res[rep] = res[repnrep]^1;
    }
    if (res[rep] < 0) {
        res[rep] = setting;
    }

    res[repnrep] = res[rep] ^ 1;
}

void solve() {
    cin >> n >> m;
    g.rsz(2*m), rg.rsz(2*m);

    rep(n) {
        char s1, s2; int t1, t2;
        cin >> s1 >> t1 >> s2 >> t2;
        t1--, t2--;

        int r1 = (s1 == '+') ? t1 : t1 + m;
        int nr1 = ( r1 + m ) % 2*m;
        int r2 = (s2 == '+') ? t2 : t2 + m;
        int nr2 = ( r2 + m ) % 2*m;

        g[nr1].pb(r2);
        g[nr2].pb(r1);
        rg[r1].pb(nr2);
        rg[r2].pb(nr1);
    }

    uf.rsz(2*m);
    iota(all(uf), 0);
    siz = vi(2*m, 1);

    s1.rsz(2*m), s2.rsz(2*m);
    For(i, 0, 2*m) dfs1(i);
    Rof(i, 0, 2*m) dfs2(post[i]);

    For(i, 0, m) if (gp(i) == gp(i + m)) {
        cout << "IMPOSSIBLE" << '\n';
        return;
    }

    ng.resize(2*m);
    init_ng();

    res = vi(2*m, -1);
    For(i, 0, 2*m) dfs3(i);
    For(i, 0, 2*m) res[i] = res[gp(i)];

    For(i, 0, m) cout << (( res[i] == 0 ) ? '-' : '+') << ' ';
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
