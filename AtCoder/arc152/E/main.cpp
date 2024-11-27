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

int N;
vi w;
void solve() {
    rewv(N, w);

    // balls can colide on non-integer cords
    //  time and movements are continuous

    // if we want, we can throw a ball of weight 0 at the start


    // some properties of x={1, 2, 3, ..., 2ⁿ-1}
    //  bit 0 is on in 2ⁿ/2 values, and off in 2ⁿ/2-1 values

    //  bit 1 is on in 2ⁿ/2 and off in 2ⁿ/2-1 values

    //  in general, bit i>0 turns on at 2^i, and off at 2^{i+1}
    //      off for 2^i seconds, then on for 2^i seconds, then off...

    //  the one exception is that we skip 0, so the first wait is only 2^i-1
    //      we can see that every bit i will turn off after 2ⁿ-1,
    //          so every bit is on in exactly 2ⁿ/2 and off in 2ⁿ/2-1

    // it follows that ⊕(w) = 2ⁿ-1


    // z=0 always satisfy the condition:
    // z=2ⁿ-1 never satisfys the condition:
    //  one of the end balls must not be 2ⁿ-1, and the xor of balls to its side is always positive
    //  so adding our weight, it will always move away

    // let L := w[1], and R := w[2ⁿ-1]
    //  if Z > (2ⁿ-1)^L^Z, L will only ever move left
    //  if Z > (2ⁿ-1)^R^Z, R will only ever move right

    // at any point in time, let i and j be balls with no balls between them
    //  we can see that R[i] = (2ⁿ-1)^L[j]

    // for any Z, there must be some ball that never changes direction (until balls stop)
    //      whenever two balls colide, one of them keeps its direction
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
