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

map<ll, vvll> mymap;
void rec(ll l, ll r) {
    if (r <= 1) return;

    ll nl = l/2, nr = (r+1)/2;
    rec(nl, min(l - 1, nr));
    l = max(l, 2ll);

    for(ll i=l; i<=r; ++i) {
        vvll cres(n, vll(n, -1));
        ll fh = i/2, sh = (i+1)/2;

        if (mymap.count(fh) == 0 || mymap.count(sh) == 0) cout << "BAD" << '\n';

        vvll fhm = mymap[fh];
        vvll shm = mymap[sh];

        For(i, 0, n) {
            For(j, 0, n) {
                For(k, 0, n) {
                    ll cand = (fhm[i][k] > -1 && shm[k][j] > -1) ? fhm[i][k] + shm[k][j] : -1;
                    if (cand > -1) {
                        cres[i][j] = ( cres[i][j] == -1 ) ? cand : min(cres[i][j], cand);
                    }
                }
            }
        }

        mymap[i] = cres;
    }
}

void solve() {
    // T[b][k] = min{ w[c][b] + T[c][k-1] }
    // T[a][b][k] = min{ T[a][c][k/2] + T[c][b][(k+1)/2] }
    cin >> n >> m >> k;
    vvll adj(n, vll(n, -1));
    rep(m) {
        red(a, b, c); --a, --b;
        adj[a][b] = ( adj[a][b] == -1 ) ? c : min(adj[a][b], (ll)c);
    }

    mymap[1] = adj;
    rec(k, k);

    ll res = mymap[k][0][n-1];
    cout << res << '\n';
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
