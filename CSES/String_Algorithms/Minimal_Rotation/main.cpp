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

int const A = 31, B = 1e9+7;

string s;
int n;
// H[i] = (s[0]A^i + ... + s[i-1]A + s[i]) mod B
// s[l]A^l + ... + s[r] = H[r] - H[l-1]*A^{r-l-1}
vll H;


ll modpow(int a, int b) {
    if (b == 0) return 1;
    ll res = (b&1) ? a : 1;
    ll sub = modpow(a, b/2);
    res = res*sub%B*sub%B;
    return res;
}

vll AP;
ll apow(int b) {
    if (b < 0) return modpow(A, b);

    if (AP[b] < 0) AP[b] = modpow(A, b);
    return AP[b];
}


ll get_hash(int l, int r) {
    ll hsh = H[r];
    if (l > 0) {
        hsh = (hsh - H[l-1]*apow(r-(l-1))) % B;
        hsh += (hsh<0)*B;
    }

    return hsh;
}


class Functor {
    public:
        // returns 1 if s[l:l+n] < s[r:r+n], 0 otherwise;
        int operator()(int l, int r) {
            int lb = 0, rb = n-1;
            while(lb < rb) {
                int m = (lb+rb)/2;

                int lh = get_hash(l, l+m);
                int rh = get_hash(r, r+m);

                if (lh == rh) lb = m + 1;
                else rb = m;
            }

            return (s[l+lb] < s[r+lb]);
        }

};


void solve() {
    re(s);
    n = s.sz;
    s += s;

    AP.assign(s.sz, -1);

    H.rsz(2*n);
    H[0] = s[0] - 'a' + 1;
    For(i, 1, 2*n) H[i] = (A*H[i-1] + (s[i] - 'a' + 1)) % B;

    vi mpts(n);
    iota(all(mpts), 0);

    int mi = 0;
    Functor f;
    For(i, 1, n) if (f(i, mi))
        mi = i;

    pln(s.substr(mi, n));
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
