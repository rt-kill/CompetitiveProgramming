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

ll n, m, k;
vvll adj, minDists;
ve<arr<ll, 3>> orders;

ll dp(int, int);

void initMinDists() {
    minDists.assign(all(adj));
    For(l, 1, n+1) {
        For(i, 1, n+1) For(j, 1, n+1) {
            ll ndist = minDists[i][l] + minDists[l][j];
            cmin(minDists[i][j], ndist);
            cmin(minDists[j][i], ndist);
        }
    }
}


// solution for pizzas [i-j) at time ct given we are at node 1
//  time when returned to node 1 is also provided
pll consume(int i, int j, ll ct) {
    ll res = 0;

    int cnode = 1;
    For(l, i, j) {
        ll st = orders[l][0], nnode = orders[l][1];
        ct = max(ct + minDists[cnode][nnode], st);
        /* ct += minDists[cnode][nnode]; */

        ll cost = ct - st;
        cmax(res, cost);

        cnode = nnode;
    }
    ct += minDists[cnode][1];

    return {res, ct};
}


// solution for last i pizzas given the current time is ct and we are at node 1
ll dpAux(int i, ll ct) {
    int j = upper_bound(all(orders), ct, [](auto l, auto r){ return l < r[2]; }) - orders.begin();

    if (j == k) return consume(i, j, ct).fi;
    if (i == j) return dp(i, j+1);

    ll p1 = dp(i, j+1);

    auto [p2, nt] = consume(i, j, ct);
    cmax(p2, dpAux(j, nt));

    ll res = min(p1, p2);
    return res;
}


// solution for last i pizzas given pizza j-1 just came out of the oven and we are at node 1
vvll mem;
ll dp(int i=0, int j=0) {
    if (i == k) return 0;
    cmax(j, i+1);
    if (mem[i][j] < 0)
        mem[i][j] = dpAux(i, orders[j-1][2]);

    return mem[i][j];
}

void solve() {
    re(n, m);
    adj.assign(n+1, vll(n+1, (LLONG_MAX>>1)));
    For(i, 1, n+1) adj[i][i] = 0;
    rep(m) {
        rdll(u, v, d);
        adj[u][v] = d, adj[v][u] = d;
    }
    initMinDists();

    re(k);
    rep(k) {
        rdll(s, u, t);
        orders.pb({s, u, t});
    }

    mem.assign(k+1, vll(k+1, -1));
    ll res = dp();
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
