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


int n, m, m2;
vvi g, rg;

vi order, seen;
void build_order(int u) {
    if (seen[u]) return;
    seen[u] = 1;
    for(auto v : g[u])
        build_order(v);
    order.pb(u);
}

vi comp, ncomp;
void set_comp(int u, int c) {
    comp[u] = c;
    for(auto v : rg[u])
        if (comp[v] < 0)
            set_comp(v, c);
}

ve<set<int>> cg;
vi res, seen2;
void assign_literals(int l) {
    if (seen2[l]) return;
    seen2[l] = 1;

    int assignment = 1;
    each(dl, cg[l]) {
        assign_literals(dl);
        assignment = assignment & res[dl];
    }

    int nl = ncomp[l];
    if (res[nl] < 0) {
        res[l] = assignment;
        res[nl] = res[l] ^ 1;
    }
}

void solve() {
    cin >> n >> m;
    m2 = 2*m;
    g.rsz(m2), rg.rsz(m2);
    rep(n) {
        char s1, s2; int t1, t2;
        cin >> s1 >> t1 >> s2 >> t2;
        t1--, t2--;

        int l1 = (s1 == '+') ? t1 : t1 + m;
        int nl1 = (l1 + m)%m2;
        int l2 = (s2 == '+') ? t2 : t2 + m;
        int nl2 = (l2 + m)%m2;

        g[nl1].pb(l2), g[nl2].pb(l1);
        rg[l2].pb(nl1), rg[l1].pb(nl2);
    }

    seen.rsz(m2);
    For(u, 0, m2) build_order(u);

    comp.assign(m2, -1);
    int num_comp = 0;
    reach(it, order) {
        int u = *it;
        if (comp[u] < 0) {
            set_comp(u, num_comp++);
        }
    }

    /* For(u, 0, m2) cout << u << ':' << comp[u] << ' '; */
    /* cout << '\n'; */

    ncomp.rsz(num_comp);
    For(l, 0, m) {
        int nl = l + m;
        if (comp[l] == comp[nl]) {
            cout << "IMPOSSIBLE" << '\n';
            return;
        }

        ncomp[comp[l]] = comp[nl];
        ncomp[comp[nl]] = comp[l];
    }

    /* For(u, 0, m2) cout << ((u+m) % m2) << ':' << ncomp[comp[u]] << ' '; */
    /* cout << '\n'; */

    /* cout << '\n'; */

    cg.rsz(num_comp);
    For(u, 0, m2) each(v, g[u]){
        if (comp[u] != comp[v])
            cg[comp[u]].insert(comp[v]);
    }

    /* For(u, 0, num_comp) { */
    /*     cout << "COMP " << u << '\n'; */
    /*     cout << "CHILDREN: "; */
    /*     each(v, cg[u]) { */
    /*         cout << v << ' '; */
    /*     } */
    /*     cout << '\n'; */
    /* } */
    /* cout << '\n'; */

    seen2.rsz(num_comp), res.assign(num_comp, -1);
    For(l, 0, num_comp) assign_literals(l);
    For(u, 0, m) cout << (res[comp[u]] == 1 ? '+' : '-') << ' ';
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
