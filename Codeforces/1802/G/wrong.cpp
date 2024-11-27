#include <bits/stdc++.h>
using namespace std;

/* Macros {{{ */
/* Basics {{{ */
using ll    = long long;
using ull   = unsigned long long;
using ld    = long double;
using str   = string;

using pi    = pair<int,int>;
using pll   = pair<ll, ll>;
using pld   = pair<ld, ld>;

using vi    = vector<int>;
using vll   = vector<ll>;
using vld   = vector<ld>;

using vpi   = vector<pi>;
using vpll  = vector<pll>;
using vpld  = vector<pld>;

using vvi   = vector<vi>;
using vvll  = vector<vll>;
using vvld  = vector<vld>;

using vvpi  = vector<vpi>;
using vvpll = vector<vpll>;
using vvpld = vector<vpld>;

#define INF     INFINITY
#define arr     array
#define ve      vector
#define pb      push_back
#define rsz(a)  resize(a)
#define mp      make_pair
#define fi      first
#define se      second
#define all(x)  x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define sz      size()

#define lb lower_bound
#define ub upper_bound

#define For(i, a, b)    for(int i=a; i<b; ++i)
#define Rof(i, a, b)    for(int i = (b)-1; i >= (a); --i)
#define rep(a)          For(_, 0, a)
#define each(a, x)      for(auto &a : x)
#define reach(a, x)     for(auto a = x.rbegin(); a != x.rend(); ++a)

template<typename T, typename U> inline void cmin(T &x, U y) { if(y < x) x = y; }
template<typename T, typename U> inline void cmax(T &x, U y) { if(x < y) x = y; }
/*}}}*/

/* IO {{{ */
// Read
#define _re_(a)     cin >> a;
#define re(...)     FOR_EACH(_re_, __VA_ARGS__)

#define rev(a, x)   x.rsz(a); each(b, x) _re_(b);
#define rewv(a, x)  _re_(a); rev(a, x);

#define _rdi_(a)    int a; _re_(a)
#define rdi(...)    FOR_EACH(_rdi_, __VA_ARGS__)

#define _rdll_(a)   ll a; _re_(a)
#define rdll(...)   FOR_EACH(_rdll_, __VA_ARGS__)

#define _pr_(a)     cout << a << ' ';
#define pr(...)     FOR_EACH(_pr_, __VA_ARGS__)

#define _ln_(...)       cout << '\n';
#define ln()            cout << '\n';

#define pln(...)        pr(__VA_ARGS__); cout << '\n';

#define _peln_aux_(a)    cout << a << '\n';
#define _peln_(...)      FOR_EACH(_peln_aux_, __VA_ARGS__)
#define peln(...)        _pln_(__VA_ARGS__)

/* IO - Helpers {{{*/
#define PARENS ()
#define EXPAND(arg)     EXPAND1(EXPAND1(EXPAND1(EXPAND1(arg))))
#define EXPAND1(arg)    EXPAND2(EXPAND2(EXPAND2(EXPAND2(arg))))
#define EXPAND2(arg)    EXPAND3(EXPAND3(EXPAND3(EXPAND3(arg))))
#define EXPAND3(arg)    EXPAND4(EXPAND4(EXPAND4(EXPAND4(arg))))
#define EXPAND4(arg)    arg

#define FOR_EACH(macro, ...)                                    \
  __VA_OPT__(EXPAND(FOR_EACH_HELPER(macro, __VA_ARGS__)))
#define FOR_EACH_HELPER(macro, a1, ...)                         \
  macro(a1)                                                     \
  __VA_OPT__(FOR_EACH_AGAIN PARENS (macro, __VA_ARGS__))
#define FOR_EACH_AGAIN() FOR_EACH_HELPER
/*}}}*//*}}}*//*}}}*/

int const M = 1e9+7;

ll modpow(int a, int b) {/*{{{*/
    ll res = 1;
    for(ll ce=1, cp=a; ce <= b; ce<<=1, cp=cp*cp%M)
        if (ce & b) res = res*cp%M;
    return res;
}

ll moddiv(int a, int b) {
    ll num = a, den = modpow(b, M-2);
    ll res = num * den % M;
    return res;
}/*}}}*/


int n, m;
vi parrent;
vpll gasRange;
ve<arr<int, 4>> queries;
ve<ve<arr<int, 4>>> pqueries;
vll res;

int mp2;
vvi sparse;
vi depth;

void init() {/*{{{*/
    re(n);

    parrent.assign(n, 0);
    For(i, 1, n) {
        re(parrent[i]);
        --parrent[i];
    }

    gasRange.rsz(n);
    For(i, 0, n) { re(gasRange[i].fi, gasRange[i].se); }

    re(m);
    queries.rsz(m);
    For(i, 0, m) {
        rdi(a, b, c, d);
        queries[i] = { --a, --b, --c, --d };
    }

    depth.assign(n, -1);
    depth[0] = 0;
}/*}}}*/

