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

int const M = 1e9 + 7;

map<ll, ll> memory;
ll rec2(ll n) {
    if (n < 0) return 0;
    if (n == 0) return 1;

    if (!memory.count(n)) {
        ll res = 0;
        For(i, 1, 7) res = (res + rec2(n-i)) % M;
        memory[n] = res;
    }

    return memory[n];
}

ll rec(ll n) {
    if (n <= 20) return rec2(n);

    if (!memory.count(n)) {
        ll m = n/2;

        ll res = rec(n-m)*rec(m) % M;
        For(d, 2, 7) for(ll r=m-d+1; r<m; ++r)
            res = (res + rec(n-r-d)*rec(r)%M)%M;
        memory[n] = res;
    }

    return memory[n];
}


ll nrec(ll l, ll r) {
    if (r <= 20) return 0;

    ll nl = l/2 - 5, nr = (r - r/2)+5;

    for(ll i = nl; i<=nr; ++i);

    nrec(nl, nr);
    return 0;
}



void solve() {
    ll n;
    re(n);

    // We see
    //  T(n) = T(k)*T(n-k) + T(k-1)*(T(n-k-1) + T(n-k-2) + ...) + T(k-3)*(...) + ... + T(k-5)
    //      We calculate [T(k-5), ..., T(k)] and [T(n-k-5), ..., T(n-k)]
    //      To reuse calculations, we would like these to be as close together as possible -- k := n/2
    //      To calculate n, we calculate [n/2 - 5, n/2+6] -- 11
    //      To calculate these, we calculate [(n/2-5)/2-5, (n/2+6)/2 + 6] -- ~17
    //      At each step, we go from k calculations to k/2 + 11 calculations
    //      So we should never need to calculate more than 20 things
    //      20*log(n) is good enough
    rec2(20);
    ll res = rec(n);
    cout << res << '\n';
}

int main() {
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
