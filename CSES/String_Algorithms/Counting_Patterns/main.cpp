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

/* Lambda {{{ */
#define compWrap(name)      [](auto l, auto r){ return name(l, r); }
#define transformWrap(name) [](auto v){ return name(v); }
/*}}}*/

/* IO {{{ */
// Read
#define _re_(a)     cin >> a;
#define re(...)     FOR_EACH(_re_, __VA_ARGS__)

#define _rdi_(a)    int a; re(a)
#define rdi(...)    FOR_EACH(_rei_, __VA_ARGS__)

#define _rdll_(a)   ll a; re(a)
#define rdll(...)   FOR_EACH(_rell_, __VA_ARGS__)

#define _pr_(a)     cout << a << ' ';
#define pr(...)     FOR_EACH(_pr_, __VA_ARGS__)

#define _pln_(a)    cout << a << '\n';
#define pln(...)    FOR_EACH(_pln_, __VA_ARGS__)

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

int const M = 1e9+7;
int const A = 31;
int const N = 1e5;
int const K = 5e5;

string s;
int n, k;
ve<str> p;

vpi SA;/*{{{*/
void suffix_array() {
    vll bucket(n);
    auto compress_buckets = [&bucket]() {
        vll tmp(all(bucket));
        sort(all(tmp));
        tmp.erase(unique(all(tmp)), tmp.end());

        For(i, 0, n) {
            int new_bucket = lower_bound(all(tmp), bucket[i]) - tmp.begin() + 1;
            bucket[i] = new_bucket;
        }
    };

    For(i, 0, n) bucket[i] = (s[i] - 'a' + 2);
    compress_buckets();

    // first j characters
    for(int j=2; j<=(n<<1); j<<=1) {
        rep(2) {
            ll MAX_BUCKET = *max_element(all(bucket));

            For(i, 0, n) {
                // current bucket takes highest precedence
                bucket[i] *= (MAX_BUCKET+1);
                if (i+j-1 < n)
                    bucket[i] += bucket[i+j-1];
            }

            compress_buckets();
        }
    }

    vpi order;
    For(i, 0, n) order.pb({bucket[i], i});
    sort(all(order));
    SA = vpi(all(order));
}/*}}}*/


void solve() {
    re(s, k);
    s += ('a'-1);
    n = s.sz;
    p.rsz(k);
    each(a, p) re(a);

    suffix_array();


    // lb should return iterator to first element that contains r
    //  That is, it should just do normal string comparisons
    auto lbComp = [](pi const& l, str const& r) -> bool {
        int ind = l.se;
        str suff = s.substr(ind, r.sz);
        /* pln(' '); */
        /* pln(suff); */
        /* pln(' '); */
        return suff < r;
    };

    // ub should return iterator to first element greater than r that does not contain r
    auto ubComp = [](str const& l, pi const& r) -> bool {
        int ind = r.se;
        str suff = s.substr(ind, l.sz);
        return l < suff;
    };

    vi res;
    each(pat, p) {
        auto lb = lower_bound(all(SA), pat, lbComp);
        auto ub = upper_bound(all(SA), pat, ubComp);
        res.pb(ub - lb);
    }

    each(re, res) pln(re);

    // Suppose all patterns have length less than sqrt(n)
    //  We can iterate through all candidate substrings in n*sqrt(n)
    //  With an additional log(K) complexity, we can increment the appropriate value if applicable
    // n*sqrt(n)*log(K) is too slightly too slow
    //  espically if we account for map overhead

    // Instead, store a sorted list of every suffix of s
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
