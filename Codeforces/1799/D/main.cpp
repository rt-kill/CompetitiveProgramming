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

int t, tes;
int n, k;
int a[(int) 3e5];
ll cold[(int) 3e5], hot[(int) 3e5];
ll dp[(int) 3e5], mins[(int) 3e5];

int head[(int) 3e5];
ll pfx[(int) 3e5];

inline ll singleCost(int i, int j) {
    if ( j < i ) return 0;
    ll res = (i > 0) ? pfx[j] - pfx[i-1] : pfx[j];
    res += (!head[i])*(cold[a[i]] - hot[a[i]]);
    return res;
}


// dp[i] := solution to a[i:] given that a[i-1] was the last process to run on 2 and a[i] runs on 1
//      if process j>i is the next process to run on processor 2:
//          dp(i) = dp(j) + ( a[j] == a[i-1] ) * (hot[j] - cold[j]) + cost(i, j-1)


// for j such that (a[j] != a[i-1]), we would like to query
//  min{j > i}( dp(j) + cost(i, j-1) )
//  = min{j > i}( dp(j) + cost(i, j-1) - cost(i, n-1) ) + cost(i, n-1)
//  = min{j > i}( dp(j) + cost(k, j-1) - cost(k, n-1) ) + cost(i, n-1)
//      for all k < i
//  = min{j > i}( dp(j) + cost(0, j-1) - cost(0, n-1) ) + cost(i, n-1)


ll myAnswers[(int)1e5];

void solve() {
    re(n, k);
    For(i, 0, n) { re(a[i]); --a[i]; }
    For(i, 0, k) { re(cold[i]); }
    For(i, 0, k) { re(hot[i]); }

    fill(head, head+n, 0);
    fill(pfx, pfx+n, 0);

    head[0] = 1, pfx[0] = cold[a[0]];
    For(i, 1, n) {
        head[i] = (a[i] != a[i-1]);
        pfx[i] = head[i] ? cold[a[i]] : hot[a[i]];
        pfx[i] += pfx[i-1];
    }


    fill(dp, dp+n, 0);
    fill(mins, mins+k, LLONG_MAX);
    ll mainMin;

    dp[n-1] = cold[a[n-1]];
    mins[a[n-1]] = dp[n-1] + pfx[n-2] - pfx[n-1];
    mainMin = mins[a[n-1]];

    Rof(i, 0, n-1) {
        ll s1 = mainMin + singleCost(i, n-1);

        ll s2 = LLONG_MAX;
        if (i > 0 && mins[a[i-1]] < LLONG_MAX)
            s2 = mins[a[i-1]] + singleCost(i, n-1) - (cold[a[i-1]] - hot[a[i-1]]);

        ll s3 = singleCost(i, n-1);

        ll res = min(s1, min(s2, s3));
        dp[i] = res;

        ll uv = res + pfx[i-1] - pfx[n-1];
        cmin(mainMin, uv);
        cmin(mins[a[i]], uv);
    }

    myAnswers[t] = dp[0];
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    /* cout << fixed << setprecision(6); */
    cin >> tes;

    for (t=0;t<tes;t++) solve();
    For(i, 0, t) cout << myAnswers[i] << endl;

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
