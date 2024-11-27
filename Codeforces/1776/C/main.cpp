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

#define rewv(a, x)  _re_(a); x.rsz(a); each(b, x) _re_(b);

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


int n, m;
vi x;
void solve() {
    re(n, m);
    x.rsz(n);
    each(v, x) re(v);

    // passes of length 1 should always be used at the end
    //  we may assume that if n <= m, there are no passes of length 1

    // if for any two passes min(u, v) > m/2, bernardo always wins
    // if for any k passes, min(...) > m/k, bernardo always wins
    //      base case: k=2
    //      suppose there are k passes for which min(..) > m/k
    //          wlog there are no other passes
    //          after the first of these is used, choose a shelf as follows:
    //              since the interval is of size > m/k, there exists some index i within it (1-indexed) for which
    //              i%(m/k+1) = 0
    //              choose that i
    //
    //  the shelves are divided into two halfs, of length l and r with min(l, r) >= m/k
    //      additionally, by choice of i, l%(m/k + 1) = m/k
    //      by induction, the most passes we can use on each half is
    //          l/(m/k + 1) = (l-m/k)/(m/k + 1), r/(m/k + 1)
    //      we see
    //          l/(m/k + 1) + r/(m/k + 1) <= (l-m/k + r)/(m/k+1) = (m-(m/k+1))/(m/k+1) = m/(m/k+1) - 1 < k-1
    //  there is a much easier proof using the pigonhole principle
    // otherwise, the solution is trivial for alison

    sort(all(x));
    reverse(all(x));

    int bdo = 0, myMin;
    For(i, 1, n) {
        if (x[i] > m/(i+1)) {
            bdo = 1;
            myMin = x[i];
            break;
        }
    }

    vi used(m+1, 0);
    if (bdo) {
        pln("Bernardo");
        cout.flush();

        rep(n) {
            rdi(y, a);
            int ind = (y >= myMin) ? a/myMin*myMin + (myMin-1) : a;
            pln(ind);
            cout.flush();
        }

    } else {
        pln("Alessia");
        cout.flush();

        // for each interval, descending, greedily select the first index that it will fit into
        //  suppose this doesnt work, and the ith interval (1 indexed) has no where to go
        //      it follows that there are at least m/x[i] already seen shelves
        //          m/x[i] <= i-1 < i
        //      but then min(...) = x[i] > m/i and benerado can always win

        For(i, 0, n) {
            int count=0;
            For(j, 1, x[i]) count += used[j];

            int rpos = x[i];
            while(rpos <= m+1) {
                count += used[rpos];
                if (count == 0) break;

                count -= used[rpos - x[i] + 1];
                ++rpos;
            }

            pr(x[i], rpos - x[i] + 1);
            ln();
            cout.flush();

            rdi(b);
            used[b] = 1;
        }
    }
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
