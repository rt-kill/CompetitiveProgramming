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

#define rewv(a, x)  _re_(a); x.rsz(a); each(b, x) _re_(b);

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

int n, q;
vi a, k, p, c, h, co;

void solve() {
    rewv(n, a);
    rewv(q, k);

    sort(all(a));
    int avalible=0, parts=0, tot=0;
    For(i, 0, n) {
        ++avalible, ++tot;
        if (avalible == a[i]) {
            h.pb(i), c.pb(tot);
            avalible = 0;
            ++parts;
        }

        p.pb(parts); // max number of components we can have saturated with happy people
        co.pb(tot);  // number of elements before this
    }

    vi res(n+1);
    For(i, 1, n+1) {
        if (a[0] > (n-(i-1))) {
            res[i] = 0;
            continue;
        }

        int l=0, r=n-1;
        while(l < r) {
            int m = (l+r+1)/2;
            int good=0;

            int di = tot - co[m];
            if (di >= (i-1))
            {
                good = (a[m] <= co[m] + (di - (i-1)));
            }
            else if (i - di > c.sz) {
                good = 0;
            } else {
                int ni = i-di;
                int spare = co[m] - c[ni-1-1];
                good = (a[m] <= spare);
            }

            if (good) l = m;
            else r = m-1;
        }

        res[i] = l+1;
    }

    each(req, k) pln(res[req]);

    // for i,k we can only make a[:i] totally happy in k components if
    //  parts[i] >= k
    //  counts[i] - counts[h[k-1]] >= i


    /* c.rsz(n+1); */
    /* each(v, a) ++c[v]; */

    /* int avalible = 0, comps = 0; */
    /* For(i, 1, n+1) { */
    /*     avalible += c[i]; */
    /*     while (avalible >= i) { */
    /*         avalible -= i; */
    /*         ++comps; */
    /*     } */
    /* } */


    // question:
    //  can we partition the first x values of a into k buckets so that everyone is happy?
    //      if yes,


    // there always exists an optimal assignment for which the following is true
    //      for some bucket B
    //      - if someone is happy, B has someone of max value who is happy
    //      - every person with value less than this max happy person is happy
    //      - any other bucket consists of only smaller and larger values
    //      - if some other bucket has a happy person, it has a person with value equal to the buckets size
    //      - any bucket with only unhappy people is of size 1
    //      - every other bucket has size at most |B|


    // start with some optimal solution
    // select B to be a bucket that contains a max value happy person

    // if some other bucket has a value inbetween,
    //      if the person in that bucket is happy, we swap them with one of the smaller values in our bucket
    //      if the person in that bucket is unhappy, we swap them with one of the larger values in our bucket
    //          since we are constructing B from an already optimal solution, the person we give to another bucket can not become happy in this transaction

    // if some other bucket has a happy person and no people with value equal to the bucket size
    //      we move the largest element from this bucket into B

    // since B has the largest happy person, it is also one of the largest buckets
    //  if some other bucket has size = |B|
    //      that bucket has a person with value |B|
    //      every person in B is of value exactly |B|
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
