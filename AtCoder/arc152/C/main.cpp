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

int N;
vi a;
void solve() {
    rewv(N, a);

    // for any operation, we may only choose i for which a[i] ≥ max(a)/2
    //  a[i] does not change if we preform operaiton i
    //  a[j] can only increase if we choose i for which a[i] is maximal

    // after operation i, all terms are in (0, 2*a[i])
    // after operation i, the sum S becomes 2*a[i]*n - S

    // operations are invertible -- so preforming some operation can never ruin the integrity of our list

    // after operation i, for all j, a[j] = a[i] + (a[i] - a[j])
    //  as long as there exists i for which max(a) > a[i] >= max(a)/2
    //      we can decrease the max element

    // suppose no such element exists
    //


    // operations can sort of be viewed as reflecting the points about the value we choose
    //  that is, the </> flip, and the distance with a[i] is the same
    //  additionally, after an operation:
    //      the max element becomes 2*a[i] - min(a)
    //          only elements that have value >= (2*a[i] - min(a))/2 can be used for the next operation
    //              4*a[i] - 2*a[j] >= 2*a[i] - min(a)
    //          this translates to values <= a[i] + min(a)/2
    //      the min element becomes 2*a[i] - max(a)


    // constant arrays are minimal:
    //  after any operation, the only two options are to inverse it, or keep growing


    // operations never change the distance between elements
    //  if the array has 0, it is optimal
    //  a solution with a minimal elements is optimal

    // by continuing to flip upwards, we eventually reach a point where we may operate on any point
    //  from here, we would like to make either the min or max element the closest to one of the lines made by their distance
    //  (minimize their value mod their difference)


    // minimize (min % (max - min))
    //  what is the smallest number % (max-min) as an integral combination of
    //      max (must include 1*max), 2*(max-a[0]), 2*(max-a[1])

    int Ma = *max_element(all(a)), ma = *min_element(all(a));
    int Mod = Ma - ma;

    vi diffs;
    For(i, 0, N) diffs.pb(2*(Ma - a[i]));

    int cgcd = diffs[0];
    For(i, 1, N) {
        int Mv = max(cgcd, diffs[i]), mv = min(cgcd, diffs[i]);
        while(mv > 0) {
            int tmp = mv;
            mv = Mv % mv;
            Mv = tmp;
        }

        cgcd = Mv;
    }

    int res = min(ma % cgcd, Ma % cgcd) + Mod;
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
