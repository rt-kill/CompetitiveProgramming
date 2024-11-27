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

int n;
ll h;
vll x;

// dp rec for l and r connectable
//  returns min cost to connect everything in the range [l,r]
ll mem1[300][300];
ll dp1(int l, int r) {
    if (l == r) return 0;
    if (mem1[l][r] >= 0) return mem1[l][r];
    ll res = LLONG_MAX;

    // bricks for a binary tree
    //  what is the optimal solution if [l,k] and [k+1,r] are the subtrees
    For(k, l, r) {
        ll left = dp1(l, k);
        ll right = dp1(k+1, r);

        ll lr = (x[k] - (x[l]+1)) - 1;
        ll ldh = (l != k) ? (lr+1)/2 + 1 : 0;
        ll lnx = x[l] + ldh;

        ll rr = (x[r] - (x[k+1]+1)) - 1;
        ll rdh = (r != (k+1)) ? (rr+1)/2 + 1 : 0;
        ll rnx = x[r] - rdh;

        ll matchCost = abs(ldh - rdh); // blocks needed to get them to the same height
        ll matchedRange = (rnx - (lnx + abs(ldh - rdh) + 1)) - 1; // range after they are at the same height (possibly -1?)
        ll mdh = (matchedRange + 1)/2 + 1; // correct with range -1

        ll connectCost = matchCost + 2*(mdh - 1) + 1;
        ll total = left + right + connectCost;

        cmin(res, total);
    }

    mem1[l][r] = res;
    return mem1[l][r];
}

// dp rec for any l and r
//  returns min solution for l, r
ll mem2[300][300];
ll dp2(int l, int r) {
    if (l > r) return 0;
    if (l == r) return h;
    if (mem2[l][r] >= 0) return mem2[l][r];
    ll res = LLONG_MAX;

    For(k, l, r+1) {
        ll range = (x[k] - (x[l]+1)) - 1;
        ll dh = (l != k) ? (range + 1)/2 + 1 : 0;
        if (dh > h) break;

        ll leftTop = dp1(l, k);
        ll leftGround = (h - dh);
        ll left = leftTop + leftGround;

        ll right = dp2(k+1, r);

        ll total = left + right;
        cmin(res, total);
    }

    mem2[l][r] = res;
    return mem2[l][r];
}



void solve() {
    re(n, h);
    x.rsz(n);
    each(v, x) re(v);

    For(l, 0, n) For(r, 0, n)
        mem1[l][r] = -1, mem2[l][r] = -1;

    ll res = dp2(0, n-1);
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
