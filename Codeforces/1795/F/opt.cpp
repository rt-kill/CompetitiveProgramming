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

int const N = 2e5;

int n, k;
vi adj[N];
int a[N];

int order[N], parent[N], rb;
int mxp[N], chip[N], moves[N];

void populate(int u=0, int p=0) {
    each(v, adj[u]) {
        if (v == p) continue;
        populate(v, u);
    }

    order[rb++] = u;
    parent[u] = p;
}

int flag(int m) {
    fill(mxp, mxp+n, 0);

    fill(chip, chip+n, -1);
    For(i, 0, k) chip[a[i]] = i;

    fill(moves, moves+k, m/k);
    For(i, 0, m - m/k*k) ++moves[i];

    For(i, 0, n) {
        int u=order[i], p=parent[u], cc=chip[u];

        if      (cc == -1)              cmax(mxp[p], mxp[u]+1);
        else if (moves[cc] <= mxp[u])   moves[cc]=0;
        else if (chip[p] == -1)         chip[p]=cc, --moves[cc];
    }

    int res = (reduce(moves, moves+k, 0, bit_or<int>{}) == 0);
    return res;
}

void solve() {
    re(n);
    fill(adj, adj+n, vi());
    rep(n-1) {
        rdi(u, v);
        --u, --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    rb = 0;
    populate();

    re(k);
    For(i, 0, k) { re(a[i]); --a[i]; }

    int l=0, r=(n-k);
    while(l < r) {
        int m = (l + r + 1)/2;
        int f = flag(m);

        if (f) l = m;
        else r = m-1;
    }

    int res = l;
    pln(res);

    // suppose the maximimum number of moves is M
    //      each chip was either moved (M+1)/k or M/k times
    //      the first M - M/k were moved (M+1)/k times, and the rest were only moved M/k times
    //  so we would like to find some sequence of moves (m1, m2, m3, ...) with i being the largest index of the min value for which
    //      mi - (k - i) is maximal

    // we root the tree arbitrarily (use 0)
    //  considering chips in decreasing order of depth
    //      at whenever we see a chip, we either move it up (if we can), or down to a subtree with no chips in it
    //          if we move a chip downwards, we will take the max length path

    // we if we already know the ammount of moves we would like the chip to make, these moves are forcing
    //      if the max path downards is at least the size of the moves, take it
    //      otherwise we must step upwards
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
