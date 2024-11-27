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


void solve() {
    red(n);
    vll p(n);
    each(a, p) re(a);

    int res = 0;
    for(int i=1; i<n; i+=2) {
        res ^= p[i];
    }

    cout << ((res > 0) ? "first" : "second") << '\n';

    // ralable the last stair to 0
    // any individual ball must be moved a total of x times where x is the stair that it is on
    // let T represent the total number of moves that must be done before the game ends
    //  T = sum(i * p[i])

    // If T is odd, we can always find a move that makes it even (simply move one ball)
    // If T is even, we can not nessesarily find a move that keeps it even

    // Instead let T be the number of usable stairs that have a ball on it
    // In the last state, T must be even (0)
    //  If T is ever odd, we can either make it even (if a stair is followed by a stair with balls on it)

    // If all balls are on even stairs, second always wins
    //      if the opponent moves a ball from stair a to a-1, move the same ammount of balls from stair a-1 to a-2

    // Let T be the number of balls on odd stairs
    //  in the final state, T is 0
    // If T is odd, we can easily make it even
    // If the opponents move keeps T even, "copying" their move keeps T even
    // The only exception to handle is copying a move from stair (3 to 2)
    //  "copying" this move will put balls on 1 and could give them a win

    // Let O be the xor of balls on odd squares and E be for even squares
    //  If O is zero, any move will change this
    //  If O is non-zero, we can make it zero -- similar to nims game
    //      This is nims game with wanting to be the last person to remove stuff from odd steps
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
