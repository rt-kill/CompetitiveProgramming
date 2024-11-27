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

int n, m;
ll k;

vvll mmult(vvll l, vvll ri) {
    vvll mmult_res(n, vll(n));
    For(c, 0, n) {
        For(r, 0, n) {
            ll val = 0;
            For(k, 0, n)
                val = (val + l[r][k] * ri[k][c])%M;
            mmult_res[r][c] = val;
        }
    }

    return mmult_res;
}

vvll mpow(vvll m, ll e) {
    if (e == 1) return m;
    vvll res = mpow(m, e/2);
    res = mmult(res, res);
    if (e&1) res = mmult(res, m);
    return res;
}


void print_matrix(vvll m) {
    cout << '\n';
    cout << '\n';
    For(r, 0, n) {
        For(c, 0, n) {
            cout << m[r][c] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
    cout << '\n';
}


void solve() {
    re(n, m, k);

    vvll adj(n, vll(n));
    rep(m) {
        red(a, b); --a, --b;
        adj[b][a] += 1;
    }

    vvll res = mpow(adj, k);

    ll re = res[n-1][0];
    cout << re << '\n';

    // Assume no loops
    // If the graph is complete, the answer is
    //  T(2) = 1
    //  T(k) = sum{ res[a, c, k-1] : c != b }
    //       = (n-2)*T(k-1) + res[a, a, k-1]
    //       = (n-2)*(n-2)*T(k-2) + (n-2)*res[a, a, k-2] + res[a, a, k-1]
    //       = C(k-2) + (n-2)C(k-3) + (n-2)^2C(k-4) + ...
    //       = C(k-2) + (n-2)*T(k-1)

    //  C(k) = (n-1)*C(k-2) + (n-1)(n-2)C(k-3) + (n-1)(n-2)^2C(k-3) + ...
    //       = (n-1)*( T(k) )

    //  T(k) = (n-1)T(k-2) + (n-2)T(k-1)
    //  Calculatable with matrix exponentation

    //  |  0   1  | |Tk-2| = |Tk-1|
    //  | n-1 n-2 | |Tk-1| = | TK |

    // Let T[b][i] be the number of paths from a to b of length i
    //  We see that
    //      T[b][i] = sum{T[c][i-1] : c->b}
    //              = sum{delta(c, b)*T[c][i-1]}

    //  d(i, j) = (j -> i)
    //  | d(1,1) d(1,2) d(1,3) ... d(1,n) | |T[1][i]|   |T[1][i+1]|
    //  | d(2,1) d(2,2) d(2,3) ... d(2,n) | |T[2][i]|   |T[2][i+1]|
    //  | d(3,1) d(3,2) d(3,3) ... d(3,n) | |T[3][i]| = |T[3][i+1]|
    //  |  ....   ....   ....  ...  ....  | |  ...  | = |   ...   |
    //  |  ....   ....   ....  ...  ....  | |  ...  |   |   ...   |
    //  | d(n,1) d(n,2) d(n,3) ... d(n,n) | |T[n][i]|   |T[n][i+1]|


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
