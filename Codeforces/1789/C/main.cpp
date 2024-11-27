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

#define rev(a, x) x.rsz(a); each(b, x) _re_(b);
#define rewv(a, x)  _re_(a); rev(a, x);

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

int n, m;
vi a;
vpi updates;

vvpi intervals;
void popIntervals() {
    intervals.assign(n+m+1, vpi());
    each(v, a) intervals[v].pb({0, -1});

    vi ca(all(a));
    For(cl, 1, m+1) {
        auto [p, v] = updates[cl-1];
        int pv = ca[--p];

        intervals[pv].back().se = cl;
        intervals[v].pb({cl, -1});
        ca[p] = v;
    }

    For(v, 1, n+m+1)
        if (intervals[v].sz && intervals[v].back().se == -1)
            intervals[v].back().se = m+1;
}

// msums[v]:= sum{i : v in a[i]} (i)
//          = sum{in : intervals[v]} (sum{i in intervals}(i))
vll msums, counts;
void popMsums() {
    msums.assign(n+m+1, 0);
    counts.assign(n+m+1, 0);

    For(v, 1, n+m+1) {
        ll count=0, sum = 0;
        each(interval, intervals[v]) {
            auto [l, r] = interval;
            ll size = r-l;
            ll offset = (ll)l * size;
            ll csum = size*(size-1)/2;

            count += size;
            sum += csum + offset;
        }

        counts[v] = count;
        msums[v] = sum;
    }
}



void solve() {
    re(n, m);
    rev(n, a);

    updates.clear();
    rep(m) {
        rdi(p, v);
        updates.pb({p, v});
    }

    popIntervals();
    popMsums();

    // a value v is counted m times for every array that has it (this double counts)
    // a value v is counted k times for every array that does not have it (k is the number of arrays that have it)

    // let c[v] be the number of arrays that have value v
    //  out of the (n choose 2) choices of (i,j)
    //      for sum{i : v in a[i]}sum{j > i}, array i will have v
    //      for sum{j : v in a[j]}sum{i < j}, array j will have v
    //      for (c[v] choose 2), array i and j will have v

    // so for each value v, we would like to query
    //      sum{i : v in a[i]}sum{j > i} = sum{i : v in a[i]}(m-i) = m*c[v] - sum{i : v in a[i]}(i)
    //      sum{j : v in a[j]}sum{i < j} = sum{j : v in a[j]}(j)

    ll res = 0;
    For(v, 1, n+m+1) {
        ll cv = counts[v];
        ll diff = m*cv - cv*(cv-1)/2;
        res += diff;
    }

    pln(res);
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
