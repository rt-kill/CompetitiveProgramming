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
int const A = 31;

vll HF, HR;
string s;
int n;

vll AP;
ll apow(int b) {
    if (AP[b] < 0) {
        ll res = (b&1) ? A : 1;
        ll sub = apow(b/2);
        res = res*sub%M*sub%M;
        AP[b] = res;
    }

    return AP[b];
}

ll qf(int l, int r) {
    ll res = HF[r];
    if (l > 0) {
        res = (res - apow(r-(l-1))*HF[l-1]) % M;
        res += (res<0)*M;
    }

    return res;
}

ll qr(int l, int r) {
    ll res = HR[l];
    if (r < n-1) {
        res = (res - apow(r-(l-1))*HR[r+1]) % M;
        res += (res<0)*M;
    }

    return res;
}

int ip1(int m, int d) {
    return qf(m-d, m+d) == qr(m-d, m+d);
}

int ip2(int m, int d) {
    return qf(m-d, m+d+1) == qr(m-d, m+d+1);
}

void solve() {
    re(s);
    n = s.sz;

    AP.assign(n, -1);
    AP[0] = 1;

    HF.rsz(n), HR.rsz(n);
    HF[0] = s[0] - 'a' + 1, HR[n-1] = s[n-1] - 'a' + 1;

    For(i, 1, n) HF[i] = (A*HF[i-1] + (s[i] - 'a' + 1))%M;
    Rof(i, 0, n-1) HR[i] = (A*HR[i+1] + (s[i] - 'a' + 1))%M;

    ll bm=0, bs=1;
    For(i, 0, n) {
        int l=0, r=min(i, n-1-i);
        while(l < r) {
            int m = (l+r+1)>>1;
            int flag = ip1(i, m);

            if (flag) l = m;
            else r = m-1;
        }

        if (2*l+1 > bs)
            bm = i, bs = 2*l+1;

        if (i < n-1 && s[i] == s[i+1]) {
            int l=0, r=min(i, n-1-(i+1));
            while(l < r) {
                int m = (l+r+1)>>1;
                int flag = ip2(i, m);

                if (flag) l = m;
                else r = m-1;
            }

            if (2*(l+1) > bs)
                bm = i, bs = 2*(l+1);
        }
    }

    int l = bm - (bs-1)/2, r = bm + bs/2;
    string res = s.substr(l, r-l+1);
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
