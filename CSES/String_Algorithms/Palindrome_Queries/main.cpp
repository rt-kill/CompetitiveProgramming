#include <bits/stdc++.h>
using namespace std;

/* Macros {{{ */
/* Basics {{{ */
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ii = pair<int,int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvll = vector<vll>;
using vvii = vector<vii>;

#define arr array
#define ve vector
#define pb push_back
#define rsz(a) resize(a)
#define mp make_pair
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define sz size()

#define For(i, a, b) for(int i=a; i<b; ++i)
#define Rof(i, a, b) for(int i = (b)-1; i >= (a); --i)
#define rep(a) For(_, 0, a)
#define each(a, x) for (auto &a : x)
#define reach(a, x) for (auto a = x.rbegin(); a != x.rend(); ++a)

template<typename T, typename U> inline void cmin(T &x, U y) { if(y < x) x = y; }
template<typename T, typename U> inline void cmax(T &x, U y) { if(x < y) x = y; }
/*}}}*/

/* IO {{{ */
#define _re_(a) cin >> a;
#define re(...) FOR_EACH(_re_, __VA_ARGS__)

#define _red_(a) int a; cin >> a;
#define red(...) FOR_EACH(_red_, __VA_ARGS__)

#define _pr_(a) cout << a << ' ';
#define pr(...) FOR_EACH(_pr_, __VA_ARGS__)

#define _prln_(a) cout << a << '\n';
#define prln(...) FOR_EACH(_prln_, __VA_ARGS__)
#define pln(...) FOR_EACH(_prln_, __VA_ARGS__)

/* IO - Helpers {{{*/
#define PARENS ()
#define EXPAND(arg) EXPAND1(EXPAND1(EXPAND1(EXPAND1(arg))))
#define EXPAND1(arg) EXPAND2(EXPAND2(EXPAND2(EXPAND2(arg))))
#define EXPAND2(arg) EXPAND3(EXPAND3(EXPAND3(EXPAND3(arg))))
#define EXPAND3(arg) EXPAND4(EXPAND4(EXPAND4(EXPAND4(arg))))
#define EXPAND4(arg) arg

#define FOR_EACH(macro, ...)                                    \
  __VA_OPT__(EXPAND(FOR_EACH_HELPER(macro, __VA_ARGS__)))
#define FOR_EACH_HELPER(macro, a1, ...)                         \
  macro(a1)                                                     \
  __VA_OPT__(FOR_EACH_AGAIN PARENS (macro, __VA_ARGS__))
#define FOR_EACH_AGAIN() FOR_EACH_HELPER
/*}}}*//*}}}*//*}}}*/

int const M = 1e9+7, A = 31;

int n, m;
string s;

ll modpow(int a, int b) {/*{{{*/
    if (b == 0) return 1;
    ll res = (b&1) ? a : 1;
    ll sub = modpow(a, b/2);
    res = res*sub%M*sub%M;
    res += (res < 0)*M;
    return res;
}/*}}}*/

int const IA = modpow(A, M-2);

vll AP;/*{{{*//*{{{*/
ll apow(int b) {
    if (AP[b] < 0) {
        ll res = (b&1) ? A : 1;
        ll sub = apow(b/2);
        res = res*sub%M*sub%M;
        res += (res < 0)*M;
        AP[b] = res;
    }

    return AP[b];
}/*}}}*/

vll IAP;/*{{{*/
ll iapow(int b) {
    if (IAP[b] < 0) {
        ll res = (b&1) ? IA : 1;
        ll sub = iapow(b/2);
        res = res*sub%M*sub%M;
        res += (res < 0)*M;
        IAP[b] = res;
    }

    return IAP[b];
}/*}}}*//*}}}*/


ll fbv[(int) 2e5+2] = {}, bbv[(int) 2e5+2] = {};
ll fbit[(int) 2e5 + 2] = {}, bbit[(int) 2e5 + 2] = {};

void update_fbit(ll k, ll v) {/*{{{*/
    ll diff = (v - fbv[k])%M;
    fbv[k] = (fbv[k] + diff)%M;
    fbv[k] += (fbv[k] < 0)*M;

    for(int i=k; i<=n; i += i&-i) {
        fbit[i] = (fbit[i] + diff) % M;
        fbit[i] += (fbit[i] < 0)*M;
    }
}

ll aux_query_fbit(int a) {
    ll res = 0;
    for(int i=a; i>0; i -= i&-i)
        res = (res + fbit[i])%M;
    res += (res < 0) * M;
    return res;
}

ll query_fbit(int l, int r) {
    ll res = aux_query_fbit(r) - aux_query_fbit(l-1);
    res += (res < 0) * M;
    return res;
}/*}}}*/

void update_bbit(ll k, ll v) {/*{{{*/
    ll diff = (v - bbv[k])%M;
    bbv[k] = (bbv[k] + diff)%M;
    bbv[k] += (bbv[k] < 0)*M;
    for(int i=k; i<=n; i += i&-i) {
        bbit[i] = (bbit[i] + diff) % M;
        bbit[i] += (bbit[i] < 0)*M;
    }
}

ll aux_query_bbit(int a) {
    ll res = 0;
    for(int i=a; i>0; i -= i&-i)
        res = (res + bbit[i])%M;
    res += (res < 0) * M;
    return res;
}

ll query_bbit(int l, int r) {
    ll res = aux_query_bbit(r) - aux_query_bbit(l-1);
    res += (res < 0) * M;
    return res;
}/*}}}*/

void update_bits(int k, char c) {
    ll fv = 1ll * (c - 'a' + 1) * apow(k-1) % M;
    ll bv = 1ll * (c - 'a' + 1) * apow((n-1) - (k-1)) % M;

    update_fbit(k, fv);
    update_bbit(k, bv);
}

void init_bit() {
    For(i, 1, n+1) update_bits(i, s[i-1]);
}


int query(int l, int r) {
    ll fv = query_fbit(l, r);
    ll fhv = fv * iapow(l-1) % M;
    ll bv = query_bbit(l, r);
    ll bhv = bv * iapow((n-1) - (r-1)) % M;

    return (fhv == bhv);
}


void solve() {
    re(n, m, s);

    AP.assign(n+1, -1);
    AP[0] = 1;
    IAP.assign(n+1, -1);
    IAP[0] = 1;

    init_bit();

    rep(m) {
        red(a, b);
        if (a == 1) {
            char c; re(c);
            update_bits(b, c);
        }

        if (a == 2) {
            red(c);
            int res = query(b, c);
            pln(((res) ? "YES" : "NO"));
        }
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
