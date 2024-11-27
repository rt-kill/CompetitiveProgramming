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

int q, a, b;
ve<arr<int, 3>> queries;

vi cl;
int gind(int v) {return lower_bound(all(cl), v) - cl.begin() + 1;}

// b1: min leq
// b2: max geq
// b2: min geq
vi b1, b2, b3;

int qb1(int k) {
    int res = INT_MAX;
    for(int i=k; i>0; i-=(i&-i)) cmin(res, b1[i]);
    return res;
}
void ub1(int k, int v) {
    for(int i=k; i<b1.sz; i+=(i&-i)) cmin(b1[i], v);
}
int qb2(int k) {
    int res = INT_MIN;
    for(int i=k; i<b2.sz; i+=(i&-i)) cmax(res, b2[i]);
    return res;
}
void ub2(int k, int v) {
    for(int i=k; i>0; i-=(i&-i)) cmax(b2[i], v);
}
int qb3(int k) {
    int res = INT_MAX;
    for(int i=k; i<b3.sz; i+=(i&-i)) cmin(res, b3[i]);
    return res;
}
void ub3(int k, int v) {
    for(int i=k; i>0; i-=(i&-i)) cmin(b3[i], v);
}


void solve() {
    re(q, a, b);
    cl.pb(a), cl.pb(b);

    rep(q) {
        rdi(t, l, r);
        cl.pb(l), cl.pb(r);
        queries.pb({t, l, r});
    }

    sort(all(cl));
    cl.erase(unique(all(cl)), cl.end());

    int Mv = cl.sz + 2;
    b1.assign(Mv, INT_MAX);
    b2.assign(Mv, INT_MIN);
    b3.assign(Mv, INT_MAX);

    // -r + min{a <= r}     ( a+b )
    //  l - max{a >= l}     ( a-b )
    // -r + min{a-b >= l}   ( a-b )

    int ia = gind(a), ib = gind(b);

    ub1(ia, a+b);
    ub2(ia, a-b);
    if (ia > ib) ub3(ia-ib, a-b);

    for(auto [t, l, r] : queries) {
        int il = gind(l), ir = gind(r);
        if (t == 1) {
            ub1(il, l+r);
            ub2(il, l-r);
            if (il > ir) ub3(il-ir, l-r);
        } else {
            int p1 = -r + qb1(ir);
            int p2 = (qb2(il) == INT_MIN) ? INT_MIN :  l - qb2(il);
            int p3 = -r + qb3(l-r);

            pr(p1, p2, p3);
            ln();

            int res = max(0, min(min(p1, p2), p3));
            pln(res);
        }
    }





    // if x >= a,   ||x-a|-b| == |x-(a+b)| = |(a+b) - x|
    // if x < a,    ||x-a|-b| == |(a-b)-x| = |(a-b) - x|

    // sps a <= b
    //  for x in [a, a+b],  ||x-a|-b| = a+b - x
    //  for x > a+b,        ...       = x - (a+b)
    //  for x < a           ...       = x - (a-b)

    // if a > b
    //  for x in [a, a+b],  ||x-a|-b| = a+b - x
    //  for x > a+b,        ...       = x - (a+b)
    //  for x in [a-b, a],  ...       = x - (a-b)
    //  for x < a-b         ...       = (a-b) - x

    // for some query (l, r)
    //  if for some point (a, b) a+b in [l, r]
    //      answer is 0
    //  if for some point (a, b) a-b in [l, r]
    //      answer is 0
    //  otherwise, we consider
    //      over (a,b) such that a <= b
    //          the smallest a+b such that  a <= r
    //          the largest a+b such that   a+b <= r
    //          the largest (a-b) for which l <= a
    //      over (a,b) such that a > b
    //          the smallest a+b for which  a <= r
    //          the largest (a+b) for which a+b <= r
    //          the largest (a-b) for which a-b <= r, l <= a
    //          the smallest a-b for which a-b >= l

    // we can simplify a bit
    //  the smallest    (a+b) such that r >= a
    //  the largest     (a-b) such that l <= a
    //  the smallest    (a-b) such that l <= a-b

    // even more
    // -r + min{a <= r}     ( a+b )
    //  l - max{a >= l}     ( a-b )
    // -r + min{a-b >= l}   ( a-b )


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
