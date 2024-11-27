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

ll n;
vll h, hpfx;
vll lh, rh;
void solve() {
    rewv(n, h);

    hpfx.assign(all(h));
    For(i, 1, n) hpfx[i] += hpfx[i-1];

    // when are we ready to castcade?
    //  if there exists a pivot ind such that
    //      for all i <= ind, h[i-1] <= h[i] - 1
    //      for all i >= ind, h[i+1] <= h[i] - 1

    // clearly if we can castcade, we will
    //  so what is the minimum number of mana needed to set up the above?

    // for some pivot i, what is the min mana needed to set up castcade about this pivot
    //  max(h[i-1] - (h[i] - 1), 0) +
    //  max( h[i-2] - ((^^) - 1), 0)

    // let pl[i] and pr[i] be the min mana needed to set up castcade for the left and right half respectively
    //  let j be the first index less than i such that h[j] < (h[i]-(i-j)) <-> h[j] - j < h[i] - i
    //      then pl[i] = (h[i-1] - (h[i]-1)) + (h[i-2] - (h[i] - 2)) + ... + (h[j+1] - (h[i] - (i-(j+1))) + pl[j]

    // to permit queries of j at moment i, we maintain a monotonically increasing dequeue of h[j] + j

    /* deque<pi> deck({{INT_MIN, -1}}); */


    map<ll, ll, greater<ll>> lmm;
    lmm[LLONG_MIN] = -1;
    lmm[h[0]] = 0;

    lh.assign(n, 0);
    for(ll i=1; i<n; ++i) {
        // first element with value < (h[i] - i)
        auto it = lmm.upper_bound(h[i] - i);
        ll j = it->se;

        // first element that can not be effected by castcade
        ll LB = max(i - h[i] - 1, -1ll);

        // lh[i] = (hpfx[i-1] - hpfx[j]) - (i-(j+1))*h[i] + (1 + 2 + ... + (i-(j+1)) + rh[j]
        if (j > LB)
            lh[i] = (hpfx[i-1] - hpfx[j]) - (i-(j+1))*h[i] + ((i-j)*(i-(j+1))/2) + lh[j];
        else if (LB < 0) // j=-1
            lh[i] = hpfx[i-1] - i*h[i] + (i*(i+1)/2);
        else
            lh[i] = hpfx[i-1] - (i-(LB+1))*h[i] + ((i-LB)*(i-(LB+1))/2);


        while(lmm.begin()->fi >= h[i]-i)
            lmm.erase(lmm.begin());
        lmm[h[i] - i] = i;
    }


    map<ll, ll, greater<ll>> rmm;
    rmm[LLONG_MIN] = n;
    rmm[h[n-1]] = n-1;

    rh.assign(n, 0);
    for(ll i=n-2; i>=0; --i) {
        // first element with value < (h[i] - i)
        auto it = rmm.upper_bound(h[i] - ((n-1) - i));
        ll j = it->se;

        // first element that can not be effected by castcade
        ll UB = min(i + h[i] + 1, (ll) n);

        // rh[i] = (hpfx[j-1] - hpfx[i]) - (j-(i+1))*h[i] + (1 + 2 + ... + (j-(i+1)) + rh[j]
        if (j < UB)
            rh[i] = (hpfx[j-1] - hpfx[i]) - (j-(i+1))*h[i] + ((j-i)*(j-(i+1))/2) + rh[j];
        else if (UB == n)
            rh[i] = (hpfx[n-1] - hpfx[i]) - ((n-1)-i)*h[i] + (((n-1)-i)*(((n-1)-i)+1)/2);
        else
            rh[i] = (hpfx[n-1] - hpfx[i]) - (UB-(i+1))*h[i] + ((UB-i)*(UB-(i+1))/2);

        while(rmm.begin()->fi >= h[i]-((n-1)-i))
            rmm.erase(rmm.begin());
        rmm[h[i] - ((n-1)-i)] = i;
    }

    ll res = LLONG_MAX;
    For(i, 0, n) {
        ll sub = (lh[i] + rh[i] + h[i]);
        cmin(res, sub);
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
