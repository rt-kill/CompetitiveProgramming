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

ll n, m, p;
vll w;
vvpll adj;
vvll mds;
vll mps;

void solve() {
    re(n, m, p);
    rev(n, w);

    adj.assign(n, vpll());
    rep(m) {
        rdi(a, b, s);
        --a, --b;
        adj[a].pb({b, s});
    }

    mds.assign(n, vll());
    For(i, 0, n) {
        priority_queue<pll, vpll, greater<pll>> pq;
        pq.push({ 0, i });

        vll cmds(n, -1);
        while(pq.sz) {
            auto [ d, u ] = pq.top(); pq.pop();

            if (cmds[u] >= 0) continue;
            cmds[u] = d;

            for( auto [ v, dd ] : adj[u] ) pq.push({ d + dd, v });
        }

        mds[i].assign(all(cmds));
    }

    if (mds[0][n-1] == -1) { pln(-1); return; }

    mps.assign(n, -1);

    auto myComp = [](auto l, auto r){ return (l[0] > r[0]) || (l[0] == r[0] && l[1] < r[1]); };
    priority_queue<arr<ll, 3>, ve<arr<ll, 3>>, decltype(myComp)> pq(myComp);
    pq.push({ 0, p, 0 });

    while(pq.sz) { // O(e + nlog(n))
        auto [ np, cc, u ] = pq.top(); pq.pop();

        if (mps[u] >= 0) continue;
        mps[u] = np;

        For(v, 0, n) if ((mds[u][v] >= 0) && (v == n-1 || w[v] > w[u])) {
            if (mds[u][v] <= cc) pq.push({ np, cc - mds[u][v], v });
            else {
                ll rp = (mds[u][v] - cc + (w[u] - 1))/w[u];
                pq.push({ np + rp, cc + w[u]*rp - mds[u][v], v });
            }
        }
    }

    pln(mps[n-1]);
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
