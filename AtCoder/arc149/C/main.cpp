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

#define INF     INFINITY
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

#define lb lower_bound
#define ub upper_bound

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

#define pln(...)        pr(__VA_ARGS__); cout << '\n';

#define _peln_aux_(a)    cout << a << '\n';
#define _peln_(...)      FOR_EACH(_peln_aux_, __VA_ARGS__)
#define peln(...)        _pln_(__VA_ARGS__)

/* IO - Helpers {{{*/
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
vvi res;
void solve() {
    re(n);
    res.assign(n, vi(n));

    if (n == 3) {
        cout << 2 << ' ' << 4 << ' ' << 5 << '\n';
        cout << 8 << ' ' << 6 << ' ' << 3 << '\n';
        cout << 1 << ' ' << 9 << ' ' << 7 << '\n';
        return;
    }

    if (n == 4) {
        pln(15, 11, 16, 12);
        pln(13, 3, 6, 9);
        pln(14, 7, 8, 1);
        pln(4, 2, 10, 5);
        return;
    }

    if (n == 5) {
        pln(2, 4, 18, 16, 9);
        pln(20, 22, 24, 14, 11);
        pln(6, 8, 10, 12, 21);
        pln(19, 17, 15, 13, 1);
        pln(3, 5, 7, 23, 25);
        return;
    }

    int ub = n*n;
    vi seen(ub);

    // if n*n/6 >= n ↔ n >= 6
    //      divide the evens and odds with the evens and odds divisible by 3

    int cb=0;
    for(int cv=2; cv<=ub; cv+=2) {
        if (cv/6*6 == cv) continue;
        int r = cb/n, c=cb%n;
        res[r][c] = cv;
        ++cb;
    }

    for(int cv=6; cv<=ub; cv+=6) {
        int r = cb/n, c=cb%n;
        res[r][c] = cv;
        ++cb;
    }

    for(int cv=3; cv<=ub; cv+=6) {
        int r = cb/n, c=cb%n;
        res[r][c] = cv;
        ++cb;
    }

    for(int cv=1; cv<=ub; cv+=2) {
        if (cv/3*3 == cv) continue;
        int r = cb/n, c=cb%n;
        res[r][c] = cv;
        ++cb;
    }

    For(r, 0, n) {
        For(c, 0, n) pr(res[r][c]);
        ln();
    }
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
