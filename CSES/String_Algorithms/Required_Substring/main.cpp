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

int const M = 1e9+7;

int n, m;
string p;

vi T;
void kmp(string s) {
    T.rsz(s.sz);
    T[0] = 0;

    int len=0, i=1;
    while(i < s.sz) {
        if (s[i] == s[len]) T[i++] = ++len;
        else if (len == 0) T[i++] = len;
        else len = T[len-1];
    }
}


ll modpow(int a, int b) {
    if (b == 0) return 1;
    ll res = (b&1) ? a : 1;
    ll sub = modpow(a, b/2);
    res = res*sub%M*sub%M;
    return res;
}


ll dp[101][1001];
// solution where the first i characters of the string are the same as p, and we can add j more chracters
ll rec(int i, int j) {
    if (j == 0) return (i == m);
    if (i+j < m) return 0;
    if (i == m) return modpow(26, j);

    if (dp[i][j] < 0) {
        ll res = 0;

        int seen[26] = {};
        for(int cur = i; cur > 0; cur = T[cur-1]) {
            int ca = p[cur] - 'A';
            if (!seen[ca]) {
                res += rec(cur+1, j-1);
                seen[ca] = 1;
            }
        }

        int ca = p[0] - 'A';
        if (!seen[ca]) {
            res += rec(1, j-1);
            seen[ca] = 1;
        }

        int unused = 26 - accumulate(seen, seen+26, 0);
        res = (res + unused*rec(0, j-1))%M;
        dp[i][j] = res;
    }

    return dp[i][j];
}


void solve() {
    re(n, p);
    m = p.sz;

    kmp(p);

    For(i, 0, m) For(j, 0, n+1)
        dp[i][j] = -1;
    ll res = rec(0, n);
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
