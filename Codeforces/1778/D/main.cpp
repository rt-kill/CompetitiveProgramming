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

#define _rdi_(a)    int a; re(a)
#define rdi(...)    FOR_EACH(_rei_, __VA_ARGS__)

#define _rdll_(a)   ll a; re(a)
#define rdll(...)   FOR_EACH(_rell_, __VA_ARGS__)

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

int const M = 998244353;


ll modpow(ll a, ll b) {
    if (b == 0) return 1;
    ll res = (b&1) ? a : 1;
    ll sub = modpow(a, b/2);
    res = res * sub % M * sub % M;
    return res;
}

ll moddiv(ll a, ll b) {
    if (b == 0) cout <<"ERRRRRRRR" << '\n';
    ll tmp = modpow(b, M-2);
    ll res = a*tmp%M;
    return res;
}



int n;
str a, b;
void solve() {
    re(n, a, b);

    // We are working over the space good of flip sequences such that no strict subsequence is good
    // Let X be the random variable that maps an element of this space to len(S)
    //  Let Xi be the random variable that maps sequences of length i to 1, and the rest to 0

    // EV[X] = EV[X1 + 2*X2 + 3*X3 + ...]
    //       = EV[X1] + 2EV[X2] + ...
    //  EV[Xi] =
    //
    // Let Ri be the random variable that maps S to len(S) if S has i repeat flips, and 0 otherwise
    // EV[X] = EV[R0] + EV[R1] + EV[R2] + ...
    //  EV[R0] = k!/n^k where k is the diff between a and b

    // We might as well assume that B is all zeros
    // With this, we can represent a as just the number of ones in it (order does not matter)
    // EV[k] = k/n * (EV[k-1] + 1) + (n-k)/n * (EV[k+1] + 1)
    //  = k/n * (k-1)/n * (EV[k-2] + 2) + k/n * (n-k-1)/n * EV[k] + (n-k)/n*(k+1)/n*EV[k] + (n-k)/n*(n-(k+1))/n(EV[k+2]+2)
    //  = 1/n^2 (
    //      k(k-1)(EV[k-2] + 2) +
    //      (k(n-k-1) + (n-k)(k+1) == (2k(n-k-1) + n)) EV[k] +
    //      (n-k)(n-k-1)(EV[k+2] + 2)
    //  )

    // EV[0] = 0
    // EV[1] = 1/n + (n-1)/n(EV[2] + 1) = 1 + EV[2]
    // EV[2] = 2/n + 2/n*EV[1] + (n-2)/n EV[3]
    //      = 2/n + 2/n + 2/n*EV[2] + (n-2)/n * EV[3]
    //      = (1/(n-2)) * (4 + (n-2)EV[3]);
    // ...
    // EV[n-1] = R1 + (p1/q1) EV[n] = R2 + (p2/q2) EV[n-1]

    vll off(n+1), mult(n+1);
    off[0] = 1, mult[0] = 1;

    For(i, 1, n) {
        // EV[i] = 1 + bp/n EV[i-1] + fp/n EV[i+1]
        //       = 1 + bp/n ( off[i-1] + mult[i-1] EV[i] ) + fp/n EV[i+1]
        // (1-(bp/n)*mult[i-1]) EV[i] = 1 + bp/n*off[i-1] + fp/n EV[i+1];
        //
        // EV[i] = (1/(1 - (bp/n)*mult[i-1])) *  (bp/n * off[i-1] + fp/n * EV[i+1])

        ll bp = i, fp = n-i;

        /* ll den = (1ll - (moddiv(bp, n)*mult[i-1]%M)) + M; */
        ll den = (moddiv(n - bp*mult[i-1]%M, n));
        den += (den < 0)*M;

        off[i] = moddiv((1 + moddiv(bp, n)*off[i-1])%M, den);
        mult[i] = moddiv(moddiv(fp, n), den);
    }

    // EV[n-1] = 1 + (n-1)/n * EV[n-2] + 1/n*(EV[n])
    //


    vll ev(n+1);
    // EV[n-1] = off[n-1] + mult[n-1] EV[n] = off[n-1] + mult[n-1] * (EV[n-1] + 1)
    //      = off[n-1] + mult[n-1] + mult[n-1]*EV[n-1]
    // EV[n-1] = 1/(1 - mult[n-1]) * (off[n-1] + mult[n-1])

    ev[n] = 0;

    Rof(i, 0, n)
        ev[i] = (off[i] + mult[i]*ev[i+1]%M)%M;

    int k=n;
    For(i, 0, n) k -= (a[i] != b[i]);
    /* each(v, ev) pr(v); */
    /* ln(); */
    pln(ev[k]);
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
