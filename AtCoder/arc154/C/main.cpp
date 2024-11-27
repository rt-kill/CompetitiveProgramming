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
vi a, b;
void solve() {
    re(n);
    rev(n, a);
    rev(n, b);

    if (inner_product(all(a), b.begin(), 1, logical_and{}, equal_to{})) { pln("Yes"); return; }


    //     _                _           _
    //    / \   _ __   __ _| |_   _ ___(_)___
    //   / _ \ | '_ \ / _` | | | | / __| / __|
    //  / ___ \| | | | (_| | | |_| \__ \ \__ \
    // /_/   \_\_| |_|\__,_|_|\__, |___/_|___/
    //                        |___/

    // We will assume that a ≠ b
    // Indices are always taken mod n

    // Definitions:
    //      SEAM:   a continuous segment, all of which has the same value
    //      TAIL:   an index i for which v[i] ≠ v[i+1]
    //      SET:    within the context of a transformation at a specific time, an index is set if its value will never change going forward
    //              alternatively, an index i is set if there exists a desired transformation that never changes i

    // Lemma: if a valid solution exists, b must have a seam of order at least 2
    //  any valid transformation has some last move, which generates a seam

    // Lemma: for any tail i, i must be set before i+1

    // Lemma: a transformation a->b exists iff a transformation a->a' for some a' in T(b) exists
    //  T(b) is the set of all arrays v such that for all tails in b, v[i] = b[i]

    // Statement: if a transformation a->b exists, then a transformation a->b exists such that
    //      whenever we preform an operation i, if i+1 is not set (with respect to this transformation), the next transformation is i+1
    // PROOF:
    //      whenever we preform an operation i, a[i] becomes a[i+1]
    //          until a[i+1] changes, operations i have no impact
    //              that is, if a[i+1] will eventually change, until it changes its value does not matter
    //              so there is no harm in preforming operation (i+1)
    //          if a[i+1] is not set, its value will eventually change

    // Statement:   if a transformation a->b exists, then after some "rotation", a value in a is set
    // PROOF:       take a transformation as stated above

    // Statement: after a k-"rotation" about some s (defines a seam)
    //  if this rotation sets some value i
    //      tails of b appear in order after their index in a
    //      that is, there exists some sequence of indices v for which
    //          v[i] >= t[i]
    //          a[v[i]] == b[t[i]]
    //          v[i] < v[i+1]
    //          v[i] < (s-1)

    // Corrollary: if a transformation a->b exists, then for some
    //  sequence of intervals [l, r] such that
    //      0 <= l[i] < l[i+1], r[i] < r[i+1]
    //      r[-1] - l[0] <= n-3
    //  the transformation
    //      each(interval) Rof(i, l, r) op(i)
    //      Rof(i, r[-1]+1, l[0]-1) op(i)
    //  will make a and b equivilent under cyclic shifts

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
