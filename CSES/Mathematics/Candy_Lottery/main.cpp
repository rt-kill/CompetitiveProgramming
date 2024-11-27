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

// n choose k times l^k
ld ncktlpk(int n, int k, ld l) {
    if (k == 0) return 1;
    ld sub = ncktlpk(n, k-1, l);
    ld mult = ld(n - k)/ld(k)*l;
    ld res = sub*mult;
    return res;
}

int n;
ld k;

ve<ld> Q, R;

void solve() {
    re(n, k);

    Q.rsz(k+1), R.rsz(k+1);
    For(v, 1, k+1) {
        For(i, 1, n+1) {
            ld sign = 2*(i&1) - 1;

            ld l1 = ld(v)/ld(k);
            /* Q[v] += sign * ncktlpk(n, i, l1); */
            Q[v] = pow(l1, n);

            ld l2 = (ld(1) - ld(1)/ld(v));
            /* R[v] += sign * ncktlpk(n, i, l2); */
            R[v] = ld(1) - pow(l2, n);
        }

    }

    ld res = 0;
    For(v, 1, k+1)
        res += ld(v) * Q[v] * R[v];

    cout << fixed << setprecision(6) << res << '\n';

    // Let P[v] be the probability that some kid is given v candies
    //  P[v]    = P[cup{xi=v : 1 <= i <= n}] = sum(P({xi = v})) - sum(P({xi = xj = v})) + ...
    //          = n*1/k - (n choose 2) * (1/k^2) + (n choose 3) * (1/k^3) - ...
    //          = sum{ (-1)^(i+1) * (n choose i) * (1/k)^i : 1 <= i <= n }

    // Let Q[v] be the probability that all kids were given at most v candies
    //  Q[v]    = n*(v/k) - (n choose 2)(v/k)^2 + ...
    //          = sum{ (-1)^(i+1) * (n choose i) * (v/k)^i : 1 <= i <= n }

    // Let R[v] be the probability that some kid was given v candies under the assumption that all kids were given at most v candies
    //  R[v]    = n*(1/v) - ...
    //          = sum{ (-1)^(i+1) * (n choose i) * (1/v)^i : 1 <= i <= n }

    // Let M[i] be the probability that the ith kid is given more candy than all kids before him
    //  M[i] = (k-2)/k * P(i-1, 1) + (k-3)/k * P(i-1, 2) + ...
    // Where P(j, l) is the probability that kids [1, j] are given at most l candies
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
