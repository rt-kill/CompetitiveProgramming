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

#define rewv(a, x)  _re_(a); x.rsz(a); each(b, x) _re_(b);

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

ll const M = 998244353;

int n;

vll factMem;
ll fact(int a) {
    if (a == 0) return 1;
    while (factMem.size() <= a) factMem.pb(-1);
    if (factMem[a] < 0) factMem[a] = a*fact(a-1)%M;
    return factMem[a];
}

ll modpow(ll a, ll b) {
    if (b == 0) return 1;
    ll res = (b&1) ? a : 1;
    ll sub = modpow(a, b/2);
    res = res * sub % M * sub % M;
    return res;
}

ll moddiv(ll a, ll b) {
    if (b == 0) return 1;
    ll den = modpow(b, M-2);
    ll res = a*den%M;
    return res;
}

ll choose(int a, int b) {
    ll num = fact(a);
    ll den = fact(b)*fact(a-b)%M;
    ll res = moddiv(num, den);
    return res;
}

vll memory;
ll dp(int v=n) {
    if (v <= 2) return 1;
    if (memory[v] >= 0) return memory[v];

    ll res = 0;
    For(i, 1, v-1) { res = (res + 2ll*choose(v-1, i-1)%M*dp(i)%M*dp(v-i)%M)%M; }
    res = (res + choose(v-1, v-2)*dp(v-1)%M)%M;

    memory[v] = res;
    return memory[v];
}

void solve() {
    re(n);
    memory.assign(n+1, -1);

    // consider the following tree:
    //  the root node is the set of all vertices
    //  suppose some node is r-connected

    // suppose G is Blue connected
    //  let S be some maximal Red connected component of G
    //  any subset of S is assumed to be correct
    //  any strict superset of S will have a node with only blue edges
    //      - blue connected, not red connected

    // we remove the at least 1-edge restriction
    // dp(n) := solution to a graph with n vertices that is blue connected
    //  dp(n) = (n-1 choose 0)dp(1)dp(n-1) + (n-1 choose 1)dp(2)dp(n-2) + ... + (n-1 choose n-2)dp(n-1)dp(1)
    // Doesn't work: assumes there is only 1 red connected component

    // dp1(n) := solution to a graph with n vertices
    // dp2(n) := solution to a graph with n vertices with its color already chosen
    //  dp1(n) = 2*dp2(n)
    //      dp1(1) = 1
    //  dp2(n) = (n-1 choose 0)dp2(1)dp1(n-1) + (n-1 choose 1)dp2(2)dp1(n-2) + ... + (n-1 choose n-2)dp2(n-1)dp1(1)
    //      dp2(1) = 1
    //      dp2(2) = 1

    // dp(n) := solution to a graph with n vertices that is blue connected
    //  dp(n) = 2*(n-1 choose 0)dp(1)dp(n-1) + 2*(n-1 choose 1)dp(2)dp(n-2) + ... + 2*(n-1 choose n-3)dp(n-2)dp(2) + (n-1 choose n-2)dp(n-1)
    //  res = 2*dp(n)

    ll res = 2ll*dp(n)%M - 2ll;
    pln(res);
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
