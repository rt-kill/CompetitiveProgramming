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

int const N = 2e5;

int n;
vi a, b;
vi counts;
void solve() {
    re(n);
    rev(n, a);
    rev(n, b);

    counts.assign(N+1, 0);
    each(v, a) ++counts[v];
    each(v, b) --counts[v];
    int mv = *max_element(all(counts));
    if (mv > 0) { pln("No"); return; }

    int toa=0, tob=0;
    For(i, 0, n-2) {
        toa |= ((a[i]&1) + (a[i+1]&1) + (a[i+2]&1) == 2);
        tob |= ((b[i]&1) + (b[i+1]&1) + (b[i+2]&1) == 2);
    }

    int ec=0, fea=-1, sea=-1, feb=-1, seb=-1;
    For(i, 0, n) {
        if (!(a[i] & 1)) {
            ++ec;
            if (fea == -1) fea = a[i];
            else if (sea == -1) sea = a[i];
        }
        if (!(b[i] & 1)) {
            if (feb == -1) feb = b[i];
            else if (seb == -1) seb = b[i];
        }
    }

    if (toa || tob) {
        int res = (toa == tob);
        res &= ((fea == feb && sea == seb) || (ec >= 3));
        pln((res ? "Yes" : "No"));
        return;
    }

    int res = 1;
    For(l, 0, n) {
        if (a[l] & 1 || b[l] & 1) {
            res &= (a[l] == b[l]);
            continue;
        }

        int r = l;
        while(r+1 < n && !(a[r+1] & 1)) ++r;
        if (r - l + 1 <= 2) res &= (a[l] == b[l] && a[r] == b[r]);
        else {
            map<int, int> tmp;
            For(i, l, r+1) ++tmp[a[i]], --tmp[b[i]];
            For(i, l, r+1) res &= tmp[a[i]] == 0;
        }
        l = r;
    }

    pln((res ? "Yes" : "No"));


    // if no two odd values of A are "touching" manually check
    // if two odd values of A are "touching", we can roll all the odd values to the right
    //      first keep movin odd values right until the far left odd value is touching another
    //      then roll right picking up everything
    // operations are invertible so it is valid to preform operations on B
    //      do the same thing on B

    // the folling properties reduce the question to "does a and b have the same values"
    //  A is all even

    // as long as there are least three even value, and two odd values are touching,
    //      the question becomes does A and B contain the same elements

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
