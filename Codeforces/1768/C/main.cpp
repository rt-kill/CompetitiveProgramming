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
vi a;
void solve() {
    re(n);
    a.rsz(n);
    each(x, a) re(x);

    vpi la(n);
    For(i, 0, n) {
        la[i] = {a[i], i};
    }

    sort(all(la));
    vi p(n), q(n);

    Rof(i, 0, n) {
        // we must fill in the range [0, i] (len i+1) with numbers at most i
        //  cant be a valid permutation: at least 2 slots will have the same number
        if (la[i].fi < i+1) {
            pln("NO");
            return;
        }

        // more that 2 occurences of a number
        if ((i > 1 && la[i].fi == la[i-2].fi)) {
            pln("NO");
            return;
        }

        if (i == 0 || la[i].fi != la[i-1].fi) {
            p[i] = la[i].fi, q[i] = la[i].fi;
        } else {
            p[i] = la[i].fi;
            q[i-1] = la[i].fi;
            --i;
        }
    }

    // if a solution exists, one exists with our current setup of p and q
    //  in otherwords, all values set so far are legal

    set<int> sp(all(p)), sq(all(q));
    int cp=1, cq=1;

    // we might as well assign the smallest values to the left side
    For(i, 0, n) {
        while(sp.count(cp)) ++cp;
        while(sq.count(cq)) ++cq;

        if (p[i] == 0) {
            p[i] = cp;
            sp.insert(cp);
        }

        if (q[i] == 0) {
            q[i] = cq;
            sq.insert(cq);
        }
    }

    // setup might be provably valid, but no harm in double checking
    For(i, 0, n) {
        if (max(p[i], q[i]) != la[i].fi) {
            pln("NO");
            return;
        }
    }

    // return to proper order
    vi rp(n), rq(n);
    For(i, 0, n) {
        rp[la[i].se] = p[i];
        rq[la[i].se] = q[i];
    }

    pln("YES");
    each(re, rp) pr(re);
    ln();
    each(re, rq) pr(re);
    ln();
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
