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

int n;
void solve() {
    re(n);

    if (!(n&1)) {
        cout << "no" << '\n';
        return;
    }

    ll c = (3*n + 1)/2;

    cout << "yes" << '\n';
    For(i, 1, n+1) {
        int v = c+i;
    }

    // {c+1, c+2, ..., c+n} = {(a1+b1), (a2+b2), ...}
    //  sl = n*c + n*(n+1)/2
    //  sr = 2n(2n+1)/2

    // a solution can only exist if c exists
    //  that is if n(2n+1) - n(n+1)/2 is divisible by n

    // 2*c = c2
    /* ll c2 = 3*n + 1; */
    /* if (c2&1) { */
    /*     pln("no"); */
    /*     return; */
    /* } */
    /* ll c = c2/2; */

    /* if (n == 1) { */
    /*     pln("yes"); */
    /*     pr(1, 2); */
    /*     ln(); */
    /*     return; */
    /* } */


    /* // odd+odd and even+even are even */
    /* //  odd+even is odd */
    /* //  half of values should be odd+even */
    /* //  other half should be odd+odd or even+even */

    /* // [(a1, b1), (a2, b2), ..., (an, bn)] */

    /* // [(a1, b1), (a1-x, b1+x+1), (a1-y, b1+y+2)] */

    /* // [(a, b), (a-1, b+2), (a+1, b+1), (a-2, b+4), (a+2, b+3)] */

    /* vpi res = {{0, 0}}; */
    /* int mf=INT_MAX, Ms=INT_MIN; */
    /* For(i, 2, n+1) { */
    /*     int ld = -((i+1)&1)*(i/2) + (i&1)*(i/2); */
    /*     int rd = ((i+1)&1)*i + (i&1)*(i-2); */

    /*     cmin(mf, ld); */
    /*     cmax(Ms, rd); */

    /*     res.pb({ld, rd}); */
    /* } */

    /* int a = 1 - mf, b = 2*n - Ms; */
    /* each(re, res) { */
    /*     re.fi += a; */
    /*     re.se += b; */
    /* } */

    /* set<int> seen; */
    /* /1* int mv=a, Mv=b; *1/ */
    /* each(re, res) { */
    /*     /1* cmin(mv, re.fi); *1/ */
    /*     /1* cmin(mv, re.se); *1/ */
    /*     /1* cmax(Mv, re.fi); *1/ */
    /*     /1* cmax(Mv, re.se); *1/ */
    /*     if (seen.count(re.fi)) { */
    /*         pln("no"); */
    /*         return; */
    /*     } */
    /*     seen.insert(re.fi); */

    /*     if (seen.count(re.se)) { */
    /*         pln("no"); */
    /*         return; */
    /*     } */
    /*     seen.insert(re.se); */
    /* } */

    /* pln("yes"); */
    /* each(re, res) { */
    /*     pr(re.fi, re.se); */
    /*     ln(); */
    /* } */
    /* pln("MYTEST"); */
    /* pln(res.sz); */
    /* pln(seen.sz); */

    /* pln("MYTEST"); */
    /* pr(2*n, mv, Mv); */

    // 2*(c+n) = 5*n + 2
    //  c+n = 5*(n/2) + 1
    //      = an + bn
    //      = bn >= 5*n/4 + 1/2
    //           > n

    // (c+1) = 3*n + 2
    //  n is odd, so this is odd
    //

    // what if i can solve it for n-2?





    // rsum == nsum <=>
    //  3n^3 == 2n^2 + n
    //  <=> 3n^2 - 2n - 1 == 0
    //  <=> n == 1

    // the matched pairs will form a geometric series
    //  that is, they will be of the form
    //      {c+1, c+2, ..., c+n}
    //      and their sum will be (2*c+n+1)*(n)/2
    //          = n*c + n(n+1)/2
    //          = (2n+1)*(2n)/2 = 2*(n+n+1)(n)/2
    //          = 2n(n)/2 + 2(n+1)(n)/2
    //          -> n*c = n^2 + (n+1)(n)/2

    // a solution can only exist if
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
