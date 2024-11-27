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

int n, m, q;
vvi adj;
vpi qur;
vi res;

int bfs() {/*{{{*/
    queue<pi> q({ {0, 0} });
    vi dists(n, -1);

    while(q.sz) {
        auto [ u, d ] = q.front(); q.pop();

        if (dists[u] >= 0) continue;
        dists[u] = d;

        each(v, adj[u]) q.push({ v, d+1 });
    }

    int res = *max_element(all(dists));
    return res;
}/*}}}*/

void init() {/*{{{*/
    re(n, m, q);

    adj.assign(n, vi());
    rep(m) {
        rdi(u, v);
        --u, --v;

        adj[u].pb(v);
        adj[v].pb(u);
    }

    res.assign(q+1, -1);
    res[0] = bfs();

    qur.rsz(q+1);
    qur[0] = { -1, -1 };
    For(i, 1, q+1) {
        rdi(u, v);
        --u, --v;
        qur[i] = { u, v };

        adj[u].pb(v);
        adj[v].pb(u);
    }

    res[q] = bfs();
}/*}}}*/

void set_adj(int l, int r, int fg) {/*{{{*/
    int m = (l+r)/2;

    if (!fg) {
        For(i, l+1, m+1) {
            auto [u, v] = qur[i];
            adj[u].pb(v);
            adj[v].pb(u);
        }
    } else {
        Rof(i, m+1, r+1) {
            auto [u, v] = qur[i];
            adj[u].pop_back();
            adj[v].pop_back();
        }
    }
}

void reset_adj(int l, int r, int fg) {
    int m = (l+r)/2;

    if (!fg) {
        Rof(i, l+1, m+1) {
            auto [u, v] = qur[i];
            adj[u].pop_back();
            adj[v].pop_back();
        }

    } else {
        For(i, m+1, r+1) {
            auto [u, v] = qur[i];
            adj[u].pb(v);
            adj[v].pb(u);
        }
    }
}/*}}}*/


// if fg == 0, graph is at state l
// if fg == 1, graph is at state r
// res[l] and res[r] are already computed

void dnc(int l=0, int r=q, int fg=1) {
    if (r-l <= 1) return;
    if (res[l] <= 2*res[r]) {
        For(i, l+1, r) res[i] = res[l];
        return;
    }

    set_adj(l, r, fg);

    int m = (l+r)/2;
    res[m] = bfs();
    dnc(l, m, 1);
    dnc(m, r, 0);

    reset_adj(l, r, fg);
}

void solve() {
    init();
    dnc();
    each(v, res) pr(v);
    ln();
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
