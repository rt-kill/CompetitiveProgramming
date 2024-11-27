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
#define _pln_aux_(a)    cout << a << '\n';
#define _pln_(...)      FOR_EACH(_pln_aux_, __VA_ARGS__)
/* #define _pln_fork_(...) TENTH_PARAM(__VA_ARGS__,_pln_,_pln_,_pln_,_pln_,_pln_,_pln_,_pln_,_pln_,_ln_)(__VA_ARGS__) */
#define pln(...)        _pln_(__VA_ARGS__)

/* IO - Helpers {{{*/
#define TENTH_PARAM(_0,_1,_2,_3,_4,_5,_6,_7,_8,NAME,...) NAME

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
vvi adj, radj, symC;
vvi buckets;
vi sym, isSym;

void clean() { n=-1, adj.clear(), radj.clear(), symC.clear(), buckets.clear(), sym.clear(); }

void root(int r=0, int p=0) {
    each(c, adj[r]) if (c != p) {
        radj[r].pb(c);
        root(c, r);
    }
}

void dfs(int r=0, int d=0) {
    while(buckets.sz <= d) buckets.pb(vi());
    buckets[d].pb(r);
    each(c, radj[r]) dfs(c, d+1);
}

vi symCounts; // be careful to keep this array all zeros
int isSymetric(int r=0) {
    int symSum = 0;
    each(c, radj[r]) {
        symSum += (symCounts[sym[c]] == 0) ? 1 : -1;
        symCounts[sym[c]] ^= 1;
    }

    if (symSum == 0) return 1;

    if (symSum == 1) {
        each(c, radj[r]) if (symCounts[sym[c]] > 0) {
            symCounts[sym[c]] = 0; // should be the only zero
            return isSymetric(c);
        }
    }

    return 0;
}

void solve() {
    clean();

    re(n);
    adj.assign(n, vi());
    rep(n-1) {
        rdi(u, v);
        --u, --v;
        adj[u].pb(v), adj[v].pb(u);
    }

    radj.assign(n, vi());
    root();

    dfs();

    auto bucketComp = [&](auto l, auto r) { return symC[l] < symC[r]; };

    sym.assign(n, 0);
    isSym.assign(n, 0);
    symC.assign(n, vi());

    each(u, buckets.back()) isSym[u] = 1;
    Rof(d, 0, buckets.sz-1) {
        auto bucket = buckets[d];
        each(u, bucket) {
            each(v, radj[u]) symC[u].pb(sym[v]);
            sort(all(symC[u]));

            /* map<int, int> counts; */
            /* each(v, symC[u]) counts[v] ^= 1; */
            /* int osum = transform_reduce(all(counts), 0, plus{}, [](auto v){ return v.se; }); */

            /* if (osum == 0) isSym[u] = 1; */
            /* if (osum == 1) { */
            /*     each(v, radj[u]) if (counts[sym[v]] > 0) */

            /* } */
        }

        sort(all(bucket), bucketComp);
        sym[bucket[0]] = 0;
        For(i, 1, bucket.sz) sym[bucket[i]] = sym[bucket[i-1]] + (symC[bucket[i]] != symC[bucket[i-1]]);
    }

    symCounts.assign(*max_element(all(sym)) + 1, 0);
    int res = isSymetric();
    pln((res ? "Yes" : "No"));

    // if a tree is symetric, all of its levels from the bottom up must be symetric
    //  clearly, the bottom level of nodes are "symetric"
    //      we will assign each node at each level a "symetry group"
    //      two nodes have the same symetry group if and only if their induced rooted subtrees are isomorphic
    //  assuming that the nodes below have been assigned proper symetry groups
    //      two nodes have the same symetry group iff they have the same number of children in each symetry group

    // when setting the symetry groups, we maintain the following property
    //  the smallest symetry group has value 1
    //  in order of symetry group magnitude, g*C[g] < n(g)
    //      this makes is so that the groups below a node are uniquely defined by their sum
    //  unfortunately, this is exponentonal, and so not possible
}

int main() {
    /* cout << fixed << setprecision(6); */
    int t=1;
    cin >> t;
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
