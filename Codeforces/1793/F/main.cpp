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
vi a;

vi res;
vvpi queryBuckets;

vi seg;
void updateSeg(int i, int k) {
    i += n;

    seg[i] = k;
    for(int p = (i>>1); p > 0; p>>=1)
        seg[p] = min(seg[2*p], seg[2*p+1]);
}

int querySeg(int l, int r) {
    l += n, r += n;

    int res = INT_MAX;
    while(l <= r) {
        if (l&1) cmin(res, seg[l++]);
        if (!(r&1)) cmin(res, seg[r--]);
        l>>=1, r>>=1;
    }

    return res;
}

void initSeg() {
    seg.rsz(2*n);
    For(i, 0, n) updateSeg(i, INT_MAX);
}


void solve() {
    re(n, q);
    a.rsz(n);
    each(x, a) re(x);

    queryBuckets.rsz(n);
    For(i, 0, q) {
        rdi(l, r);
        l--, r--;
        queryBuckets[r].pb({l, i});
    }


    stack<pi> stak1({{INT_MAX, -1}});
    stack<pi> stak2({{0, -1}});

    // ltDiffs[i] is the vector of all values before i for which a[i] is the first value greater than it
    vvi ltDiffs(n);
    // gtDiffs[i] is the vector of all values before i for which a[i] is the first value less than it
    vvi gtDiffs(n);


    // this doesn't work
    //  whe I need is a vector for which
    //      v[i] is the set of all indices such that in the interval [0:i], a[i] is the smallest diff to it
    //  would this vector be too big?
    //      for any j, if ther is some j < k < i for which a[j] < a[k] < a[i]
    //          j would not be in v[i]
    //      in fact, j is int a[i] if and only if for all j < k < i,
    //          a[j] > a[k] < a[i] OR
    //          a[j] < a[k] > a[i]
    //      for some (j, i), the pair is valid iff for all j < k < i
    //          a[k] > max(a[j], a[i]) OR
    //          a[k] < min(a[j], a[i])


    For(i, 0, n) {
        while(stak1.sz && a[i] > stak1.top().fi) {
            int j = stak1.top().se; stak1.pop();
            ltDiffs[i].pb(j);
        }
        stak1.push({a[i], i});

        while(stak2.sz && a[i] < stak2.top().fi) {
            int j = stak2.top().se; stak2.pop();
            gtDiffs[i].pb(j);
        }
        stak2.push({a[i], i});
    }

    initSeg();

    res.rsz(q);
    For(r, 0, n) {
        each(l, ltDiffs[r]) {
            int diff = a[r] - a[l];
            updateSeg(l, min(seg[n+l], diff));
        }

        each(l, gtDiffs[r]) {
            int diff = a[l] - a[r];
            updateSeg(l, min(seg[n+l], diff));
        }

        for(auto [l, i] : queryBuckets[r])
            res[i] = querySeg(l, r);
    }

    each(re, res) {
        if (re == 99999) { pln(1); }
        else pln(re);
    }
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
