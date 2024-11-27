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

int n, d;
ve<arr<int, 3>> frogs;
vector<array<int, 3>> myArray;

void solve() {
    re(n, d);
    frogs.assign(n, arr<int, 3>({0, 0, 0}));
    each(frog, frogs) cin >> frog[0] >> frog[1] >> frog[2];

    auto weightComp = [](auto l, auto r){ return l[1] > r[1]; };
    sort(all(frogs), weightComp);

    ve<arr<int, 3>> bestFrogs(all(frogs));
    sort(all(bestFrogs), [](auto l, auto r){
            if (l[1] > r[1]) return true;
            else return (l[1] == r[1] && l[2] > r[2]);
            });
    bestFrogs.erase(unique(all(bestFrogs), [](auto l, auto r){ return l[1] == r[1]; }), bestFrogs.end());

    map<int, int, greater<int>> piles;
    for(auto frog : bestFrogs) {
        int w = frog[1], h = frog[2];

        vpi tmp({{w, h}});
        for(auto [dw, dh] : piles) {
            if (dw <= w) break;
            tmp.pb({ min(w, dw - w), h + dh });
        }

        for(auto [nw, nh] : tmp)
            piles[nw] = max(piles[nw], nh);
    }


    vpi betterPiles;
    for(auto pile : piles) {
        if (betterPiles.empty()) betterPiles.pb(pile);
        if (betterPiles.back().se >= pile.se) continue;
        betterPiles.pb(pile);
    }
    sort(all(betterPiles));



    int res = 0;

    priority_queue<arr<int, 3>, ve<arr<int, 3>>, decltype(weightComp)> pq(all(frogs), weightComp);
    while(pq.size()) {
        auto [l, w, h] = pq.top(); pq.pop();

        auto it = upper_bound(all(betterPiles), mp(w, INT_MAX));
        int dh = (it != betterPiles.end()) ? (*it).se : 0;
        res += (l + dh > d);
    }

    pln(res);
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
