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

class Solution {
private:
    vll tp, niners; // powers of 10
public:
    Solution() {
        tp.pb(1);
        For(i, 1, 19) tp.pb(10ll * tp.back());

        niners.pb(9);
        For(i, 1, 18) niners.pb(niners.back() + 9ll*tp[i]);
    }

    int l10(ll v) {
        int l=0, r=17;
        while(l < r) {
            int m = (l+r+1)/2;
            if (v/tp[m] > 0) l = m;
            else r = m-1;
        }
        return l;
    }

    ll maxLeq(ll v) {
        int i = l10(v), o=0;
        if (i == o) return v;
        ll inner = (i > o) ? ((v % tp[i]) - (v % tp[o+1])) / tp[o+1] : 0;

        while(i > o && ((v/tp[i])%10 <= (v/tp[o])%10 || inner > 0)) {
            if ((v/tp[i])%10 > (v/tp[o])%10) v -= tp[o+1];
            v += ((v/tp[i])%10 - (v/tp[o])%10) * tp[o], --i, ++o;
            inner = (i > o) ? ((v % tp[i]) - (v % tp[o+1])) / tp[o+1] : 0;
        }

        if (o == 0 && (v/tp[i])%10 == 1) return niners[i-1];

        if (i > o) {
            v -= tp[i];
            v += ((v/tp[i])%10 - (v/tp[o])%10) * tp[o];
            For(j, o+1, i) v += (9 - (v/tp[j])%10) * tp[j];
        }
        return v;
    }

    ll minGeq(ll v) {
        int i = l10(v), o=0;
        if (i == o) return v;
        ll inner = (i > o) ? ((v % tp[i]) - (v % tp[o+1])) / tp[o+1] : 0;

        while(i > o && ((v/tp[i])%10 >= (v/tp[o])%10 || inner < niners[i - o - 1])) {
            if ((v/tp[i])%10 < (v/tp[o])%10) v += tp[o+1];
            v += ((v/tp[i])%10 - (v/tp[o])%10) * tp[o], --i, ++o;
            inner = (i > o) ? ((v % tp[i]) - (v % tp[o+1])) / tp[o+1] : 0;
        }

        if (o == 0 && (v/tp[i])%10 == 9) return tp[i+1] + 1;

        if (i > o) {
            v += tp[i];
            v += ((v/tp[i])%10 - (v/tp[o])%10) * tp[o];
            For(j, o+1, i) v += (0 - (v/tp[j])%10) * tp[j];
        }
        return v;

    }

    string nearestPalindromic(string n) {
        ll num = stoll(n);
        ll ml = maxLeq(num);
        if (ml == num) ml = maxLeq(num-1);

        ll ub = minGeq(num);
        if (ub == num) ub = minGeq(num+1);


        /* ll ub = num + tp[l10(num)] + 1; */
        /* ll tmp = maxLeq(ub); */

        /* while(tmp > num) { */
        /*     ub = tmp, tmp = maxLeq(tmp-1); */
        /*     pln(tmp); */
        /* } */

        stringstream stream;
        if (num - ml <= ub - num) stream << ml;
        else stream << ub;

        str res = stream.str();
        return res;
    }
};

int main() {
    auto s = Solution();
    str n, res;

    n="123", res = s.nearestPalindromic(n);
    pln(n);
    pln(res);
    ln();

    n="1", res = s.nearestPalindromic(n);
    pln(n);
    pln(res);
    ln();

    n="121", res = s.nearestPalindromic(n);
    pln(n);
    pln(res);
    ln();

    n="1213", res = s.nearestPalindromic(n);
    pln(n);
    pln(res);
    ln();

    n="807045053224792883", res = s.nearestPalindromic(n);
    pln(n);
    pln(res);
    ln();

    n="230584300921369395", res = s.nearestPalindromic(n);
    pln(n);
    pln(res);
    ln();


    return 0;
}