void init_sparse() {/*{{{*/
    mp2=0;
    while(n >= (1<<mp2)) ++mp2;

    sparse.assign(n, vi(mp2));
    For(i, 0, n) sparse[i][0] = parrent[i];
    For(j, 0, mp2) For(i, 0, n)
        sparse[i][j+1] = sparse[sparse[i][j]][j];
}

int query_depth(int u) {
    if (depth[u] >= 0) return depth[u];

    int cp=u, cd=0;
    Rof(j, 0, mp2) {
        if (sparse[cp][j] != 0) {
            cp = sparse[cp][j];
            cd += (1<<j);
        }
    }

    depth[u] = cd+1;
    return depth[u];
}

int query_parrent(int u, int d) {
    int cp=u, cd=d;
    Rof(j, 0, mp2) {
        if (cd >= (1<<j)) {
            cp = sparse[cp][j];
            cd -= (1<<j);
        }
    }
    return cp;
}

int query_lca(int u, int v) {
    int du = query_depth(u), dv = query_depth(v);

    if (du < dv) v = query_parrent(v, dv-du);
    if (du > dv) u = query_parrent(u, du-dv);

    if (u == v) return u;

    int cu=u, cv=v, cd=0;
    Rof(j, 0, mp2) {
        if (sparse[cu][j] != sparse[cv][j]) {
            cu = sparse[cu][j];
            cv = sparse[cv][j];
            cd += (1<<j);
        }
    }

    return parrent[cu];
}/*}}}*/

void preprocess_queries() {/*{{{*/
    init_sparse();

    pqueries.rsz(m);
    For(i, 0, m) {
        auto [ a, b, c, d ] = queries[i];
        int lca1 = query_lca(a, b), lca2 = query_lca(c, d);

        int da = query_depth(a), db = query_depth(b);
        int dc = query_depth(c), dd = query_depth(d);

        int dlca1 = query_depth(lca1), dlca2 = query_depth(lca2);

        if (da - dlca1 >= dc - dlca2) {
            int l1 = dc - dlca2, l2 = da - dlca1 - l1, l3 = db - dlca1;

            int m1 = query_parrent(a, l1);
            int m2 = query_parrent(d, l3);

            pqueries[i].pb( { a, m1, c, lca2 } );
            pqueries[i].pb( { m1, lca1, lca2, m2 } );
            pqueries[i].pb( { lca1, b, m2, d } );
        } else {
            int l1 = da - dlca1, l2 = dc - dlca2 - l1, l3 = dd - dlca2;

            int m1 = query_parrent(b, l3);
            int m2 = query_parrent(c, l1);

            pqueries[i].pb( { a, lca1, c, m2 } );
            pqueries[i].pb( { lca1, m1, m2, lca2 } );
            pqueries[i].pb( { m1, b, lca2, d } );
        }
    }

    each(qset, pqueries) each(que, qset) {
        if (min(query_depth(que[0]), query_depth(que[1])) > min(query_depth(que[2]), query_depth(que[3]))) {
            swap(que[0], que[2]);
            swap(que[1], que[3]);
        }

        if (query_depth(que[0]) < query_depth(que[1])) {
            swap(que[0], que[1]);
            swap(que[2], que[3]);
        }
    }
}/*}}}*/

vi ds, cc;/*{{{*/
vpll rr;
ll prod;
map<pi, pi> pnm;
map<arr<int, 3>, arr<int, 3>> rpnm;

void init_ds() {
    ds.rsz(n);
    iota(all(ds), 0);

    cc.assign(n, 1);

    rr.assign(all(gasRange));

    prod = transform_reduce(all(rr), 1ll,
            [](auto l, auto r){ return l * r % M; },
            [](auto cr){ return cr.se - cr.fi + 1; });
}

int find(int u) {
    if (ds[u] != ds[ds[u]]) ds[u] = find(ds[u]);
    return ds[u];
}

void merge(int u, int v) {
    int r1 = find(u), r2 = find(v);
    if (r1 == r2) return;

    int nr=r1, pr=r2;
    if (cc[r1] < cc[r2]) swap(nr, pr);

    ds[pr] = nr;
    cc[nr] += cc[pr];

    auto rr1=rr[nr], rr2=rr[pr];
    pll nrr = { max(rr1.fi, rr2.fi), min(rr1.se, rr2.se) };
    rr[nr] = nrr;

    if (rr1.fi <= rr1.se) prod = moddiv(prod, rr1.se - rr1.fi + 1);
    if (rr2.fi <= rr2.se) prod = moddiv(prod, rr2.se - rr2.fi + 1);

    if (nrr.fi <= nrr.se) prod = prod * (nrr.se - nrr.fi + 1) % M;
    else prod = 0;
}

