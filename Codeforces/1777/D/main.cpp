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

int const M = 1e9+7;

int n;
vvi buff;
vvi adj;

ll fm[(int) 1e5 + 1] = {};
ll fact(int a) {
    if (a == 0) return 1;
    if (fm[a] == 0)
        fm[a] = a*fact(a-1)%M;
    return fm[a];
}

ll modpow(int a, int b) {
    if (b == 0) return 1;
    ll res = (b&1) ? a : 1;
    ll sub = modpow(a, b/2);
    res = res*sub%M*sub%M;
    return res;
}

ll moddiv(int a, int b) {
    ll den = modpow(b, M-2);
    ll res = a*den%M;
    return res;
}

ll choose(int a, int b) {
    ll num = fact(a);
    ll den = fact(b)*fact(a-b)%M;
    ll res = moddiv(num, den);
    return res;
}

void init_adj(int r=1, int p=0) {
    each(c, buff[r]) {
        if (c == p) continue;
        adj[r].pb(c);
        init_adj(c, r);
    }
}


void solve() {
    re(n);
    buff.rsz(n+1);
    rep(n-1) {
        rdi(u, v);
        buff[u].pb(v);
        buff[v].pb(u);
    }

    adj.rsz(n+1);
    init_adj();

    // suppose that R is the solution to some tree T
    //  if I add a leaf to a leaf and make (T'), how does R change?
    //      R -> (R + 0*States(T)) + (R + depth(l)*States(T))
    //  if I add x leaves to a leaf and make (T'),
    //      R -> (R + 0*States(T)) + (R + (nl) + depth(l)*(nl)*States(T)) + (R + 2*(nl choose 2) + 0*...) + ...

    // state of tree with 1 node
    ll res = 1;
    ll nodeCount = 1;
    queue<pi> q({{1, 1}});

    while(q.size()) {
        pr(nodeCount, res);
        ln();
        auto [l, d] = q.front(); q.pop();

        ll nc = adj[l].sz;
        ll tmp = 0;
        For(i, 0, nc+1) {
            ll parit = i&1;
            ll diff = (res*choose(nc, i)%M +
                    (i + parit*d)*choose(nc, i)%M*modpow(2, nodeCount)%M)%M;
            tmp = (tmp + diff)%M;
        }
        res = tmp;
        nodeCount += nc;

        each(c, adj[l])
            q.push({c, d+1});
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
