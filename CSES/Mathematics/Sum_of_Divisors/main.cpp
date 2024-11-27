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

int const M = 1e9 + 7;

ll sum(ll a, ll b) {
    ll lh = b+a, rh = b-a+1;
    lh /= (!(lh&1) + 1), rh /= (!(rh&1) + 1);
    lh %= M, rh %= M;
    ll res = lh*rh%M;
    return res;
}

ll n;
void solve() {
    re(n);

    // sum(phi(n))
    //      = 1*n + 2*(n/2) + 3*(n/3) + ... + n*(n/n)
    //      = 1*n + 2*(n/2) + ... + sqrt(n)*(n/sqrt(n)) + ...

    int m = sqrt(n);
    /* cout << "Middle is " << m << '\n'; */

    ll lh = 0;
    for(ll i = 1; i <= m; ++i)
        lh = (lh + i*(n/i))%M;

    /* cout << "Left Half is " << lh << '\n'; */

    ll den = m+1;
    ll rh = 0;
    while(den <= n) {
        ll val = n/den;

        ll xlb = (n-1)/val, xub = n/val + 1, x;
        for(ll tmp = xlb; tmp <= xub; ++tmp)
            if (val == n/tmp) x = tmp;

        ll lden = x;

        ll msum = sum(den, lden)*val%M;
        /* cout << "den,   lden,   sum,  val,   msum" << '\n'; */
        /* cout << den << ' ' << lden << ' ' << sum(den, lden) << ' ' << val << ' ' << msum << '\n'; */

        rh = (rh + msum)%M;

        den = lden+1;
    }

    /* cout << "Right Half is " << rh << '\n'; */

    ll res = (lh + rh)%M;
    cout << res << '\n';
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
