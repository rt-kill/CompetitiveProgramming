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

int n, k;
void solve() {
    re(n, k);

    int t1=n, t2=k, t3;
    while(t2 > 0) {
        t3 = t2;
        t2 = t1 % t2;
        t1 = t3;
    }

    int gcd = t1;

    if (((n&1)^1) || ((gcd&1)^1) || (((n/gcd)&1)^1)) { pln(-1); return; }

    vi group({0});
    int ce=k;
    while(ce != 0) {
        group.pb(ce);
        ce = (ce + k) % n;
    }

    vpi res;
    vi seen(n);

    for(int i=0; i<group.sz-1; i+=2) {
        res.pb({ group[i], group[i+1] });
        seen[group[i]] = 1, seen[group[i+1]] = 1;
    }

    int r1=-1, r2=-1;
    For(r, 0, n) {
        if (seen[r]) continue;
        if (r1 < 0) {
            r1 = r;
            each(g, group)
                seen[(r1 + g) % n] = 1;
            continue;
        }

        r2 = r;
        each(g, group)
            seen[(r2 + g) % n] = 1;

        for(int i=0; i<group.sz-1; i+=2) {
            int u1 = (r1 + group[i]) % n, u2 = (r1 + group[i+1]) % n;
            int v1 = (r2 + group[i]) % n, v2 = (r2 + group[i+1]) % n;

            res.pb({ u1, v2 });
            res.pb({ v1, u2 });
        }

        res.pb({ 0, r1 });
        r1 = -1, r2 = -1;
    }

    pln(res.sz);
    for(auto [ a, b ] : res) { pln(a, b); }



    // I may add an edge between a and b if and only if I have not added an edge between a+k and b+k

    // a -> (a+k)%n is a permutation
    // even cycles (odd length) can easily be made connected and asyclic by selecting every other pair of adjacent points
    //  this is not good, however, as connecting connected cycles would create a cycle in our graph (two edges will be added between the cycles)
    //  thus actually, if there are more than one cycle, none of them may be connected

    // if there is only one cycle ( (n, k) = 1 ), the answer is yes via (a, a+k) (a+2k, a+3k) ...

    // all cycles will be the same length
    // at least one of the cycles must be even (odd length) so gcd(n, k) must be odd
    //      suppose all of the cycles are odd (even length)
    //      none of them can be made to be connected alone, so in order to get the graph connected, we must connect them to each other
    //          we can notice that any cycle can only be made into an even number of components:
    //              simple induction
    //          but then for the components to form a tree, there must be an odd number of edges between them (not possible)
    // the number of even cycles must be odd
    //      odd cycles can only be broken into odd connected components
    //      if we have an even number of them, then we have an even number of nodes requiring an odd number of edges

    // from here it is pretty easy:
    //      connect one of the cycles (a, a+k) (a+2k, a+3k) ...
    //      for any pair of cycles not yet seen
    //          connect their every other node: (a, b+k) (a+k, b) ...
    //          select any node from one of them and connect it to our connected component

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
