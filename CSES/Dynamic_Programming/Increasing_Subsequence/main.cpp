#include <bits/stdc++.h>
using namespace std;

/* Macros {{{ */
/* Basics {{{ */
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ii = pair<int,int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvll = vector<vll>;
using vvii = vector<vii>;

#define arr array
#define ve vector
#define pb push_back
#define rsz(a) resize(a)
#define mp make_pair
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define sz size()

#define For(i, a, b) for(int i=a; i<b; ++i)
#define Rof(i, a, b) for(int i = (b)-1; i >= (a); --i)
#define rep(a) For(_, 0, a)
#define each(a, x) for (auto &a : x)
#define reach(a, x) for (auto a = x.rbegin(); a != x.rend(); ++a)

template<typename T, typename U> inline void cmin(T &x, U y) { if(y < x) x = y; }
template<typename T, typename U> inline void cmax(T &x, U y) { if(x < y) x = y; }
/*}}}*/

/* IO {{{ */
#define _re_(a) cin >> a;
#define re(...) FOR_EACH(_re_, __VA_ARGS__)

#define _red_(a) int a; cin >> a;
#define red(...) FOR_EACH(_red_, __VA_ARGS__)

#define _pr_(a) cout << a << ' ';
#define pr(...) FOR_EACH(_pr_, __VA_ARGS__)

#define _prln_(a) cout << a << '\n';
#define prln(...) FOR_EACH(_prln_, __VA_ARGS__)
#define pln(...) FOR_EACH(_prln_, __VA_ARGS__)

/* IO - Helpers {{{*/
#define PARENS ()
#define EXPAND(arg) EXPAND1(EXPAND1(EXPAND1(EXPAND1(arg))))
#define EXPAND1(arg) EXPAND2(EXPAND2(EXPAND2(EXPAND2(arg))))
#define EXPAND2(arg) EXPAND3(EXPAND3(EXPAND3(EXPAND3(arg))))
#define EXPAND3(arg) EXPAND4(EXPAND4(EXPAND4(EXPAND4(arg))))
#define EXPAND4(arg) arg

#define FOR_EACH(macro, ...)                                    \
  __VA_OPT__(EXPAND(FOR_EACH_HELPER(macro, __VA_ARGS__)))
#define FOR_EACH_HELPER(macro, a1, ...)                         \
  macro(a1)                                                     \
  __VA_OPT__(FOR_EACH_AGAIN PARENS (macro, __VA_ARGS__))
#define FOR_EACH_AGAIN() FOR_EACH_HELPER
/*}}}*//*}}}*//*}}}*/

int n;
vi x;

map<int, int, greater<int>> e;
map<int, int, greater<int>> rev;

void solve() {
    re(n);
    x.rsz(n);
    each(a, x) re(a);

    e[0] = 0;
    For(i, 0, n) {
        // if current sequence exists that ends on x[i], continue
        if (e.count(x[i])) continue;

        // find largest list with that ends on value less than i
        auto [k, v] = *e.upper_bound(x[i]);

        if (rev.count(v+1)) {
            int ok = rev[v+1];
            e.erase(ok);
            rev.erase(v+1);
        }

        e[x[i]] = v+1;
        rev[v+1] = x[i];
    }

    pln(transform_reduce(all(e), 0, [](auto l, auto r){return max(l, r);}, [](auto v){ return v.se; }));
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
