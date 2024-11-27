#include <bits/stdc++.h>
using namespace std;

/* Macros {{{ */
/* Basics {{{ */
using ll    = long long;
using ull   = unsigned long long;
using ld    = long double;
using str   = string;

using pi    = pair<int,int>;
using pll   = pair<ll, ll>;
using pld   = pair<ld, ld>;

using vi    = vector<int>;
using vll   = vector<ll>;
using vld   = vector<ld>;

using vpi   = vector<pi>;
using vpll  = vector<pll>;
using vpld  = vector<pld>;

using vvi   = vector<vi>;
using vvll  = vector<vll>;
using vvld  = vector<vld>;

using vvpi  = vector<vpi>;
using vvpll = vector<vpll>;
using vvpld = vector<vpld>;

#define INF     INFINITY
#define arr     array
#define ve      vector
#define pb      push_back
#define rsz(a)  resize(a)
#define mp      make_pair
#define fi      first
#define se      second
#define all(x)  x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define sz      size()

#define lb lower_bound
#define ub upper_bound

#define For(i, a, b)    for(int i=a; i<b; ++i)
#define Rof(i, a, b)    for(int i = (b)-1; i >= (a); --i)
#define rep(a)          For(_, 0, a)
#define each(a, x)      for(auto &a : x)
#define reach(a, x)     for(auto a = x.rbegin(); a != x.rend(); ++a)

template<typename T, typename U> inline void cmin(T &x, U y) { if(y < x) x = y; }
template<typename T, typename U> inline void cmax(T &x, U y) { if(x < y) x = y; }
/*}}}*/

/* IO {{{ */
// Read
#define _re_(a)     cin >> a;
#define re(...)     FOR_EACH(_re_, __VA_ARGS__)

#define rev(a, x)   x.rsz(a); each(b, x) _re_(b);
#define rewv(a, x)  _re_(a); rev(a, x);

#define _rdi_(a)    int a; _re_(a)
#define rdi(...)    FOR_EACH(_rdi_, __VA_ARGS__)

#define _rdll_(a)   ll a; _re_(a)
#define rdll(...)   FOR_EACH(_rdll_, __VA_ARGS__)

#define _pr_(a)     cout << a << ' ';
#define pr(...)     FOR_EACH(_pr_, __VA_ARGS__)

#define _ln_(...)       cout << '\n';
#define ln()            cout << '\n';

#define pln(...)        pr(__VA_ARGS__); cout << '\n';

#define _peln_aux_(a)    cout << a << '\n';
#define _peln_(...)      FOR_EACH(_peln_aux_, __VA_ARGS__)
#define peln(...)        _pln_(__VA_ARGS__)

/* IO - Helpers {{{*/
#define PARENS ()
#define EXPAND(arg)     EXPAND1(EXPAND1(EXPAND1(EXPAND1(arg))))
#define EXPAND1(arg)    EXPAND2(EXPAND2(EXPAND2(EXPAND2(arg))))
#define EXPAND2(arg)    EXPAND3(EXPAND3(EXPAND3(EXPAND3(arg))))
#define EXPAND3(arg)    EXPAND4(EXPAND4(EXPAND4(EXPAND4(arg))))
#define EXPAND4(arg)    arg

#define FOR_EACH(macro, ...)                                    \
  __VA_OPT__(EXPAND(FOR_EACH_HELPER(macro, __VA_ARGS__)))
#define FOR_EACH_HELPER(macro, a1, ...)                         \
  macro(a1)                                                     \
  __VA_OPT__(FOR_EACH_AGAIN PARENS (macro, __VA_ARGS__))
#define FOR_EACH_AGAIN() FOR_EACH_HELPER
/*}}}*//*}}}*//*}}}*/

ll N, M;
vll X, Y;

str P1 = "Takahashi";
str P2 = "Aoki";

void solve() {
    re(N, M);
    X.rsz(M), Y.rsz(M);
    For(i, 0, M) { re(X[i], Y[i]); }

    if (M == 0) { pln(( N&1 ? P1 : P2 )); return; }

    ll dn = min(X.front()-1, N-X.back())/2*2;
    int fis = X.front() <= dn+2, bis = X.back() >= N-dn-1;

    if (fis ^ bis) { pln(P1); return; }

    int fv = (X.front() == dn+1) ? Y.front() : 1^Y.front();
    int bv = (X.back() == N-dn) ? Y.back() : 1^Y.back();
    int dp = ((N-dn) - (dn+1) + 1)&1;
    int gp = fv^bv^dp^1;

    int rgp = (N&1)^(M&1^1);
    pln(( gp == rgp ? P1 : P2 ));

    // in order for P1 to win
    //  the number of played squares must be odd
    //  the |M|+|PS| must have parity (|M|&1^1)
    //  the number of gaps = N-(|M|+|PS|) must have parity (N&1)^(|M|&1^1)
    //      N even: (|M|&1^1)
    //      N odd:  1^(|M|&1^1)


    // suppose either one of the first two squares or one of the last two squares is set (only one of them)
    //  P1 wins

    // suppose neither of them are set, the first player to set one of them loses
    //  so the first player that can't play within 2:N-2 loses
    //      then 4:N-4

    // so   if M=0 and N is odd, P1 wins
    //      if M=0 and N is even, P2 wins




    //      if M>0, the game reduces to min(X[0], N-X.back())-N-(min(...))

    // suppose M=1, and only the last square is set: P1 always wins
    // suppose M=1, and some middle square is set

    // suppose M=0
    //  if N is odd, P1 needs the first and last colors to be different
    //  he will not place at the first 2 or last two squares as then P2 decides the gap parity
    //      wherever he places in the middle,



    if (M > 1) {
        int dp = (X.back() - X.front() + 1)&1ll;
        int vd = Y.front() ^ Y.back();
        int gp = dp^vd^1;
    }


    // claim: in a final game state, if g[i]≠g[j], and j-i+1 is even
    //  there are an even number of gaps between i and j
    //      wlog g[i] = 1
    //      if there were an odd number of gaps, all of which 1-0, it is easy to see j-i+1 is odd
    //          (odd number of gaps) (some number of even length sequences) -> odd length
    //      so some gap must be 0-1
    //      parity of location on 0 and 1 are different so either the first half up to 0 has even legnth, or the second half does
    //      proceed by induction

    // if g[i]≠g[j] and j-i+1 is odd, there are an odd number of gaps between them
    //      wlog g[i] = 1
    //      if all gaps are 1-0, we have even length (see above)
    //      some gap is 0-1, use above statement or proceed by induction

    // if g[i]=g[j] and j-i+1 is even, must be an odd number of gaps
    // if g[i]=g[j] and j-i+1 is odd, must be an even number of gaps


    // in some final state, select i<j such that g[i]=1, g[j]=0, and j-i+1 is even
    //  there could be 0 gaps between i and j
    //  suppose there is exactly 1 gap between i and j,
    //      this is not possible since it would require j-i+1 to be odd

    // at the end of the game, for all i, either i or i+1 has a square on it
    //      there are at most n/2 empty squares
    //  the numer of empty squares left is the number of 0-1's plus the number of 1-0's
    //      a 0-1 can only follow a 0-1 if there is an even number of squares between them
    //          the same is true for 1-0's following 1-0's
    //      a 0-1 can only follow a 1-0 if there is an odd number of squares between them
    //          the same is true for 1-0's following 0-1's

    // a 1-01 is the "same" as a 10-1

    // let P(i, j) be the parity of filled squares

    //      let V be the sequence of i's for which the number at i is not equel to the number at i+2
    //      |V| = #empty squares
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

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
