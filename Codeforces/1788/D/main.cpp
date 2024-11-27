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

#define _rdi_(a)    int a; _re_(a)
#define rdi(...)    FOR_EACH(_rdi_, __VA_ARGS__)

#define _rdll_(a)   ll a; _re_(a)
#define rdll(...)   FOR_EACH(_rdll_, __VA_ARGS__)

#define _pr_(a)     cout << a << ' ';
#define pr(...)     FOR_EACH(_pr_, __VA_ARGS__)

#define _ln_(...)       cout << '\n';
#define ln()            cout << '\n';
#define _pln_aux_(a)    cout << a << '\n';
#define _pln_(...)      FOR_EACH(_pln_aux_, __VA_ARGS__)
/* #define _pln_fork_(...) TENTH_PARAM(__VA_ARGS__,_pln_,_pln_,_pln_,_pln_,_pln_,_pln_,_pln_,_pln_,_ln_)(__VA_ARGS__) */
#define pln(...)        _pln_(__VA_ARGS__)

/* IO - Helpers {{{*/
#define TENTH_PARAM(_0,_1,_2,_3,_4,_5,_6,_7,_8,NAME,...) NAME

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

int const M = 1e9+7;

int n;
vll x, rx;
void solve() {
    re(n);
    x.rsz(n);
    each(a, x) re(a);

    rx.assign(all(x));
    reverse(all(rx));

    // let S be some subset of the points
    //  let k be some index such that S[k] goes left, and S[k+1] goes right
    //      the number of points in S is the number of points in S[:k] + S[k+1:]
    //  if no such k exists, all points go left except for the first point
    //      so the number of points will be 1
    // by induction we can conclude that the final number of points in S is the nubmer of points that go right
    //

    // let T[x] be the solution to the subsets of x for which x is the left most element

    // let D[x] be subsets of S for which x is the largest point, and all values go left
    //  that is, the number of subsets of S[:i] such that S[i] = x, and we end with just one point
    //
    //  let (i, j) be an arbitrary pair, and R[i, j] be the solution for sets for which
    //      no point between x[i] and x[j] is in the set
    //      every point before x[i] goes left, x[i] goes left, x[j] goes right
    //
    //  let pi be the smallest index such that x[i] - x[pi] <= x[j] - x[i]
    //  let pj be the largest index such that x[pj] - x[j] < x[j] - x[i]
    //      if no such indices exist, then R[i, j] = 0 since no sets exist
    //      otherwise
    //          R[i, j] = sum{pi, i}(D[k]) * sum{j, pj}(S[])
    //      NOTE: this is wrong

    // G[i][j] is the number of sets that start at x[i] followed by x[j], every point goes right
    vvll G(n, vll(n));
    // Gpfx[j] is the prefix sums array for G[:][j]
    vvll Gpfx(n, vll(n));

    Rof(i, 0, n-1) {
        G[i][n-1] = 1;
        Gpfx[i][n-1] = 1;
    }

    Rof(j, 0, n-1) Rof(i, 0, j) {
        ll diff = x[j] - x[i];
        int nj = (n-1) - (upper_bound(all(rx), x[j]+diff, greater<int>()) - rx.begin());

        G[i][j] = 1;
        if (nj != j) G[i][j] += Gpfx[j][j+1] - ((nj < n-1) ? Gpfx[j][nj+1] : 0);
        G[i][j] %= M;

        Gpfx[j][i] = Gpfx[j][i+1] + G[i][j];
        Gpfx[j][i] %= M;
    }


    // D[i][j] is the number of sets that end in x[i] followed by x[j] and end at 1 point
    vvll D(n, vll(n));
    // Dpfx[j] is the prefix sums array for D[:][j]
    vvll Dpfx(n, vll(n));

    For(j, 1, n) {
        D[0][j] = 1;
        Dpfx[j][0] = 1;
    }

    For(i, 1, n) For(j, i+1, n) {
        ll diff = x[j] - x[i];
        int bi = lower_bound(all(x), x[i]-diff, less<int>()) - x.begin();

        // point before i must be in [bi, i]
        // D[i][j] = 1 + sum{[bi, i)}(D[bi][i])
        D[i][j] = 1;
        if (bi != i) D[i][j] += Dpfx[i][i-1] - ((bi > 0) ? Dpfx[i][bi-1] : 0);
        D[i][j] %= M;

        Dpfx[j][i] = Dpfx[j][i-1] + D[i][j];
        Dpfx[j][i] %= M;
    }

    // T[i][j] is the answer for Sets whose first split is (i, j)
    vvll T(n, vll(n));
    // Tpfx[j] is the pfx for T[:][j]
    vvll Tpfx(n, vll(n));


    // NT[i][j] is the number of tails for elements that start with i j
    vvll R(n, vll(n));
    // NTpfx[j] is the pfx for NT[:][j]
    vvll Rpfx(n, vll(n));


    Rof(j, 0, n) Rof(i, 0, j)  {
        ll diff = x[j] - x[i];

        int bi = lower_bound(all(x), x[i]-diff, less<int>()) - x.begin();
        if (bi == i) continue;

        int nj = (n-1) - (upper_bound(all(rx), x[j]+diff, greater<int>()) - rx.begin());
        if (nj == j) continue;

        // number of initial segments
        //  each head ends with exactly 1 point
        ll heads = Dpfx[i][i-1]; // i > 0 since bi != i
        if (bi > 0) heads -= Dpfx[i][bi-1];
        heads %= M;
        heads += (heads < 0)*M;

        // number of tails
        ll tails = Tpfx[j][j+1]; // j < n-1 since j != nj
        if (nj < n-1) tails -= Tpfx[j][nj+1];
        tails %= M;
        tails += (tails < 0)*M;

        ll moreTails = Gpfx[j][j+1];
        if (nj < n-1) moreTails -= Gpfx[j][nj+1];
        moreTails %= M;
        moreTails += (moreTails < 0)*M;

        tails = (moreTails + tails)%M;


        // number of tails where first split is i
        T[i][j] = heads*tails%M;

        Tpfx[i][j] = Tpfx[i][j+1] + T[i][j];
        Tpfx[i][j] %= M;
    }

    ll res = 0;

    // no splis
    For(i, 0, n) For(j, i+1, n) {
        res = (res + D[i][j])%M;
        res = (res + G[i][j]-1)%M;
    }

    // splits
    For(i, 0, n) For(j, i+1, n)
        res = (res + T[i][j])%M;

    pln(res);
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
