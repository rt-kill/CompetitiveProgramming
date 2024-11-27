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


int a, b, c, l;
void solve() {
    re(a, b, c, l);

    // suppose b == c == 0
    //  res = min(l-1, a)
    //  output:
    //      (1, 0, 2)
    //      (2, 1, 3)
    //      (3, 2, 4)
    //      (1, 3, 5)
    //      ...
    // it is similar if a==c==0 or a==b==0

    // It NEVER makes sense to have someone use the computer twice in a row
    //  so after the first problem is solved, a's basically take only 1 unit of time

    // let counts[i] be the number of teamates that have been working for (i<4) turns on the same problem
    //  initially counts[0] = 3, counts[1:] = 0
    // at each unit of time, counts[3] += counts[2], counts[i<3] = counts[i-1], counts[0] = 0
    //
    // a contest state can be represented by a current time unit, a counts array, and the counts of unsolved problems


    // we would like to maximize the positions where the computer is finished being used
    //  suppose in some contest state, it is optimal to wait an extra turn and solve b over an imediate a
    //      it follows that in some later state, an a is required to save at least 1 wait unit
    //      swapping the events can only help our order
    //  the same is true for b and c

    // the only uncovered case is when a takes 1 unit, b does not take 1 unit, and c takes 2
    //      this can never be the case, as we have 3 teamates

    // Corollary: the following strategy is forcing and optimal
    //      If at any point we can solve a in 1 unit, but b takes at least 2, and c at least 3, solve a
    //      If at any point we can solve b but not c in 1 unit, solve b
    //      If at any point we can solve c in 1 unit, solve c

    // Corollary: always start with the easiest problem avalible
    //      the same applies if we shift the times


    vvi peeps(5);
    peeps[0] = {3, 2, 1};

    auto shift = [&peeps]() {
        Rof(i, 0, 4) {
            while(peeps[i].sz) {
                peeps[i+1].pb(peeps[i].back());
                peeps[i].pop_back();
            }
        }
    };

    ve<arr<int, 3>> res;
    auto pull = [&peeps, &res](int i, int s, int t) {
        arr<int, 3> entry = { peeps[i].back(), t - s, t };
        peeps[0].push_back(peeps[i].back());
        peeps[i].pop_back();

        res.pb(entry);
    };


    For(time, 0, l+1) {
        // c in 0 units
        if (c && peeps[4].sz) {
            pull(4, 4, time);
            --c;

        // b in 0 units and c in at least 1
        } else if (b && (peeps[3].sz || peeps[4].sz)) {
            if (peeps[3].sz) pull(3, 3, time);
            else pull(4, 3, time);
            --b;

        // a int 0 units and b in at least 1
        } else if (a && (peeps[2].sz || peeps[3].sz || peeps[4].sz)) {
            if (peeps[2].sz) pull(2, 2, time);
            else if (peeps[3].sz) pull(3, 2, time);
            else pull(4, 2, time);
            --a;
        }

        shift();
    }

    pln(res.sz);
    each(re, res) {
        pr(re[0], re[1], re[2]);
        ln();
    }


    // when do we prefer a problem a over b?
    //  as the first problem, we always prefer type a
    //

    // might be backtracking with some cracked pruning
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
