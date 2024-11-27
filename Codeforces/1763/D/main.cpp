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

ll const M = 1e9+7;

ll fm[(int) 1e5] = {};
ll modfact(ll a) {
    if ( a == 0 ) return 1;
    if (fm[a] == 0) fm[a] = modfact(a-1) * a % M;
    return fm[a];
}

ll modpow(ll a, ll b) {
    if (b == 0) return 1;
    ll res = (b&1) ? a : 1;
    ll sub = modpow(a, b/2);
    res = res * sub % M * sub % M;
    return res;
}

ll moddiv(ll a, ll b) {
    ll den = modpow(b, M-2);
    ll res = a*den%M;
    return res;
}

ll choose(ll a, ll b) {
    if (a < 0) return 0;
    if (b < 0 || b > a) return 0;
    ll num = modfact(a);
    ll den = modfact(b) * modfact(a-b) % M;
    ll res = moddiv(num, den);
    return res;
}


ll n, i, j, x, y;
void solve() {
    re(n, i, j, x, y);

    // all elements between i and j must be between x and y
    //  there is a bijection between assignments and subsets of elements between x and y:
    //      each set has a unique assignment (either increasing or decreasing)
    //  so the problem becomse, how many b subsets are there of elements (x, y)
    //      this is ( (y - x - 1) choose (j - i - 1) )

    // if x > y, then k <= i
    //      any set of elements before x can be made to work
    //      some in more ways than others
    //
    // if x < y, then k >= j

    // what if we fix k?
    //  clearly the value at k must be n
    //      any partioning of elements into sets of size k-1 defines a unique bitonic permutation
    //      that is, there are (n-1 choose k-1) bitonic permutations

    // what if we fix k, and some value after k?
    //      fix index i > k with value x
    //  still the value at k must be n
    //      we must choose (i - k - 1) elements in the range (n, x)
    //      and (n - i) elements in the range(x, 1]
    //  any such selection defines a unique bitonic permutation
    // we can use a similar argument for fixed k and a fixed value before k

    // what if we fix k, and two values after k
    //      fix indices j > i > k with values y < x
    //          the answer is ( n-x-1 choose i-k-1 ) * ( x-y-1 choose j-i-1 ) * ( y-1 choose n-j-1 )


    // solve it assumming x != n && y != n
    if (x == n) {
        ll p1 = choose( x-y-1, j-i-1 );
        ll p2 = choose( y-1, n-j);
        ll res = (i > 1) ? p1 * p2 % M : 0;

        pln(res);
        return;
    } else if (y == n) {
        ll p1 = choose( y-x-1, j-i-1 );
        ll p2 = choose( x-1, i-1 );
        ll res = (j < n) ? p1 * p2 % M : 0;

        pln(res);
        return;
    }

    ll res = 0;
    if (x < y) {
        For(k, j+1, n) {
            ll p1 = choose( x-1, i-1 );
            ll p2 = choose( y-x-1, j-i-1 );
            ll p3 = choose( n-y-1, k-j-1 );
            ll diff = p1 * p2 % M * p3 % M;
            res = (res + diff)%M;
        }

        For(k, i+1, j) {
            // everything greater than y must be put in the range [i, j]

            // must choose j-k-1 points greater than y
            ll p1 = choose ( n-y-1, j-k-1 );

            // left over points that are greater than y
            //  these must all be taken
            ll missing = (n-y-1) - (j-k-1);

            // must choose k-i-1 unchoosen points greater than x
            //  minus extra 1 because we cant take y
            ll p2 = choose ( (n-x-1) - (j-k-1) - 1 - missing, k-i-1-missing );
            // must choose i-1 points less than x
            ll p3 = choose ( x-1, i-1 );
            // must choose n-j unchoosen points less than y
            //  minus extra 1 because we cant take x
            /* ll p4 = choose ( (y-1) - (i-1) - 1, n-j ); */
            ll p4 = 1;

            ll diff = p1*p2%M*p3%M*p4%M;

            res = (res + diff)%M;
        }

    } else if (x > y){
        For(k, 2, i) {
            ll p1 = choose( n-x-1, i-k-1 );
            ll p2 = choose( x-y-1, j-i-1 );
            ll p3 = choose( y-1, n-j );
            ll diff = p1 * p2 % M * p3 % M;
            res = (res + diff)%M;
        }

        For(k, i+1, j) {
            // everything greater than y must be put in the range [i, j]

            // must choose k-i-1 points greater than x
            ll p1 = choose ( n-x-1, k-i-1 );

            // left over points that are greater than y
            //  these must all be taken
            ll missing = (n-x-1) - (k-i-1);


            // must choose j-k-1 unchoosen points greater than y
            //  minus extra 1 because we cant take x
            ll p2 = choose ( (n-y-1) - (k-i-1) - 1 - missing, (j-k-1)-missing );
            // must choose n-j points less than y
            ll p3 = choose ( y-1, n-j );
            // must choose n-j unchoosen points less than y
            //  minus extra 1 because we cant take x
            /* ll p4 = choose ( (y-1) - (i-1) - 1, n-j ); */
            ll p4 = 1;

            /* pr(k, p1, p2, p3, p4, missing) */
            /* ln(); */


            ll diff = p1*p2%M*p3%M*p4%M;

            res = (res + diff)%M;
        }
    }

    pln(res);
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
