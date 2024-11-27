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

int k;

vii diffs = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

// board[i] = board[r + c*8]
ve<ld> board;
ve<ve<ld>> mytrix;

void update_board() {
    ve<ld> buffer(8*8);

    For(r, 0, 8*8) {
        ld val = 0;
        For(c, 0, 8*8)
            val += mytrix[r][c] * board[c];
        buffer[r] = val;
    }

    board.assign(all(buffer));
}

void solve() {
    re(k);

    board.assign(8*8, 1);
    /* mytrix.assign(8*8, ve<ld>(8*8, 1)); */
    mytrix.assign(8*8, ve<ld>(8*8, 0));
    For(r, 0, 8) For(c, 0, 8) {
        ld count = 0;
        for(auto [dr, dc] : diffs) {
            int nr = r + dr, nc = c + dc;
            if (nr < 0 || nr >= 8 || nc < 0 || nc >= 8) continue;
            ++count;
        }

        ld prob = 1/count;

        for(auto [dr, dc] : diffs) {
            int nr = r + dr, nc = c + dc;
            if (nr < 0 || nr >= 8 || nc < 0 || nc >= 8) continue;

            int from = r + c*8; // any robots here
            int to = nr + nc*8; // have prob chance of moving here
            /* mytrix[to][from] *= (1 - prob); */
            mytrix[to][from] = prob;
        }
    }

    rep(k-1) update_board();

    ld tmp = 0;
    For(r, 0, 8) For(c, 0, 8) {
        ld count = 0;
        for(auto [dr, dc] : diffs) {
            int nr = r + dr, nc = c + dc;
            if (nr < 0 || nr >= 8 || nc < 0 || nc >= 8) continue;
            ++count;
        }

        ld prob = 1/count;
        ld res = 1;

        for(auto [dr, dc] : diffs) {
            int nr = r + dr, nc = c + dc;
            if (nr < 0 || nr >= 8 || nc < 0 || nc >= 8) continue;

            int from = r + c*8; // any robots here
            int to = nr + nc*8; // have (1-prob) chance of not moving here

            res *= pow(1-prob, board[from]);
        }

        cout << res << '\n';

        // res is the probability that board[r][c] is empty
        tmp += res;
    }

    cout << tmp << '\n';
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
