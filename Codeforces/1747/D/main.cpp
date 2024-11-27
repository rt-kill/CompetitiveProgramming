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

int n, q;
vll a, pfx, spfx;
vvi ollsts, ellsts;
vi nzinds, res;


vpi queries;
void solve() {
    re(n, q);
    rev(n, a);

    rep(q) {
        rdi(l, r);
        --l, --r;
        queries.pb({l, r});
    }

    pfx.assign(all(a));
    For(i, 1, n) pfx[i] ^= pfx[i-1];

    spfx.assign(all(pfx));
    sort(all(spfx));
    spfx.erase(unique(all(spfx)), spfx.end());

    ollsts.rsz(n), ellsts.rsz(n);
    For(i, 0, n) {
        int ind = lower_bound(all(spfx), pfx[i]) - spfx.begin();
        if (i&1)    ollsts[ind].pb(i);
        else        ellsts[ind].pb(i);
    }

    For(i, 0, n) if (a[i] != 0) nzinds.pb(i);
    nzinds.pb(n);

    res.rsz(q);
    For(i, 0, q) {
        auto [l, r] = queries[i];

        ll xorv = (l > 0) ? pfx[r] - pfx[l-1] : pfx[r];
        if (xorv != 0) { res[i] = -1; continue; }

        int ind1 = *lower_bound(all(nzinds), l);
        if (r < ind1) { res[i] = 0; continue; }

        if ((r - l + 1)&1) { res[i] = 1; continue; }

        if (a[l] == 0) { res[i] = 1; continue; }
        if (a[r] == 0) { res[i] = 1; continue; }

        ll lpfx = (l > 0) ? pfx[l-1] : 0;
        int ind2 = lower_bound(all(spfx), lpfx) - spfx.begin();

        int ind3 = r;
        if (l&1) {
            auto it = upper_bound(all(ollsts[ind2]), l);
            if (it != ollsts[ind2].end()) ind3 = *it;
        } else {
            auto it = upper_bound(all(ellsts[ind2]), l);
            if (it != ellsts[ind2].end()) ind3 = *it;
        }

        if (ind3 < r) { res[i] = 2; continue; }
        res[i] = -1;
    }

    each(re, res) pln(re);

    // queries for which (r-l+1) is in {1, 2, 3} are impossible unless the xor of the values is 0

    // no operations should intersect:
    //  base case: 1 operation is clear
    //  induction: suppose after preforming O[1],
    //      by hypothesis none of the remaining operations should intersect
    //      Contradictions: let O[i] be the first operation that intersects with O[1]
    //          if O[1] is fully contained by O[i], O[1] did nothing
    //          if O[1] fully contains O[i], O[i] did nothing
    //          if O[1] left intersects O[i] evenly, the last x values in O[i] are unnesesary (intervals keep odd length)
    //          if O[1] left intersects O[i] oddly, they can be merged (interval keeps odd length)
    //          if O[1] right intersects O[i] evenly, ...
    //          if O[1] right intersects O[i] oddly, ...

    // it follows that if (r-l+1) is odd,
    //      there a solution iff the xor of the entier interval is 0
    //          (so 1 is optimal) unless all values are already 0

    // if (r-l+1) is even
    //      there is a solution iff the xor of the entier interval is 0 and
    //              for some strict prefix, the xor of that interval is 0
    //          (so 2 is optimal) unless all values are already 0

    // we want to support the following
    //  given l, r what is the xor of values in l, r
    //  given l, r are all values in [l, r] zero
    //  given l, what is the smallest r>=l such that [l, r] is zero
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