pi findPar(pi cp) {
    if (!pnm.count(cp)) {
        auto [ u, v ] = cp;
        if (u == 0 || v == 0) return { u, v };

        int r1 = find(u), r2 = find(v);
        if (r1 != r2) return { u, v };

        pnm[cp] = { parrent[u], parrent[v] };
    }

    pnm[cp] = findPar(pnm[cp]);
    return pnm[cp];
}

// provided { a, c, depth }, returns the smallest k<=d such that
//  a+k and c+depth-k are not merged
arr<int, 3> rfindPar(arr<int, 3> crp) {
    if (!rpnm.count(crp)) {
        auto [ u, v, d ] = crp;
        if (d == 0) return { u, v, d };

        int r1 = find(u), r2 = find(query_parrent(v, d));
        if (r1 != r2) return { u, v, d };

        rpnm[crp] = { parrent[u], v, d-1 };
    }

    rpnm[crp] = rfindPar(rpnm[crp]);
    return rpnm[crp];
}/*}}}*/

void apply_query(arr<int, 4> quer) {/*{{{*/
    auto [ a, b, c, d ] = quer;
    int da = query_depth(a), db = query_depth(b);
    int dc = query_depth(c), dd = query_depth(d);

    int reved = dc < dd;

    if (!reved) { // both are moving up
        int ca=a, cc=c;
        while(query_depth(ca) > db) {
            merge(ca, cc);
            tie(ca, cc) = findPar({ ca, cc });
        }
        if (ca == b) merge(ca, cc);

    } else {
        int ca=a, cc=d, cd=da-db;
        while(cd > 0) {
            merge(ca, query_parrent(cc, cd));
            auto [ta, tc, td] = rfindPar({ ca, cc, cd });
            ca = ta, cc = tc, cd = td;
        }
        if (ca == b) merge(ca, cc);
    }
}/*}}}*/

void solve() {
    init();
    preprocess_queries();
    init_ds();

    res.assign(m, 0);
    For(i, 0, m) {
        /* pln("Query", i); */

        each(quer, pqueries[i]) apply_query(quer);
        res[i] = prod;

        /* ln(); */
    }

    each(resp, res) { pln(resp) };

    // consider a new graph with a node for each city, and initially no edges
    //  whenever the kings children run a check, it imposes some structure on the cities (specifically that some of them must have the same prices)
    //  in this new graph, there will be an edge between two cities only if they must share the same prices
    //      that is, in one of the childrens walks, the two cities are checked at the same time
    // since the only part we really care about are the components, we can use a union find

    // we need to be able to maintain the valid intervals of each set (the intersection of all gasRanges within it)
    // and the product of all intervals
    //  this is not hard: when we union, update the interval, and multiply the current product by the inverse of the two, and then their intersection

    // so the only question is how to efficiently process each query
    //  it is clearly too slow to manually traverse the paths

    // repeated queries may be "removed"
    // queries contained in previous queries may be "removed"
    // intersections of paths may be "reomved"
    // queries that contain previous queries may be "split"
    // if the paths in a query intersect at some point, the nodes may be merged

    // we cant merge just any query, because it will destroy the tree structure
    //  that is it could create a cycle

    // suppose all queries share an end point
    //  the solution would be:
    //      given a query { a, b, c, d } (b == d)
    //      first use a map to convert points to valid nodes { a, c } = { M[a], M[c] }
    //      while(a != c)
    //          preform union operation
    //          replace all edges in/out of c with edges in/out of a (this maintains the tree structure)
    //          update M[c] = a
    //          step a and c

    // since every step decreases the number of nodes by 1, this is O(n + m)

    // the process is very similar if instead of sharing an end point, they simply share a point (or their ends share a parrent)
    //  the only diference is we need to first find the intersection point
    //  this change makes it O(n + m*log(n))

    // now back to the general question
    // what is the problem with creating cycles?
    //  one problem is that we can not simply stop stepping when we hit an intersecting point
    //      -- the paths may diverge again later
    //  another problem is that we no longer know where to step (the paths between nodes are no longer unique)


    // we can do some preprocessing on the queries as follows:
    //  start with the query {a, b, c, d}
    //      find the lowest common ancestor of l1, l2 of (a, b), (c, d) rooted at 0
    //      replace the query with the 4 queries:
    //          { a, min(l1, p[a]...), ... }

    // this allows us to assume that for every query
    //  (a, b) is a path up/down (we choose) the rooted tree
    //  (b, c) is either a path up/down (we don't choose) the rooted tree

    // we would like to do more preprocessing:
    //  specifically, given some query with already merged heads, I would like to find the smallest depth such that the nodes are no longer merged
    //      we store an object, where a pair (a, b) of merged nodes stores the first pair (a+d, b+d) whose parrents are not merged
    //          if the parrents of (a, b) are merged, set its value to the value of its parrents
    //  this is similar to a union find





    // some assumptions we can make:
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    /* cout << fixed << setprecision(6); */
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
