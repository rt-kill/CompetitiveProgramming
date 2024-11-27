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

#define rev(a, x) x.rsz(a); each(b, x) _re_(b);
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
ve<set<int>> adj;

int isPath(int r, int p=-1) {
    if (adj[r].sz > 2) return 0;

    int res = 1;
    each(c, adj[r]) if (c != p) {
        int tmp = isPath(c, r);
        if (res == 0 || tmp == 0) res = 0;
        else res += tmp;
    }

    return res;
}

vi counts;
void pop_counts(int r, int p=-1) {
    counts[r] = 1;
    each(c, adj[r]) if (c != p) {
        pop_counts(c, r);
        counts[r] += counts[c];
    }
}

int findCent(int r) {
    pop_counts(r);
    int tot = counts[r];

    int flag = 0;
    while(!flag) {
        flag = 1;

        each(c, adj[r]) if (counts[c] > tot/2) {
            flag = 0;
            counts[r] -= counts[c];
            counts[c] = tot;
            r = c;
            break;
        }
    }

    return r;
}


int myRec(int r) {
    int pathLen = isPath(r);
    if (pathLen > 0) return pathLen;

    int cent = findCent(r);

    vi cwp, cnp;
    arr<int, 2> mcnp = { INT_MAX, INT_MAX };

    vi children(all(adj[cent]));
    adj[cent].clear();

    // XXX: two things
    //  1: I am not considering the case where all children have a different color
    //      this is always 1 and so never optimal
    //  2: when I call myRec on c, I am assuming that c can be a root
    //      instead, I should call a differnet function that requires r to be the root


    each(c, children) {
        adj[c].erase(cent);
        cnp.pb(myRec(c));
        cmin(mcnp[1], cnp.back());
        if (mcnp[0] > mcnp[1]) swap(mcnp[0], mcnp[1]);
        adj[c].insert(cent);

        adj[cent].insert(c);
        cwp.pb(myRec(c));
        adj[cent].erase(c);
    }

    adj[cent].insert(all(children));

    int res = 0;
    For(i, 0, cwp.sz) {
        int ccwp = cwp[i], ccnp = cnp[i];
        int tmp = (ccnp != mcnp[0]) ? mcnp[0] : mcnp[1];
        cmin(tmp, ccwp);
        cmax(res, tmp);
    }

    return res;
}


void solve() {
    re(n);
    adj.assign(n, set<int>());

    rep(n-1) {
        rdi(u, v);
        --u, --v;
        adj[u].insert(v);
        adj[v].insert(u);
    }

    counts.assign(n, 0);
    int res = myRec(0);
    pln(res);


    // suppose in an optimal solution u and v adjacent by e have differnet colors
    //  then if we delete edge e, nothing changes

    // let dpwp(u, v) be defined as the solution to the subgraph induced by v with parrent u (include u)
    // let dpnp(u, v) be defined as the solution to the subgraph induced by v with parrent u (exclude u)

    // to find res
    // find a centroid u of G, and calculate dpwp(u, v) and dpnp(u, v) for all children v of u

    // res = max{c : child}( min(dpwp(u, c), min{o not c}(dpnp(u, o))) )
    //      after calculating, this can be done in deg(u)log(deg(u))

    // we get T(n) = 2*T(n/2) + deg(n)*log(deg(n))


    // for some vertex r, select a coloring so that
    //  no two vertices of the same color are the same distance from r
    //  for any two vertices of the same color, there is a path between them of that color
    //  the ammount of vertices colored by the least used color is maximal
    // define val(r) to be the ammount of vertices colored by the least used color
    // we would like to find the max over all r of val(r)

    // let r be arbitrary, and consider the tree rooted at r
    //  any two disjoint, point induced subgraphs can not share any colors
    //  that is, letting c[v] be the number of CHILDREN of v (c[v] = deg(v) - 1)
    //      we must use at least sum{v non-leaf}(c[v] - 1) colors
    // so any coloring uses at least
    //      sum{v non-leaf}(c[v] - 1) = sum{v non-leaf}(deg(v) - 2)
    //          = sum{v}(deg(v) - 2) + |leafs|
    //          = 2*|E| - 2|V| + |L| = 2n - 2 - 2n + |L| = |L| - 2
    // suppose all colors are used at least C times
    //  n = sum{colors} #color >= C*|colors|
    //  that is, C <= n/|colors| <= n/(|L|-2)


    // if |L| = 2, solution is obvious
    // suppose that G is not a path (|L| > 2)
    // fix some root r
    //  all leaves must be assigned different colors
    //      if two of them share a parrent, val(r) = 1
    //      otherwise, we may pair them with their unique parrents


    // we can notice bijection between colorings that are valid for some root, and
    //      vertex parititons P such that partitions form paths, and
    //      for some root r, and all p in P, the path p is contained in a path from r to a leaf


    // Lemma: for a valid partition P and two paths p1, p2 in P, no path in P exists that connects two internal nodes of p1 and p2
    //      clear if you draw it out


    // by induction, we prove that a partition P is valid iff any 2 paths, if adjacent, are adjacent by one of the paths ends
    //  take some p in P. the internal nodes of p have children, each of which partition the partitions
    //      by induction, each of these subsets of P are valid


    // O(|E| * |V|/(|L|-2))
    // dp(u, p, co) := solution to subgraph induced by u as a child of p given the color of u get an offset +co
    // val(u) = max(max{c : child}( min(dp(c, u, 1), min{o : child not c}(dp(o, u, 0))) ), min{c : child}( dp(c, u, 0) ));
    // this should be fast enough if |L| >= sqrt(n)
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
