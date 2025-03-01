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

#define INF     INFINITY
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

#define lb lower_bound
#define ub upper_bound

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

#define rev(a, x)   x.rsz(a); each(b, x) _re_(b);
#define rewv(a, x)  _re_(a); rev(a, x);

#define _rdi_(a)    int a; _re_(a)
#define rdi(...)    FOR_EACH(_rdi_, __VA_ARGS__)

#define _rdll_(a)   ll a; _re_(a)
#define rdll(...)   FOR_EACH(_rdll_, __VA_ARGS__)

#define _pr_(a)     cout << a << ' ';
#define pr(...)     FOR_EACH(_pr_, __VA_ARGS__)

#define _ln_(...)       cout << '\n';
#define ln()            cout << '\n';

#define pln(...)        pr(__VA_ARGS__); cout << '\n';

#define _peln_aux_(a)    cout << a << '\n';
#define _peln_(...)      FOR_EACH(_peln_aux_, __VA_ARGS__)
#define peln(...)        _pln_(__VA_ARGS__)

/* IO - Helpers {{{*/
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

class Solution {
private:
    ll const A = 101, M = 1e9+7;

    ll modpow(int a, int b) {
        ll res = 1;
        for(ll ce=1, cp=a; ce <= b; ce<<=1, cp = cp*cp%M)
            if (ce & b) res = res * cp % M;
        return res;
    }

    int n;
    str s;

    vll fwh, bwh;
    void myHash() {
        fwh.rsz(n), bwh.rsz(n);

        fwh[0] = s[0] - 'a';
        For(i, 1, n) fwh[i] = (A*fwh[i-1] + (s[i] - 'a')) % M;

        bwh[n-1] = s[n-1] - 'a';
        Rof(i, 0, n-1) bwh[i] = (A*bwh[i+1] + (s[i] - 'a')) % M;
    }

    ll gfwh(int l, int r) {
        ll res = (l > 0) ? fwh[r] - modpow(A, r-l+1)*fwh[l-1] : fwh[r];
        res %= M;
        res += (res<0)*M;
        return res;
    }

    ll gbwh(int l, int r) {
        ll res = (r < n-1) ? bwh[l] - modpow(A, (r-l+1))*bwh[r+1] : bwh[l];
        res %= M;
        res += (res<0)*M;
        return res;
    }

    int isPal(int l, int r) {
        return gfwh(l, r) == gbwh(l, r);
    }

public:
    long long maxProduct(str t) {
        n = t.sz;
        s = t;
        myHash();

        int l, r;
        vi mps(n), mpe(n);

        l=0, r=0;
        while(r < n) {
            cmax(l, 0);
            l += ((l&1) ^ (r&1));

            while(!isPal(l, r)) l += 2;
            mpe[r] = (r-l+1);
            ++r, l -= 2;
        }

        l=n-1, r=n-1;
        while(l >= 0) {
            cmin(r, n-1);
            r -= ((l&1) ^ (r&1));

            while(!isPal(l, r)) r -= 2;
            mps[l] = (r-l+1);
            --l, r += 2;
        }

        ll res = 0;

        ll mpl=0;
        map<int, int> rightPals;
        For(i, 0, n) ++rightPals[mps[i]];

        For(i, 0, n-1) {
            --rightPals[mps[i]];
            if (rightPals[mps[i]] == 0) rightPals.erase(mps[i]);

            cmax(mpl, mpe[i]);
            ll mpr = rightPals.size() ? (*rightPals.rbegin()).fi : 0;

            cmax(res, mpr*mpl);
        }

        return res;
    }
};

int main() {
    auto s = Solution();
    str t;
    int res;

    t = "ababbb"; res = s.maxProduct(t);
    pln(res);

    t = "wtbptdhbjqsrwkxccxkwrsqjbhdtpbtw"; res = s.maxProduct(t);
    pln(res);

    return 0;
}
