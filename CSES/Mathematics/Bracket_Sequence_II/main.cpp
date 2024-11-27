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

ll modpow(ll a, ll b) {
    if (b == 0) return 1;
    ll res = (b&1) ? a : 1;
    ll sub = modpow(a, b/2);
    res = res*sub%M*sub%M;
    return res;
}

ll moddiv(ll a, ll b) {
    ll bi = modpow(b, M-2);
    ll res = a*bi%M;
    return res;
}

ll choose(ll a, ll b) {
    if (b > a) return 0;
    if (b == 0) return 1;
    ll sub = choose(a, b-1);
    ll num = sub*(a-b+1)%M, den = b;
    ll res = moddiv(num, den);
    return res;
}

int n;
string s;
void solve() {
    re(n, s);

    int x=0, y=0, valid=1;
    each(a, s) {
        x += (a == '('), y += (a == ')');
        valid &= (x >= y);
    }

    if (!valid || n&1) {
        cout << 0 << '\n';
        return;
    }

    int rem = n - x - y;
    int rx = n/2 - x, ry = n/2 - y;

    ll res = choose(rem, ry) - choose(rem, ry+1);
    res += (res<0)*M;
    cout << res << '\n';

    // (rem choose rx) is the number of ways to reach (n,n) from (x,y) minimally
    // Any invalid path will eventually have y = x+1
    //  Flipping after this point will give us a path to (n-1, n+1)
    //  Any path to (n-1, n+1) that starts at (x,y) can be flipped as well to go to (n, n)
    //  Number of paths to (n-1, n+1) is (rem choose ry+1) or (rem choose rx-1)

    // res = (rem choose rx) - (rem choose rx-1)
    //     = (rem choose ry) - (rem choose ry+1)


    // we can use a similar intuition as bracket sequences 1
    //  we would like to find all paths from (a,b) to (n,n) that never cross the line x=y
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
