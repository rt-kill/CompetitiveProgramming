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

int n;
str s;
void solve() {
    re(n, s);

    vi ft(26);
    each(x, s) ++ft[x - 'a'];

    vpi sft;
    For(i, 0, 26) sft.pb({ft[i], i});
    sort(all(sft), greater<pi>());

    // number of characters to include
    int mc=INT_MAX, bnc;
    For(i, 1, 27) {
        int fn = n/i;
        if (fn*i != n) continue;

        int ccst = 0;
        For(j, 0, i)
            ccst += max(0, fn - sft[j].fi);

        if (ccst < mc) {
            mc = ccst;
            bnc = i;
        }
    }

    int fn = n/bnc;
    int res=0;
    str t = s;

    For(i, bnc, 26) {
        int cpnt = 0;
        while (sft[i].fi > 0) {
            ++res;
            while(t[cpnt] != (sft[i].se + 'a')) ++cpnt;
            t[cpnt] = ('a'-1);
            --sft[i].fi;
        }
    }

    For(i, 0, bnc) {
        int cpnt = 0;
        while (sft[i].fi > fn) {
            ++res;
            while(t[cpnt] != (sft[i].se + 'a')) ++cpnt;
            t[cpnt] = ('a'-1);
            --sft[i].fi;
        }

        while(sft[i].fi < fn) {
            while(t[cpnt] != ('a' - 1)) ++cpnt;
            t[cpnt] = (sft[i].se + 'a');
            ++sft[i].fi;
        }
    }

    pln(res, t);


    // if it is already balanced, we just return s

    // we count the number of each character to get a table
    //  c1 | c2 | c3 | ...
    //  f1 | f2 | f3 | ...

    // how many characters do we want t to have?
    //  if t has 1 character, the cost will simply be
    //      min(n-f1, n-f2, ...)
    //  if t has 2 characters,

    // it always makes sense to keep the letters that appear the most frequently
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
