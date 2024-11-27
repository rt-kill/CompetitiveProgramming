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
ll x, y;
str at, bt;
vi a, b, pfx;

vi oih, oit, noh, nota;
vll dp;

void solve() {
    re(n, x, y, at, bt);
    each(c, at) a.pb(c == '1');
    each(c, bt) b.pb(c == '1');

    For(i, 0, n) if (b[i]) a[i] ^= 1, b[i] ^= 1;

    ll N = accumulate(all(a), 0);
    if (N == 0) { pln(0); return; }
    if (N&1) { pln(-1); return; }

    int z2 = 0;
    For(i, 0, n-1) z2 |= (a[i] == 0 && a[i+1] == 0);

    if (N == 2) {
        int i = find(all(a), 1) - a.begin(), j = a.rend() - find(rall(a), 1);

        ll res = x*(j - i);
        if (i+1 < j) cmin(res, y);
        if (z2) cmin(res, 2ll*y);

        pln(res);
        return;
    }

    partial_sum(all(a), back_inserter(pfx));

    // we may now assume that N ≥ 4
    ll res = y*(N/2);


    // this should be the last case to consider
    //  suppose we have the sequences of 1's, {si}
    //      if the left most sequence is of even order, we simply consume it
    //      if the left most sequence is of odd order, we reduce it to order 1
    //  we have two options:
    //      ignore the 1 that is left behind to eventually use a y operation on, or move it right to the next odd block
    //          suppose we have the intervals [i, i], [l1, r1], [l2, r2], ..., [lk, _]
    //      where lk is the first odd block
    //          the cost of moving to block lk would be
    //              x*((l1 - i - 1) + (l2 - r1 - 1) + ... + (lk - r{k-1} - 1)) = x*(nz[i:lk])
    //              plus some other consequences
    //          the cost of not moving to block lk would be y/2


    // first lest calculate oih (odd interval head)
    oih.assign(n, 0), oit.assign(n, 0), noh.assign(n, -1), nota.assign(n, -1);
    For(l, 0, n) {
        int r = l;
        while(r+1 < n && a[r+1]) ++r;
        if ((r - l + 1) & 1) {
            oih[l] = 1, oit[r] = 1;

            int i = l-1;
            while(i >= 0 && noh[i] == -1) {
                noh[i] = l;
                --i;
            }

            i = r-1;
            while(i >= 0 && nota[i] == -1) {
                nota[i] = r;
                --i;
            }
        };

        l = r;
    }

    // dp[i] := solution to a[i:]
    dp.assign(n+1, -1);
    dp[n] = 0, dp[n-1] = -1 * (a[n-1] != 0);
    Rof(i, 0, n-1) {
        int nc = ( i > 0 ) ? N - pfx[i-1] : N;
        if (nc&1) continue;

        if (a[i] == 0) { dp[i] = dp[i+1]; continue; }
        if (a[i] && a[i+1]) { dp[i] = x + dp[i+2]; continue; }

        int ch = i;
        while(noh[ch] != -1) {
            ch = noh[ch];
        }
    }




    if (x < y) {

    }


    // if N == 2 and the 1's in a are adjacent
    //      if ∃i, a[i] = a[i+1] = 0
    //          res = min(x, 2*y)
    //      else res = x
    // if N == 2 and the 1's in a are non-adj
    //      res = min(x*(j-i), y)
    //

    // if a has an odd number of 1's, not possible
    // if a has exactly two ones at i < j
    //      if (i+1 == j)   res = min(x, 2*y)
    //      else            res = min(x*(j-i), y)

    // we consider the continuous sequences of 1's in a
    //  if y < x, we would like to remove non-adj elements in a way that minimizes the size of the last continuous sequence (1.0)
    //      as long as there are more than one continuous sequence, we can always clear all values using only y



    // if there are at least four 1's, res = y*(N/2) is an option
    //      while there are at least two continuous sequences of size 2
    //          choose them
    //      if there is a continuous sequence of size 2,
    //          match it with an index of another set so that there are no more continuous sequences of size 2
    //              if sequence of size 1 exists, take it
    //              if sequence of size 3 exists, take its middle point
    //              if sequence of size ≥ 4 exists, take its first point
    //      over sequences of odd length, continue to match their first and last points
    //      over sequences of even length, continue to match each i with i+2


    // suppose y ≤ x and N ≥ 4
    //  res = y*(N/2) is optimal
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
