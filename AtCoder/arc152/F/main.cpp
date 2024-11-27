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

int n;
vvi adj;
vpi edges;

vi counts;
int count(int ei) {
    if (counts[ei] == 0) {
        auto [_, u] = edges[ei];

        counts[ei] = 1;
        each (ej, adj[u]) {
            if (ej == (ei^1)) continue;
            counts[ei] += count(ej);
        }
    }

    return counts[ei];
}

vi mpath;
int pl;
int getPath(int r=0, int p=0) {
    if (r == n-1) { mpath.pb(r); return 1; }
    for(auto ei : adj[r]) {
        auto [_, c] = edges[ei];
        if (c == p) continue;
        if (getPath(c, r)) { mpath.pb(r); return 1; }
    }

    return 0;
}

vvi nadj;
void buildNadj(int r, int p, int e1=-1, int e2=-1) {
    for(auto ei : adj[r]) {
        auto [_, c] = edges[ei];
        if (c == p || c == e1 || c == e2) continue;

        nadj[r].pb(c); // nadj is directed
        buildNadj(c, r, e1, e2);
    }
}

vi ncounts;
int ncount(int r) {
    if (ncounts[r] == 0) {
        ncounts[r] = 1;
        each(c, nadj[r]) ncounts[r] += ncount(c);
    }

    return ncounts[r];
}

int ndfs(int r, int k) {
    if (k == 0) return 1;

    vpi tmp;
    each(c, nadj[r]) tmp.pb({ ncount(c), c });
    sort(all(tmp));

    int cs = transform_reduce(all(tmp), 0, plus{}, [](auto v){ return v.fi; });
    int ss = cs - tmp.back().fi, lu = tmp.back().se;
    if (ss < k/2-2) return 1 + ndfs(lu, k-2-2*ss);

    int res = 1;
    Rof(i, 0, tmp.sz) {
        if (k > 0) ++res;
        k -= tmp[i].fi;
    }

    return res;
}

void solve() {
    re(n);
    adj.rsz(n);
    rep(n-1) {
        rdi(u, v);
        --u, --v;

        edges.pb({ u, v });
        adj[u].pb(edges.sz - 1);

        edges.pb({ v, u });
        adj[v].pb(edges.sz - 1);
    }

    counts.assign(edges.sz, 0);

    getPath();
    reverse(all(mpath));
    pl = mpath.sz;

    // after n operations, we will be on color (n&1), the color of (n-1) is ((pl-1)&1)
    if (((pl-1)&1) ^ (n&1)) { pln(-1); return; }

    vvi buckets(pl);
    buckets[0].pb(1);

    vi bucket_counts(pl);

    For(i, 0, pl) {
        int u = mpath[i];
        each(ei, adj[u]) {
            auto [_, c] = edges[ei];
            if (i > 0 && mpath[i-1] == c) continue;
            if (i < pl-1 && mpath[i+1] == c) continue;
            buckets[i].pb(count(ei));
        }

        bucket_counts[i] = accumulate(all(buckets[i]), 0);
    }

    int bs = accumulate(all(bucket_counts), 0);
    int mbi = max_element(all(bucket_counts)) - bucket_counts.begin();
    int mbc = bucket_counts[mbi];

    if ( mbc-mbi <= bs/2 ) { pln(pl); return; }
    // otherwise, we use mbi nodes from bucket mbi to move to node mbi

    int cni=0, bcb=0;
    while(cni != mbi) {
        buckets[cni].pb(1);
        ++bucket_counts[cni];
        ++cni;
    }

    // toRem is the number of nodes under mbi that we are free to remove as either a back then forwards transaction
    //      a forwards then backwards transaction
    //      or one of the transactions to reach mbi
    int toRem = mbi;
    For(i, 0, pl) if (i != mbi) toRem += bucket_counts[i];

    // the question becomes under the subtree mbi, and preforming k := n-toRem operations
    //      is it possible to end at mbi
    //      and if so what is the min number of vertices visited

    nadj.assign(n, vi());
    int e1 = (mbi > 0)      ? mpath[mbi-1] : -1;
    int e2 = (mbi < pl-1)   ? mpath[mbi+1] : -1;
    buildNadj(mpath[mbi], -1, e1, e2);

    ncounts.assign(n, 0);
    int k = count(mpath[mbi]) - toRem;
    if (k&1) { pln(-1); return; }
    int off = ndfs(mpath[mbi], k) - 1;
    pln(pl + off);

    // k must be even
    // if k is even, a solution always exists:
    //  if there are multiple subtrees:
    //      choose any two leafs in seperate subtrees, and proceed by induction
    //  if there is only one subtree, choose some leaf in it, and then use induction on that subtree with k-2
    //      then as a last operation choose the original root
    // clearly lower k is at least as good

    // suppose r has x children
    //  if I continue on the smaller subtree without just an up down, at least 2 nodes will be added
    //      additionally, this will consume at most 2*#smallSubtreeNodes of k
    //          it would be strictly better to just do up and downs (even on a different subtree)
    //          so we never actually explore the smallest subtree, and its nodes are only ever used as outs

}

int main() {
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
