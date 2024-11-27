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

ll const M = 1e9 + 7;
ll const OM = M-1;

int n;
ve<pair<ll, ll>> p;
vll divcOM;

ll mpow(ll a, ll b) {/*{{{*/
    if (b == 0) return 1;
    ll res = (b&1) ? a : 1;
    ll sub = mpow(a, b/2);
    sub = sub*sub%M;
    res = res*sub%M;
    return res;
}/*}}}*/

// a/b % M
ll divM(int a, int b) {
    ll binv = mpow(b, M-2);
    ll res = a*binv%M;
    return res;
}

// (1 + a + a^2 + ... + a^b)
ll msum(ll a, ll b) {/*{{{*/
    ll num = mpow(a, b+1) - 1;
    num += (num < 0)*M;

    ll den = a-1;
    den += (den < 0)*M;

    ll res = divM(num, den);
    return res;
}/*}}}*/

vll divPDP;
ll gdiv_prod() {
    divPDP.rsz(n+1);
    divPDP[n] = 1;

    Rof(i, 0, n) {
        auto [ prime, count ] = p[i];
        ll sub = divPDP[i+1];
        ll lh = mpow(sub, count+1);

        ll sOM = count*(count+1)/2%OM;
        ll np = divcOM[i+1]*sOM%OM;
        ll rh = mpow(prime, np)%M;

        ll res = lh*rh%M;
        divPDP[i] = res;
    }

    return divPDP[0];
}

vll divSDP;
ll gdiv_sum() {/*{{{*/
    divSDP.rsz(n+1);
    divSDP[n] = 1;

    Rof(i, 0, n) {
        auto [ prime, count ] = p[i];

        ll sub = divSDP[i+1];
        ll sum = msum(prime, count);

        ll res = sub*sum%M;
        divSDP[i] = res;
    }

    return divSDP[0];
}/*}}}*/



void solve() {
    re(n);
    p.rsz(n);
    each(a, p) { re(a.fi, a.se); }

    divcOM.rsz(n+1);
    divcOM[n] = 1;
    Rof(i, 0, n) {
        divcOM[i] = (p[i].se + 1)*divcOM[i+1]%OM;
    }


    // the number of divisors is the product of (count+1)
    ll div_count = 1;
    each(a, p) div_count = div_count * (a.se + 1) % M;

    // the product of divisors can be solved for recursively
    //  res(i)  = {1^{res(i+1)}*res(i+1)} * p^{res(i+1)}*res(i+1) * p^{2*res(i+1)}...
    //          = (1^{res(i+1)} * p^{res(i+1)} * p^2^{res(i+1)} * ...) * {res(i+1)}^{k+1}
    //          = p^{res(i+1)*(0 + 1 + 2 + ... + k)} * res(i+1)^{k+1}

    ll div_prod = gdiv_prod();

    // the sum of divisors can be solved for recursively
    //  res(i)  = res(i+1) + p*res(i+1) + ... + p^k*res(i+1)
    //          = res(i+1) * (1 + p + ... + p^k)
    //          = res(i+1) * ((p^{k+1} - 1)/(p-1))
    ll div_sum = gdiv_sum();

    cout << div_count << ' ' << div_sum << ' ' << div_prod << '\n';
}

int main() {
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
