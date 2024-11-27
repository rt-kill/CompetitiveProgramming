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

vvll modmult(vvll m1, vvll m2) {
    vvll res(2, vll(2));
    For(r, 0, 2) For(c, 0, 2) {
        ll val = 0;
        For(k, 0, 2)
            val = (val + m1[k][c]*m2[r][k])%M;
        res[r][c] = val;
    }

    return res;
}


vvll modpow(vvll trix, ll e) {
    vvll tmp = { { 1, 0 }, { 0, 1 } };
    if (e == 0) return tmp;

    if (e&1) tmp.assign(all(trix));
    vvll sub = modpow(trix, e/2);
    vvll res = modmult(tmp, modmult(sub, sub));
    return res;
}

ll n;
void solve() {
    re(n);

    // We can solve this problem in two ways:

    // Inspired by Dice Game:
    // Notice that fib[i] is the same as the number of ways to write i as a sum of {1, 2}
    //      fib[0] = 1 -- empty sum
    //      fib[1] = 1 -- (1)
    //      fib[2] = 2 -- (1 + 1, 2)
    //  The intuition for this is via induction: clearly if this is true for fib[i-1] and fib[i-2],
    //      then any sum to i is either one to i-1 followed by a 1 or one to i-2 followed by a 2
    //
    // With this intuition, we can see that
    //  Fib[i] = (Fib[k]*Fib[i-k]) + (Fib[k-1]*Fib[i-k+1])
    //      The first half of this represents the number of ways to sum to i that contains a prefix that sums to k
    //      The second half of this represents the number of ways to sum to i doesn't contain a prefix that sums to k

    // We finially arrive at
    //  Dp[n] = Dp[n/2]*Dp[n-n/2] + Dp[n/2-1]*Dp[n-n/2+1]
    //  Now it might seem that this is too slow:
    //      Every Dp uses 4 sub cases, building a Quad Tree
    //      Quad tree has depth log(n), so it will have O(n) nodes
    //  But, this tree has a lot of reused nodes -- the structure will be as follows:
    //       1                  n
    //       3          [(n-2)/2, (n+3)/2]
    //       4          [(n-6)/4, (n+9)/4]
    //       5         [(n-14)/8, (n+19)/8]
    //       5                 ...

    //  Each level has at most 5 nodes
    //  The intuition for this is that the interval first shrinks in half (we divide it by two and potentially add 1 to the right)
    //      interval of length 5 goes to at most 3
    //  Then we stretch it to the left and right each by 1
    //      interval of length 3 goes to 5
    //  So really this tree will have O(log(n)) nodes


    // Approach 2:
    // We notice that
    // |0 1| |fib[i-2]| = |fib[i-1]|
    // |1 1| |fib[i-1]| = | fib[i] |

    // So
    // |0 1|^i |fib[0]| = | fib[i] |
    // |1 1|   |fib[1]| = |fib[i+1]|

    vvll mytrix = { { 0, 1 }, { 1, 1 } };
    ll res = modpow(mytrix, n)[0][1];
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
