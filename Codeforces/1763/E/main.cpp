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

int p;

// requires k > 0
int largest(int k) {
    // return largest n such that (n choose 2) <= k

    int l = 2, r = ceil(sqrt(k)) + 2;
    while(l < r) {
        int m = (l+r+1)/2;
        int mc2 = m*(m-1)/2;

        pr(l, r, m, mc2, k);
        ln();

        if (mc2 > k) {
            r = m-1;
        } else {
            l = m;
        }
    }

    pr(k, l, r);
    ln();
    return l;
}

int minNodes(int tp) {
    int nodes = 0, cp = tp;
    while(cp > 0) {
        int lrg = largest(cp);
        int lrgc2 = lrg*(lrg-1)/2;
        cp -= lrgc2;
        nodes += lrg;
    }

    return nodes;
}

void solve() {
    re(p);
    if (p == 0) {
        pr(0, 0);
        ln();
        return;
    }

    int nodes = minNodes(p);


    // in order to maximize unidirectional pairs, we would like to find the maximum k for which (maximize components)
    //      nodes = a1 + a2 + ... + ak
    //      p = (a1 choose 2) + (a2 choose 2) + ...
    //
    // since nodes is minimal, ai > 1
    //  greedy?
    //      while(nodes > 2 and (p-1 is acheviable by (nodes-2))) take 2?

    vi compSizes;
    int cp = p, cn = nodes;
    For(i, 2, 1000) {
        int ic2 = i*(i-1)/2;
        while(minNodes(cp - ic2) == cn - i) {
            cp -= ic2, cn -= i;
            compSizes.pb(i);
        }
    }

    sort(all(compSizes));

    ll Muni = 0, pn=0;
    each(x, compSizes) {
        ll diff = pn*x;
        Muni += diff;
        pn += x;
    }

    sort(all(compSizes), greater<int>());
    ll nMuni = 0, npn=0;
    each(x, compSizes) {
        ll diff = npn*x;
        nMuni += diff;
        npn += x;
    }

    ll r2 = max(Muni, nMuni);


    // Any directed graph G can be decomposed to a tree of strongly connected components
    // the number of bidirectional pairs is
    //  sum_{comp} ((|comp| choose 2))

    // given some value x, we would like to know if there exists a breakdown
    //  x = a1 + a2 + ... + ak
    // such that
    //  p = (a1 choose 2) + (a2 choose 2) + ... + (ak choose 2)
    //

    pr(nodes, r2);
    ln();
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
