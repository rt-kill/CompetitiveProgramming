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
vi p;
void solve() {
    re(n);
    p.rsz(n+1);
    For(i, 1, n+1) re(p[i]);


    int flag=0;
    set<int> seen;

    ll res = 0;
    For(i, 1, n+1) {
        if (p[i] == i) continue;

        int size = 0;
        set<int> tmpseen;
        int cond = 0;

        while(p[i] != i) {
            if (tmpseen.count(p[i]+1) || tmpseen.count(p[i]-1))
                cond=1;
            tmpseen.insert(p[i]);

            swap(p[i], p[p[i]]);
            ++size;
        }

        if (tmpseen.count(p[i]+1) || tmpseen.count(p[i]-1))
            cond=1;
        ++size;

        flag |= cond;
        res += size-1;
    }

    res += (flag) ? -1 : 1;
    pln(res);


    // there is 1 inversion for every value before 1
    //  so either p[1] = 1, or p[2] = 1
    //      if p[2] = 1, then p[1] = 2
    //      and for all i > 2, p[i] = i
    //  it follows by induction that for there to be exactly one inversion
    //      there exists some j such that p[j] = j+1 && p[j+1] = j
    //      for all i!=j, p[i] = i;

    // cost of sorting a permutation:
    //  a permutation can be broken into disjoint cycles
    //  for some cycle c, we can sort it with len(c)-1 transpositions
    //  in fact this is minimal:
    //      involves some algebra
    //  but basically, the optimal sorting is just to send p[i] to index p[i]
    // cost of sorting a permutation is number of incorrect elements - number of components

    // if j and j+1 are part of the same cycle for any j, then the answer is (C-1)
    //      adding the transposition increases the cycle count by 1

    // otherwise, adding any of these transposiitons will decrease the cycle count by 1 and cost an extra move

    // if we alread have j such that p[j]=j+1 and p[j+1]=j, just sort the rest of the perm
    // otherwise, we wonder if adding such a transposition
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
