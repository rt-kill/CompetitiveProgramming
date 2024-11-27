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

int const M = 998244353;

ll modpow(ll a, ll b) {/*{{{*/
    if (b == 0) return 1;
    ll res = (b&1) ? a : 1;
    ll sub = modpow(a, b/2);
    res = res * sub % M * sub % M;
    return res;
}

vll factmem;
ll modfact(ll a) {
    if (factmem.sz == 0) factmem.pb(1);
    for(ll i = factmem.sz; i <= a; ++i) factmem.pb(factmem.back() * i % M);
    return factmem[a];
}

ll moddiv(ll a, ll b) {
    ll den = modpow(b, M-2);
    ll res = ll(a)*den % M;
    return res;
}

ll choose(ll a, ll b) {
    if (min(a, b) < 0 || b > a) return 0;
    ll num = modfact(a);
    ll den = modfact(b) * modfact(a - b) % M;
    ll res = moddiv(num, den);
    return res;
}/*}}}*/


int n;
vi a;

int Mv;
vi counts, primes;
void init_data() {
    Mv = *max_element(all(a));
    counts.assign(Mv+1, 0);
    each(v, a) ++counts[v];

    vi notPrime(Mv+1, 0);
    notPrime[1] = 1;
    for(ll i=2; i<=Mv; ++i) {
        if (notPrime[i]) continue;
        for(ll v=i*i; v<=Mv; v += i) notPrime[v] = 1;
    }

    For(i, 1, Mv+1)if (!notPrime[i] && counts[i] > 0) primes.pb(i);
}

// dp(i, j) := ∑{ partitions of size j of primes[i:] } ∏counts[p]
//           = ∑{ partitions of size j of primes[i:] that contain primes[i] } ∏counts[p]
//           + ∑{ partitions of size j of primes[i:] that dont primes[i] } ∏counts[p]
//           = counts[primes[i]] * dp(i+1, j-1) + dp(i+1, j)
// dp(i, 1)  = coutns[primes[i]] * 1 + dp(i+1, 1)
// dp(i, 0) := 1

vvll dpmem;
ll dp(int i, int j) {
    if (j == 0) return 1;
    if (i >= primes.sz) return 0;

    if (dpmem[i][j] < 0) {
        ll p1 = counts[primes[i]] * dp(i+1, j-1) % M;
        ll p2 = dp(i+1, j);
        dpmem[i][j] = (p1 + p2) % M;
    }

    return dpmem[i][j];
}


void solve() {
    re(n);
    a.rsz(2*n);
    each(v, a) re(v);
    init_data();

    // for even i, R[i] must be prime
    //  first count the number of unique primes among a, P
    // P choose 2 is the number of ways to choose the primes in our factorization
    //  for each selection, we have n! ways of assigning the remaining values as exponents
    //      let C[v] be the number of exponents that have value v
    //      to remove repeats, we take n!/(∏ (C[v]!))

    // This gives us the solution
    //      ∑{choice of n primes}( n!/(∏ C[v]!) )

    // for each factorization, if v is a prime C[v] = counts[v] - 1
    //      otherwise C[v] = counts[v]

    // let v be the smallest prime
    //      ∑{choice of n primes}( n!/(∏ C[v]!) )
    //      = ∑{choice of n primes including v}(n!/(∏ C[v]!)) + ∑{choice of n primes excluding v}(n!/(∏ C[v]!))

    // we can break a into three buckets
    //      B1 = primes that appear only once
    //      B2 = primes that appear multiple times
    //      B3 = non-primes

    // we have For(k, n-|B1|, min(|B2|, n)) {
    //      res += soluiton where we take exactly k primes from B2
    // }

    // let D := product of factorials of counts of values
    //      D := ∏counts[v]!
    // a solution were we take exactly k primes from B2 is
    //  ∑{choices of k vlaues from B2}( (∑{values in choice}coutns[v])(n!)/D )
    //  = ((n!)/D) ∑{choices of k vlaues from B2}( (∑{values in choice}counts[v]) )
    //  = ((n!)/D) ∑{v in B2}( counts[v] * (#choices v is in) )
    //  = ((n!)/D) ∑{v in B2}( counts[v] * (|B2|-1) choose k-1 )


    // res = ∑ { choices of n primes } ( permutations of unchosen elements / number of times each permutation is repeated )
    //     = ∑ { P } ( n! / ∏ (counts[v] - δ(v, P))! )
    //     = ∑ { P } ( n! / ( ∏ ( counts[v]! ) / ∏ ( counts[v]*δ(v, P) ) ) )
    //     = (n!/∏counts[v]!) * ∑ { P } ( ∏ ( δ(v, P) * counts[v] ) )


    ll num = modfact(n), den = 1;
    For(v, 1, Mv+1) den = den * modfact(counts[v]) % M;
    ll mult = moddiv(num, den);

    dpmem.assign(primes.sz+1, vll(n+1, -1));
    ll sum = dp(0, n);

    // XXX: Why does this different from (mult * sum) % M?
    ll res = mult * sum % M;
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
