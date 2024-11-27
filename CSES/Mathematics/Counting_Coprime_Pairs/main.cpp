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

int const N = 1e5;
int const X = 1e6;
ll  const M = 1e10;

ll n;
vll x, counts, S;

void solve() {
    cin >> n;
    x.rsz(n), counts.rsz(X+1);
    each(a, x) {
        re(a);
        ++counts[a];
    }

    S.rsz(X+1);
    For(i, 2, X+1) For(j, 1, X/i + 1)
            S[i] += counts[i*j];

    // S[i] is the number of elements divisible by i
    // We can derive a solution from |cup(cross(S[i], S[i]))|
    //  Let sq(S[i]) := cross(S[i], S[i])

    // From inclusion exclusion, we get
    //  |cup(sq(S[i]))| = sum(|sq(S[i])|) - sum(|cap(|sq(..

    // We notice the following
    //  cap(sq(S[i]), sq(S[j])) = sq(cap(S[i], S[j]))
    //  for primes, cap(S[p], S[q]) = cap(S[p*q])
    //  S[i*j] <= S[i] -> |cup(sq(S[i]))| = |cup(sq(S[p]))|

    // Arriving at the following
    //  |cup(sq(S[i]))|     = sum(|sq(S[p])|) - sum(|sq(S[pq])|) + sum(|sq(S[pqr]|)) - ...
    //                      = sum(|sq(S[p])|)
    //                      - (2*sum(|sq(S[pq])|)  : {p < q})
    //                      + (6*sum(|sq(S[pqr])|) : {p < q < r})
    //                      - ...

    // Obviously |sq(S[i])| = |S[i]| choose 2

    vll bad(X+1), pdiv(X+1), omega(X+1);

    For(i, 2, X+1) {
        if (pdiv[i] > 0) {
            ll div = pdiv[i];
            ll j = i/div;

            if (bad[j] || j/div*div == j) {
                bad[i] = 1;
                continue;
            }

            omega[i] = omega[j] + 1;
        } else {
            omega[i] = 1;
            For(j, 1, X/i+1) if (pdiv[i*j] == 0)
                pdiv[i*j] = i;
        }
    }

    ll aux_res = 0;
    For(i, 2, X+1) {
        if (bad[i]) continue;
        ll parity = omega[i]&1;
        ll sign = 2*parity - 1;
        ll sq = S[i]*(S[i]-1)/2;

        ll tmp = aux_res + sq*sign;
        aux_res = tmp;
    }


    ll res = n*(n-1)/2 - aux_res;
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
