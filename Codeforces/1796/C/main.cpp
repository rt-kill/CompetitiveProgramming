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

int const M = 998244353;

ll modpow(ll a, ll b) {/*{{{*/
    if (b == 0) return 1;
    ll res = (b&1) ? a : 1;
    ll sub = modpow(a, b/2);
    res = res * sub%M * sub%M;
    return res;
}

vll factMem;
ll fact(ll a) {
    if (a == 0) return 1;
    while(factMem.sz <= a) factMem.pb(-1);
    if (factMem[a] < 0) factMem[a] = a*fact(a-1)%M;
    return factMem[a];
}

ll moddiv(ll a, ll b) {
    ll den = modpow(b, M-2);
    ll res = a*den%M;
    return res;
}

ll choose(ll a, ll b) {
    ll num = fact(a);
    ll den = fact(b) * fact(a-b) % M;
    ll res = moddiv(num, den);
    return res;
}/*}}}*/

int l, r;
vi lbs, ubs;
void solve() {
    re(l, r);

    lbs.clear();
    lbs.pb(l);
    while(lbs.back()*2 <= r) lbs.pb(lbs.back()*2);
    int MPS = lbs.sz; // max size of beautiful set

    // so we can assume lbs.sz >= 2
    if (MPS == 1) {
        pr(MPS, r-l+1);
        return;
    }

    // in a maximal beautiful set s, s[i+1]/s[i] <= 3
    //  otherwise, for j>i, replace s[j] with s[j-1]*2 and we get a larger set
    // additionally, there is at most one term for which s[i+1]/s[i] = 3
    //  otherwise, since 3*3 >= 2*2*2, we can get a larger beautiful set

    // maximal beautiful sets are uniquely defined by their smallest term, and the position of i such that s[i+1]/s[i] = 3
    //      i=-1 for no 3

    // let k be some starting value
    //  there exists a beautiful set that starts with k if k*(1<<(MPS-1)) <= r
    //  there exists a beautiful set that starts with k and has a 3 if k*(1<<(MPS-2))*3 <= r

    ll NSN3 = r/(1 << (MPS-1)) - l + 1;
    ll NSW3 = r/((1 << (MPS-2))*3) - l + 1;

    ll res = NSN3;
    if (NSW3 > 0) res = (res + NSW3*(MPS-1)%M)%M;
    /* if (NSW3 >= 0) res = (res + NSW3*(MPS-1)%M)%M; */

    pr(lbs.sz, res);
    ln();
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
