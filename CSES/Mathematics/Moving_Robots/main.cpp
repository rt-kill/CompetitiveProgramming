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

vii diffs = { {1, 0}, {0, -1}, {-1, 0}, {0, 1} };

void solve() {
    red(k);
    // Let N[a][b][k] be the number of ways for robot a to move to square b in k moves
    // Let D[a][k] be the number of ways for robot a to move in k moves

    // N[a][b][k] = sum(N[a][nb][k-1] : nb -> b)
    // D[a][k]  = sum(N[a][b][k] : all b)
    //          = sum(N[a][b][k-1] * #nb : all b)

    // Let M[a][b][k] be N[a][b][k]/D[a][k]
    // M[a][b][k] = sum(N[a][nb][k-1] : nb -> b) / sum(N[a][b][k-1] * #nb : all b)
    //  = sum(M[a][nb][k-1] * D[a][k-1] : nb -> b) / ...
    //  = sum(M[a][nb][k-1] : nb -> b) * (D[a][k-1]/D[a][k])

    // (D[a][k-1]/D[a][k]) = sum(N[a][b][k-1] : all(b)) / sum(N[a][b][k-1] * #nb : all b)


    // Let M[a][b][k] be the probability that a ends up on b after k moves
    //  M[a][b][k] = sum(M[a][nb][k-1] * P(nb, b) : nb -> b)

    ve<ve<ve<ld>>> probs(8*8, ve<ve<ld>>(8*8, ve<ld>(k+1, 0)));
    For(r, 0, 8) For(c, 0, 8) {
        int p = r + 8*c;
        probs[p][p][0] = 1;
    }

    For(i, 1, k+1) {
        For(r1, 0, 8) For(c1, 0, 8) {
            For(r2, 0, 8) For(c2, 0, 8) {
                int a = r1 + 8*c1, b = r2 + 8*c2;

                for(auto [dr, dc] : diffs) {
                    int nr2 = r2 + dr, nc2 = c2 + dc;
                    if (nr2 < 0 || nr2 >= 8 || nc2 < 0 || nc2 >= 8) continue;
                    int nb = nr2 + 8*nc2;

                    int ncount = 0;
                    for(auto [ddr, ddc] : diffs) {
                        int nnr2 = nr2 + ddr, nnc2 = nc2 + ddc;
                        if (nnr2 < 0 || nnr2 >= 8 || nnc2 < 0 || nnc2 >= 8) continue;
                        ++ncount;
                    }

                    ld mp = (ld)1/(ld)ncount;
                    probs[a][b][i] += probs[a][nb][i-1]*mp;
                }
            }
        }
    }

    ld res = 0;
    For(r1, 0, 8) For(c1, 0, 8) {
        int a = r1 + 8*c1;
        ld pempty = 1;
        For(r2, 0, 8) For(c2, 0, 8) {
            int b = r2 + 8*c2;

            // probability that b does NOT move to a
            ld nprob = ld(1) - probs[b][a][k];
            pempty *= nprob;
        }

        res += pempty;
    }

    cout << fixed << setprecision(6) << res << '\n';
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
