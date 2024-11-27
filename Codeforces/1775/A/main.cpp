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

int n;
str s;
void solve() {
    re(s);
    n = s.sz;


    str a, b, c;
    For(i, 1, n-1) {
        if ( (s[i] <= s[0] && s[i] <= s[i+1]) ||
             (s[i] > s[0] && s[i] > s[i+1]) ) {
            a = s.substr(0, i);
            b = {s[i]};
            c = s.substr(i+1);

            pr(a, b, c);
            ln();
            return;
        }
    }

    if (s[0] == s[1]) {
        a = {s[0]};
        b = {s[1]};
        c = s.substr(2);

        pr(a, b, c);
        ln();
        return;
    }

    if (s[n-2] == s[n-1]) {
        a = s.substr(0, n-2);
        b = {s[n-2]};
        c = {s[n-1]};

        pr(a, b, c);
        ln();
        return;
    }

    pr(":(");
    ln();




    // if for some n-1 > i > 0, s[i] <= s[0] && s[i] <= s[i+1]
    //      we have a solution

    // if for some n-1 > i > 0, s[i] > s[0] && s[i] > s[i+1]
    //      we have a solution

    //  otherwise for all i, either s[i] > s[0] and s[i] <= s[i+1]
    //      or s[i] <= s[0] && s[i] > s[i+1]

    //  if s[2] > s[0] and s[2] <= s[i+1]
    //      then s[i+1] > s[0] so s[i+1] <= s[i+2]
    //      etc..., s is monotonically increasing
    //          b > a for all assignments
    //          thus we may ignore a and would like to find b and c such that b >= c
    //              by monotonic, b >= c always
    //          solution only exists is s[n-1] == s[n-2]

    //  if s[2] <= s[0] and s[2] > s[3]
    //      then s[1:] is strictly decreasing
    //      a solution exists only if s[0] == s[1]


    // if some non-first or last character of s is 'a'
    //  let i be the index of 'a'
    //  a = s[:i], b=s[i], c=s[i+1:] is valid

    // mc = min(s[0], s[n-1]);
    // Mc = max(s[0], s[n-1]);

    // if max(s[1:n-1]) > max(s[0], s[n-1]), we have an answer
    // if min(s[1:n-1]) < min(s[0], s[n-1]), we have an answer

    //  wlog assume that either s[0] = a or s[n-1] = a
    //      if s[0] == s[n-1] = a, then a = s[0], b=s[1:n-1], c=s[n-1] is valid

}

int main() {
    /* cout << fixed << setprecision(6); */
    int t=1;
    cin >> t;
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
