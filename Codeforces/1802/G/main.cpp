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

int const Mod = 1e9+7;

ll modpow(int a, int b) {/*{{{*/
    ll res = 1;
    for(ll ce=1, cp=a; ce <= b; ce<<=1, cp = cp*cp%Mod)
        if (b & ce) res = res*cp%Mod;
    return res;
}

ll moddiv(int a, int b) {
    ll num = a, den = modpow(b, Mod-2);
    ll res = num*den%Mod;
    return res;
}/*}}}*/

int const N = 2e5; // same as M
int const Log = 18;

int n, m;
int P[N];
int L[N], R[N];
arr<int, 4> iq[N];
int res[N];

int dep[N];
int sp[N][Log];
ve<arr<int, 4>> nq[N];

int ds[2*N][Log], cc[2*N][Log];
ll prod;


void read_input() {/*{{{*/
    cin >> n;

    P[0] = 0;
    For(i, 1, n) cin >> P[i], --P[i];
    For(i, 0, n) cin >> L[i] >> R[i];

    cin >> m;
    For(i, 0, m) {
        auto& [a, b, c, d] = iq[i];
        re(a, b, c, d);
        a--, b--, c--, d--;
    }
}/*}}}*/

void pop_dep(int r) {/*{{{*/
    if (dep[r] >= 0) return;
    pop_dep(P[r]);
    dep[r] = dep[P[r]] + 1;
}

void pop_sp() {
    For(i, 0, n) sp[i][0] = i;
    For(j, 0, Log-1) For(i, 0, n)
        sp[i][j+1] = sp[P[sp[i][j]]][j];
}

int pa(int u, int k) {
    int res = u;
    for(int tk=k; tk>0; tk-=(tk&-tk)) {
        int nz = __builtin_ctz(tk&-tk);
        res = P[sp[res][nz]];
    }
    return res;
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    u = pa(u, dep[u] - dep[v]);

    int cu=u, cv=v;
    Rof(i, 0, Log) {
        while(sp[cu][i] != sp[cv][i]) {
            cu = P[sp[cu][i]];
            cv = P[sp[cv][i]];
        }
    }

    int res = cu; // = cv
    return res;
}/*}}}*/

void preprocess_queries() { // nq: { h1, h2, l2k, rev } {{{
    fill(dep, dep+n, -1);
    dep[0] = 0;
    For(i, 1, n) pop_dep(i);

    pop_sp();

    For(i, 0, m) {
        nq[i].clear();

        auto [ a, b, c, d ] = iq[i];
        int lca1 = lca(a, b), lca2 = lca(c, d);

        if (dep[a] - dep[lca1] < dep[c] - dep[lca2])
            swap(a, c), swap(b, d), swap(lca1, lca2);

        int l1 = dep[c] - dep[lca2];
        int l2 = dep[a] - dep[lca1] - l1;
        int l3 = dep[b] - dep[lca1];

        int m1 = pa(a, l1);
        int m2 = pa(d, l3);

        ve<arr<int, 4>> tmp;
        tmp.pb({ a, c, l1+1, 0 });
        tmp.pb({ m1, m2, l2+1, 1 });
        tmp.pb({ b, d, l3+1, 0 });

        for( auto [ h1, h2, k, rev ] : tmp ) {
            if (!rev) {
                int ch1=h1, ch2=h2;
                for(int tk=k; tk>0; tk-=(tk&-tk)) {
                    int nz = __builtin_ctz(tk&-tk);
                    nq[i].pb({ ch1, ch2, nz, 0 });
                    ch1=P[sp[ch1][nz]], ch2=P[sp[ch2][nz]];
                }

            } else {
                int ch1=h1;
                stack<pi> stak;
                for(int tk=k; tk>0; tk-=(tk&-tk)) {
                    int nz = __builtin_ctz(tk&-tk);
                    stak.push({ ch1, nz });
                    ch1=P[sp[ch1][nz]];
                }

                int ch2 = h2;
                while(stak.sz) {
                    auto [ ph1, nz ] = stak.top(); stak.pop();
                    nq[i].pb({ ph1, ch2, nz, 1 });
                    ch2=P[sp[ch2][nz]];
                }
            }
        }
    }

}
/*}}}*/

int find(int u, int k=0) {/*{{{*/
    if (ds[u][k] != ds[ds[u][k]][k]) ds[u][k] = find(ds[u][k], k);
    return ds[u][k];
}

int get_range(int u) {
    int r = find(u);
    return (L[r] <= R[r]) ? (R[r] - L[r] + 1) : 0;
}

void init_ds() {
    For(i, 0, 2*n) For(j, 0, Log)
        ds[i][j] = i, cc[i][j] = 1;
    For(i, n, 2*n) ds[i][0] = i-n;

    prod = 1;
    For(i, 0, n) prod = prod * get_range(i) % Mod;
}

queue<arr<int, 4>> merge_queue;
void merge() {
    ll num=1, den=1;

    while(merge_queue.sz) {
        auto [h1, h2, l2k, rev] = merge_queue.front(); merge_queue.pop();
        int rh1 = find(h1, l2k), rh2 = find(h2 + rev*n, l2k);
        if (rh1 == rh2) continue;

        if (cc[rh1][l2k] < cc[rh2][l2k]) swap(rh1, rh2);

        if (l2k > 0) {
            int m1 = P[sp[h1][l2k-1]], m2 = P[sp[h2][l2k-1]];

            if (!rev) {
                merge_queue.push({ h1, h2, l2k-1, 0 });
                merge_queue.push({ m1, m2, l2k-1, 0 });

            } else {
                merge_queue.push({ h1, m2, l2k-1, 1 });
                merge_queue.push({ m1, h2, l2k-1, 1 });
            }

        } else {
            den = den * get_range(rh1) % Mod * get_range(rh2) % Mod;

            L[rh1] = max(L[rh1], L[rh2]);
            R[rh1] = min(R[rh1], R[rh2]);
            num = num * get_range(rh1) % Mod;
        }

        ds[rh2][l2k] = rh1;
        cc[rh1][l2k] += cc[rh2][l2k];
    }

    prod = moddiv(prod * num % Mod, den);
}/*}}}*/


void solve() {
    read_input();
    preprocess_queries();
    init_ds();

    For(i, 0, m) {
        each(qur, nq[i]) merge_queue.push(qur);
        merge();
        res[i] = prod;
    }

    For(i, 0, m) cout << res[i] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

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
