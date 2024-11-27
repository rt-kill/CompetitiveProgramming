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

int n, M;

ll modpow(int a, int b) {
    if (b == 0) return 1;
    ll res = (b&1) ? a : 1;
    ll sub = modpow(a, b/2);
    res = res * sub % M * sub % M;
    return res;
}

vll fm;
ll fact(ll a) {
    if (fm[a] < 0) fm[a] = a*fact(a-1)%M;
    return fm[a];
}

ll moddiv(int a, int b) {
    ll den = modpow(b, M-2);
    ll res = a*b%M;
    return res;
}

ll choose(ll a, ll b) {
    ll num = fact(a);
    ll den = fact(b)*fact(a-b)%M;
    ll res = moddiv(num, den);
    return res;
}


void solve() {
    re(n, M);
    fm.assign(3*n+1, -1);
    fm[0] = 1;

    // it is easy to prove that we only ever need at most 3 sorts
    //  lh, rh, lh will always sort the list
    //  rh, lh, rh will always sort the list

    // let p be an arbitray permutation and ip its inverse
    //  if ip[1] > 2n, then at least 2 sorts are needed
    //      the same follows for any i <= n
    //    more specifically, we will always need to do an lh sort after the first rh sort
    //  if ip[2n+1] <= n, then at least 2 sorts are needed
    //      the same follows for any i > 2n
    //    more specifically, we will always need to do an rh sort after the first lh sort
    //
    //  it clearly follows that if both are true, then 3 sorts are needed
    //      suppose that only one of them is true
    //  if ip[i] <= 2n for all i <= n
    //      only 2 sorts are needed, lh then rh
    //  if ip[i] > n for all i > 2n
    //      only 2 sorts are needed, rh then lh

    // unless elements from [1:n] or [2n:3n] are perfectly sorted, we will always need 2 sorts
    //  in the even of such an occurence, unless the list is already sorted, we will always need exactly one sort


    // so we have gotten somewhere:
    //  we will need 0 sorts if and only if the list is already sorted
    ll c0 = 1;

    //  we will need 1 sort if only if:
    //      [1:n] is already sorted, and the entier list is not
    //          this is equal to (2n)! - 1
    //      [2n+1:3n] is already sorted, and the entier list is not
    //          this is equal to (2n)! - 1
    ll c1 = ((2*fact(2*n) - fact(n)) - 1) % M;

    //  we will need 2 sorts if and only if:
    //      for some i<=n, ip[i] > 2n and for all j>2n, ip[j] > n
    //          sum_{i=1 -> n} (n choose i) * (2*n - i choose n)
    ll c2p1 = 0;
    For(i, 0, n+1) {
        c2p1 = (c2p1 + choose(n, n-i) * choose(n, i)% M * choose(2*n-i, n) % M) % M;
    }
    c2p1 = c2p1 * fact(n) % M * fact(n) % M * fact(n) % M;
    ll c2p2 = 2*choose(2*n, n)%M * fact(n)%M * fact(2*n) % M;

    ll c2 = (c2p2 - c2p1)%M;
    c2 += (c2 < 0)*M;
    c2 -= (c1 + c0);
    c2 += (c2 < 0)*M;

    //          (2n choose n) ways of picking buckets for j>2n
    //          n! ways of filling these buckets
    //          problem reduces to number of 2n permutations such that some i<=n, ip[i] > n
    //              (2n)! permutations
    //              n!*n! permutations for which this is not true
    //              answer is ((2n)! - n!*n!)
    //          (2n choose n)*(n!)*((2n)! - n!*n!)
    //
    //      for some j>2n, ip[j] <=n and for all i<=n, ip[i] <= 2n
    //          same as above
    /* ll c2p1 = (choose(2*n, n) * fact(n) % M); */
    /* ll c2p2 = (fact(2*n) - fact(n)*fact(n))%M; */
    /* c2p2 += (c2p2 < 0)*M; */
    /* ll c2 = 2*( c2p1 * c2p2 % M ) % M; */

    //  we will need 3 sorts if and only if:
    //      for some i<=n and some j>2n, ip[i] > 2n && ip[j] <= n
    //          this is harder to count
    //
    //
    //
    //      there are (3n)! total permutations
    //      this is not true for permutations where (1:n) are before 2n and (2n+1:3n) are after n
    //
    //          sum over number of buckets in [n+1:2n] to assign values of [1:n]
    //          (sum_{i=0 -> n} (n choose n-i)*(n choose i)*(n!) * {
    //                  sum_{j=0 -> n-i} (n choose n-j)*(n-i choose j)*(n!)
    //              }) * (n!)
    //
    //          we see that
    //              sum_{j=0 -> n-i} (n choose j)*(n-i choose j)
    //            = (n!)/(n-i)! * sum_{j=0 -> n-i} (n-i choose j)*(n-i choose j)
    //            = (n!)/(n-i)! * (2(n-i) choose n-i)
    //
    //  2*(2n choose n) * (n!) * (2n)!

    /* ll c3p1 = 0; */
    /* For(i, 0, n+1) { */
    /*     // we choose i of the middle buckets for the first n values */
    /*     // we have 2n-i buckets for the second j values */
    /*     ll tp1 = fact(n) * choose(n, n-i) % M * choose(n, i) % M; */
    /*     ll tp2 = fact(n) * choose(2*n - i, n) % M; */
    /*     c3p1 = ( c3p1 + tp1*tp2%M ) % M; */
    /* } */

    /* ll intct = fact(n) * c3p1 % M; */
    /* intct += (intct < 0)*M; */

    /* ll c3 = (fact(3*n) - 2*(choose(2*n, n) * fact(n) % M * fact(2*n) % M) + intct)% M; */
    /* c3 += (c3 < 0)*M; */

    ll c3 = (fact(3*n) - c0 - c1 - c2)%M;
    c3 += (c3 < 0)*M;

    pr(c0, c1, c2, c3);
    ln();

    ll res = (0*c0 + 1*c1 + 2*c2 + 3*c3)%M;
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
