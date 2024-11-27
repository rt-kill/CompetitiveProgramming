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
#define re(...)     { FOR_EACH(_re_, __VA_ARGS__) }

#define rewv(a, x)  { _re_(a); x.rsz(a); each(b, x) _re_(b); }

#define _rdi_(a)    int a; _re_(a)
#define rdi(...)    FOR_EACH(_rdi_, __VA_ARGS__)

#define _rdll_(a)   ll a; _re_(a)
#define rdll(...)   FOR_EACH(_rdll_, __VA_ARGS__)

#define _pr_(a)     cout << a << ' ';
#define pr(...)     { FOR_EACH(_pr_, __VA_ARGS__) }

#define _ln_(...)       cout << '\n';
#define ln()            cout << '\n';
#define _pln_aux_(a)    cout << a << '\n';
#define _pln_(...)      FOR_EACH(_pln_aux_, __VA_ARGS__)
/* #define _pln_fork_(...) TENTH_PARAM(__VA_ARGS__,_pln_,_pln_,_pln_,_pln_,_pln_,_pln_,_pln_,_pln_,_ln_)(__VA_ARGS__) */
#define pln(...)        { _pln_(__VA_ARGS__) }

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

int const M = 998244353;

int n;
void solve() {
    re(n);

    // Given any labled tree, a permutation on nodes will generate a new distinct tree if and only if
    //  the nodes in the permutation are NOT leaves to the same parrent
    // Any permutation can be written in a "simplest" form
    //  as a product of disjoint cycles such that the nodes in each cycle pairwise are NOT leaves to the same parrent
    //      suppose some cycle has multiple nodes (u, v) that are leaves to the same parrent
    //          (u, ..., A, v, ..., B) = (u, ..., A)(v, ..., B)

    // what if we just consider the ways of assign -1 edges
    //  for each valid assignment of -1 edges, any method of completing the tree will make a valid tree
    //  these assignments will create components that we can then connect

    // Lemma: a component must have an even number of nodes
    //  2E = 2(n-1) = sum(deg(v))
    //      sum(deg(v)) is even, and we have an odd number of nodes
    //      so some node must have even degree, but then this component is not good

    // Corollary: there are no good trees on an odd number of nodes
    //  good trees induce a decompositon into even order components
    //  such a decomposition does not exist on an odd number of nodes


    // This observation gives us an inductive way of counting good trees
    // let T(n) be the number of good trees on n nodes
    // let G(n) be the number of good trees on n nodes that use only -1 edges

    // XXX: We are over counting!!!
    //  Something = (n choose 2)G(2)T(n-2)(2*(n-2)) + (n choose 4)G(4)T(n-4)(4*(n-4)) + ... + G(n)
    // To stop overcounting, we require node 1 be in the comp we correlate with G
    //  T(n) = (n-1 choose 2-1)G(2)T(n-2)(2*(n-2)) + (n-1 choose 4-1)G(4)T(n-4)(4*(n-4)) + ... + G(n)


    // Definition: super good tree -- a good tree with only -1 edges
    //  equivilently, a tree for which every node has odd degree

    // Lemma: for n > 2, supper good trees must have a node with degree > 2
    //  otherwise every node is a leaf, but this is not possible

    // Lemma: for n > 2, supper good trees have a node to which two leaves are connected
    //  the base case is n=4, for which there is a unique super good tree
    //  for n>4, we take some node of degree > 2, call it r
    //      while r has an unvisited child c of degree > 2,
    //          mark r as visited
    //          set r=c
    //  since the tree is finite, this process must terminate
    //  the node that we terminate on has at least 2 unvisited nodes
    //  these nodes must be leafs QED

    // Let S be the set of all good trees on n nodes
    //  we can partition S into sets such that
    //      two trees are in the same set if and only if
    //          the component induced by the path from 1 to n is the same
    //      the induced component is the number of nodes rechable via -1 edges from this path




    // XXX: ^ Looks like its getting no where

    // let S be some collection of k Components such that S[1] has node 1 and S[k] has node n
    // there are 2^{|S|-2} trees over these components
    //  there is a symetric property here
    //      sum{trees}(sum{nodes}(deg(v))) = 2^{|S|-2}2*(n-1)
    //      = sum{nodes}(sum{trees}(deg(v)))
    //      = |S|(sum{trees}(deg(v)))
    //      -> sum{trees}(deg(v)) = 2^{|S|-2}2(n-1)/|S|
    //
    //  the number of trees we can make is
    //      sum{trees}(sum{nodes}(|S[v]|deg(v)))
    //      = sum{nodes}|S[v]|sum{trees}(deg(v))
    //      = 2^{|S|-2}2(n-1)/|S| * sum{nodes}|S[v]|
    //
    //      = (n*(n-1) * 2^{|S|-1}) / (|S|)

    // This number is per component assignment


    // In an arbitrary tree, there is a unique path from 1 to n
    //  we iterate over the first +1 that we hit along this path
    //      suppose we hit the first +1 at edge i
    //  R = #(good trees such that there is a path out of 1 of length i, that takes 1 to n, ...)
    //    = T(i, i)*T(n-i,0)
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
