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

int n, m;
vvi heights;

// sparse[r][c][k] = min(square(r, c, (1<<k)))
ve<ve<ve<int>>> sparse;
vi lp2;
void init_sparse() {
    lp2.assign(m+1, 0);
    For(i, 1, m+1) {
        if (i == (i&-i)) lp2[i] = __builtin_ctz(i);
        else lp2[i] = lp2[i-1];
    }

    sparse.assign(n, vvi(m, vi(lp2[m]+1)));
    For(r, 0, n) For(c, 0, m)
        sparse[r][c][0] = heights[r][c];

    For(k, 0, lp2[m]) {
        For(r, 0, n) For(c, 0, m) {
            int tls = sparse[r][c][k];
            int bls = ((r + (1<<k)) < n) ? sparse[r+(1<<k)][c][k] : INT_MAX;
            int ls = min(tls, bls);

            int trs = ((c + (1<<k)) < m) ? sparse[r][c+(1<<k)][k] : INT_MAX;
            int brs = (((r + (1<<k)) < n) && ((c + (1<<k)) < m)) ? sparse[r+(1<<k)][c+(1<<k)][k] : INT_MAX;
            int rs = min(trs, brs);

            sparse[r][c][k+1] = min(ls, rs);
        }
    }
}

int query_sparse(int r, int c, int k) {
    if (r+k > n || c+k > m) return -1;

    int e = lp2[k];
    int diff = k - (1<<e);

    int tls = sparse[r][c][e];
    int bls = sparse[r+diff][c][e];
    int ls = min(tls, bls);

    int trs = sparse[r][c+diff][e];
    int brs = sparse[r+diff][c+diff][e];
    int rs = min(trs, brs);

    return min(ls, rs);
}

void solve() {
    re(n, m);
    heights.assign(n, vi(m));
    each(row, heights) each(square, row)
        re(square);

    init_sparse();

    int l = 1, r = n;
    while(l < r) {
        int mid = (l+r+1)/2;

        int flag = 0;
        For(r, 0, n) For(c, 0, m) {
            int v = query_sparse(r, c, mid);
            flag |= (v >= mid);
        }

        if (flag) l = mid;
        else r = mid-1;
    }

    int res = l;
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
