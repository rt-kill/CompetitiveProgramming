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

int const M = 1e9+7;

ll modpow(ll a, ll b) {
    if (b == 0) return 1;
    ll res = (b&1) ? a : 1;
    ll sub = modpow(a, b/2);
    res = res*sub%M*sub%M;
    return res;
}

ll moddiv(ll a, ll b) {
    ll tmp = modpow(b, M-2);
    ll res = a*tmp%M;
    return res;
}

int n;
void solve() {
    re(n);

    ll fh = moddiv((1ll * n)*(n+1)%M*(2*n+1)%M, 6);
    ll sh = 1ll*n*n%M*(n-1)%M - 2*moddiv((1ll * (n-1))*(n)%M*(2*(n-1)+1)%M, 6);
    ll res = 2022ll*(fh + sh)%M;
    res += (res<0)*M;
    pln(res);

    // optimal path is r,d,r,d,r,d...

    // sum(1*1 + 2*2 + ... + n*n) = (n)(n+1)(2n+1)/6
    //

    // = sum(1*1 + 2*2 + ... + n*n) + sum(1*2, 2*3, ..., (n-1)*n)
    // sum(a1, a2, a3, ..., an) = a1 + (a1 + (a2-a1)) + (a1 + (a2 - a1) + (a3 - a2)) + ...
    //                          = n*a1 + (n-1)*(a2 - a1) + (n-2)*(a3 - a2) + ... + (an - a{n-1})
    //
    //  k*k - (k-1)*(k-1) = 2*k - 1
    //  sum(1*1, 2*2, ..., n*n) = n*1 + (n-1)*(3) + (n-2)*(5) + (n-3)*(7) + ... + (1)*(2n-1)
    //      = 2*(1*n + 2*(n-1) + 3*(n-2) + ... + (n)*(1)) - (n + n-1 + n-2 + ... + 1)
    //      = 2*(n + 2*n + 3*n + 4*n + ... + (n-1)*n) - 2*(1*0 + 2*1 + 3*2 + ... + n*(n-1)) - n*(n+1)/2
    //
    //  res = 2*(n + 2*n + 3*n + 4*n + ... + (n-1)*n)
    //          - (1*0 + 2*1 + 3*2 + ... + n*(n-1))
    //          - n*(n+1)/2
    //      = 2*n*n*(n-1)/2 - n*(n+1)/2
    //          -
    //
    //
    //  sum(1*2, 2*3, ..., (n-1)*n) = (n-1)*2 + (n-2)*4 + (n-3)*6 + ... + (1)*(2*(n-1))
    //      = 2*(n + 2*n + 3*n + ... + (n-1)*n) - 2*(1*1 + 2*2 + 3*3 + ... + (n-1)*(n-1))
    //      = 2*(n*(n*(n-1)/2) - ())

    //          terms = n + (n-1)
    //  sum(1*1, 1*2, 2*2, 2*3, 3*3, ..., n*n)
    //      = (2n - 1)*1 + (2n-2)*2 + (2n-3)*2 + (2n-4)*3 + (2n-5)*3 + ...
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
