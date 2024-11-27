#include <bits/stdc++.h>
using namespace std;

/* Macros {{{ */
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ii = pair<int,int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvll = vector<vll>;
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

// #define re(a) cin >> a;
// #define rei(a) int a; re(a);
// #define reii(a) ii a; re(a.fi); re(a.se);
// #define rell(a) ll a; re(a);
// #define revi(a, b) vi a(b); each(c, a) re(c);
// #define revll(a, b) vll a(b); each(c, a) re(c);
// #define revii(a, b) vii a(b); each(c, a) re(c.fi), re(c.se);
/* }}} */

int n, qi;
vi v;
vvi t;

// Support LCA Query{{{
vi perm, iperm, parrent;/*{{{*/
void bfs0() {
    perm.assign(n, -1);
    parrent.assign(n, -1);
    queue<int> q({0});
    while(q.sz) {
        int r = q.front(); q.pop();
        perm[r] = iperm.sz;
        iperm.pb(r);

        each(c, t[r]) {
            if (perm[c] >= 0) continue;
            parrent[c] = r;
            q.push(c);
        }
    }
}/*}}}*/

vi order, loc;/*{{{*/
void dfs1(int r=0, int p=-1) {
    loc[r] = order.sz;
    order.pb(perm[r]);
    each(c, t[r]) {
        if (c == p) continue;
        dfs1(c, r);
        order.pb(perm[r]);
    }
}/*}}}*/

vvi sparse;/*{{{*/
vi lp2;
void init_sparse() {
    lp2.rsz(order.sz + 1);

    int p = 1;
    For(i, 0, lp2.sz) {
        p += (1 << p) < i;
        lp2[i] = p-1;
    }

    sparse.assign(order.sz, vi(p));
    For(i, 0, sparse.sz) sparse[i][0] = order[i];
    For(j, 0, p-1) For(i, 0, sparse.sz)
        sparse[i][j+1] = (i + (1<<j) < sparse.sz) ?
            min(sparse[i][j], sparse[i+(1<<j)][j]) : 0;
}

int query_sparse(int l, int r) {
    int siz = r - l + 1;

    int clp2 = lp2[siz];

    int lh = sparse[l][clp2];
    int rh = sparse[r-(1<<clp2)+1][clp2];
    return min(lh, rh);
}

int query_lca(int a, int b) {
    int l = min(loc[a], loc[b]), r = max(loc[a], loc[b]);

    int mm = query_sparse(l, r);
    int lca = iperm[mm];

    return lca;
}/*}}}*//*}}}*/


vi des, depth;/*{{{*/
void dfs0(int r=0, int p=-1, int d=0) {
    depth[r] = d;
    des[r] = 1;
    each(c, t[r]) {
        if (c == p) continue;
        dfs0(c, r, d+1);
        des[r] += des[c];
    }
}/*}}}*/

vi seg;/*{{{*/
vii segInds;
int ch = -1;
stack<int> stak;

void dfs2(int r=0, int p=-1) {
    if (r < 0) {
        while(stak.sz) {
            int e = stak.top(); stak.pop();
            segInds[e].se = ch;
        }
        ch = -1;
        return;
    }

    segInds[r].fi = seg.sz;
    seg.pb(v[r]);
    stak.push(r);
    if (ch == -1) ch = r;

    int dc=-1, dd=0;
    each(c, t[r]) {
        if (c == p) continue;
        if (dd < des[c]) dd = des[c], dc = c;
    }
    dfs2(dc, r);

    each(c, t[r]) {
        if (c == p || c == dc) continue;
        dfs2(c, r);
    }
}

void init_seg() {
    seg.rsz(n), segInds.rsz(n);
    dfs2();
    Rof(i, 0, n) seg[i] = max(seg[2*i], seg[2*i + 1]);
}

void update_seg(int r, int nv) {
    int ind = segInds[r].fi;
    v[r] = nv;
    seg[ind] = nv;
    for(int i = (ind>>1); i>0; i>>=1)
        seg[i] = max(seg[2*i], seg[2*i + 1]);
}

int query_seg(int l, int r) {
    if (l > r) swap(l, r);

    int res = 0;
    while(l <= r) {
        if (l&1) res = max(res, seg[l++]);
        if (!(r&1)) res = max(res, seg[r--]);
        l>>=1, r>>=1;
    }
    return res;
}

int query_to_head(int a) {
    int dph = segInds[a].se;
    int l = segInds[dph].fi, r = segInds[a].fi;
    int res = query_seg(l, r);
    return res;
}

int query_nodes(int a, int b) {
    int l = segInds[b].fi, r = segInds[a].fi;
    int res = query_seg(l, r);
    return res;
}

/*}}}*/

int query(int a, int b) {
    int lca = query_lca(a, b);

    int res = 0;
    while(depth[a] > depth[lca]) {
        int dph = segInds[a].se;
        if (depth[dph] > depth[lca]) {
            res = max(res, query_to_head(a));
            a = parrent[dph];
        } else {
            res = max(res, query_nodes(a, lca));
            a = lca;
        }
    }


    while(depth[b] > depth[lca]) {
        int dph = segInds[b].se;
        if (depth[dph] > depth[lca]) {
            res = max(res, query_to_head(b));
            b = parrent[dph];
        } else {
            res = max(res, query_nodes(b, lca));
            b = lca;
        }
    }


    res = max(res, seg[segInds[lca].fi]);


    return res;
}

void solve() {
    cin >> n >> qi;
    v.rsz(n);
    For(i, 0, n) cin >> v[i];
    t.rsz(n);
    rep(n-1) {
        int a, b; cin >> a >> b; --a, --b;
        t[a].pb(b);
        t[b].pb(a);
    }

    des.rsz(n), depth.rsz(n), loc.rsz(n);
    dfs0();             // populate des and depth
    bfs0();             // populate perm, iperm, and parrent
    dfs1();             // build order
    init_sparse();      // sets up LCA queries
    init_seg();         // builds seg tree and populates segInds

    vi resl;
    rep(qi) {
        int ty, a, b; cin >> ty >> a >> b;
        if (ty == 1) {
            update_seg(a-1, b);
        } else {
            int res = query(a-1, b-1);
            resl.pb(res);
        }
    }

    each(re, resl) cout << re << ' ';
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
