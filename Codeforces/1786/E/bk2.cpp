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

#define _rdi_(a)    int a; re(a)
#define rdi(...)    FOR_EACH(_rei_, __VA_ARGS__)

#define _rdll_(a)   ll a; re(a)
#define rdll(...)   FOR_EACH(_rell_, __VA_ARGS__)

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
vll a;

vll counts;
ll curSum = 0;

// For calculating best acheviable mex
vll mexbit;
vll mexve;

// range update range query
vll rurq1;
vll rurq2;


void update_bit(vll &bit, vll &bve, int ind, ll k) {/*{{{*/
    ll diff = k - bve[ind];
    bve[ind] += diff;

    for(int i=ind; i<=n; i+=(i&-i)) {
        bit[i] += diff;
    }
}

void update_bit(vll (*bit), int ind, ll diff) {
    for(int i=ind; i<=n; i+=(i&-i)) {
        (*bit)[i] += diff;
    }
}

ll aux_query_bit(vll (*bit), int ind) {
    ll res = 0;
    for(int i=ind; i>0; i-=(i&-i)) {
        res += (*bit)[i];
    }
    return res;
}

ll query_bit(vll (*bit), int l, int r) {
    return aux_query_bit(bit, r) - aux_query_bit(bit, l-1);
}/*}}}*/

void init_bits() {/*{{{*/
    counts.assign(n+1, 0);
    mexbit.assign(n+1, 0);
    mexve.assign(n+1, 0);

    rurq1.assign(n+1, 0);
    rurq2.assign(n+1, 0);
    For(i, 1, n) {
        update_bit(&rurq1, i+1, -1);
        update_bit(&rurq2, i+1, -i);
    }

    curSum = 0;
}/*}}}*/


void update_mex(int hp) {/*{{{*/
    int l=0, r=hp;
    while(l < r) {
        int m = (l + r + 1)/2;
        ll msum = r-m+1;
        ll csum = query_bit(&mexbit, m, r);

        if (msum == csum) {
            r = m-1;
        } else {
            l = m;
        }
    }

    // first 0 value at or below hp
    int ind = l;
    if (ind == 0) return;
    update_bit(mexbit, mexve, ind, 1);
}

ll query_mex() {
    ll mex = query_bit(&mexbit, 1, n) + 1;
    return mex;
}/*}}}*/

void update_rurq(ll hp) {/*{{{*/
    // spell 2 will deal{{{
    //  1 damage for each monster with at least 1 hp
    //  1 damage for each monster with at least 2 hp
    //  if there is a monster with 2 hp
    //      1 damage for each monster with at least 3 hp
    //  otherwise,
    //      increment diff to 1, and this much damage minus diff
    //  if there is a monster with 3 hp
    //
    // Suppose S[i] is the number of monsters with at least i hp
    //  Let D[i] be the number of missing monsters before i
    // Damage2 = sum to mex (S[i] - D[i])
    //  when a monster is added, we use range update to update S[i] - D[i]
    //  then we range query
    //  range update and range query is supported by a lazy segment tree

    // we would like to range update [0:hp] with +1
    // if there are no monsters with hp helth, we would like to update
    //      [hp+1 : n] with +1}}}

    // update [1:hp] with +1
    update_bit(&rurq1, 1, 1);
    update_bit(&rurq1, hp+1, -1);
    update_bit(&rurq2, hp+1, -hp);

    // update [hp+1 : n] with +1
    if (counts[hp] == 0) {
        update_bit(&rurq1, hp+1, 1);
        update_bit(&rurq2, hp+1, hp);
    }
}

ll query_rurq(int l, int r) {
    ll lh = aux_query_bit(&rurq1, l-1) * (l-1) - aux_query_bit(&rurq2, l-1);
    ll rh = aux_query_bit(&rurq1, r) * r - aux_query_bit(&rurq2, r);
    ll res = rh - lh;
    return res;
}/*}}}*/

void update_bits(ll hp) {/*{{{*/
    update_mex(hp);
    update_rurq(hp);

    ++counts[hp];
    curSum += hp;
}

ll query_bits() {
    ll mex = query_mex();
    /* // sum of hp's at least mex *//*{{{*/
    /* ll sum = query_sum(mex, n+1); */
    /* // number of mosters with hp at least mex */
    /* ll count = query_counts(mex, n+1); */

    /* // sum of hp's less than mex that are missing */
    /* ll smiss = query_mm(1, mex-1); */
    /* // number of hp's less than mex that are missing */
    /* ll bmiss = query_mc(1, mex-1); */

    /* // cost to bring all mosters to mex-1 */
    /* ll bbm = sum - (mex-1)*count; */

    // spell 2 will deal
    //  1 damage for each monster with at least 1 hp
    //  if there is a monster with at least 1 hp
    //      1 damage for each monster with at least 2 hp
    //  otherwise ...
    //  if there is a monster with 2 hp
    //      1 damage for each monster with at least 3 hp
    //  otherwise,
    //      increment diff to 1, and this much damage minus diff
    //  if there is a monster with 3 hp
    //

    // Suppose S[i] is the number of monsters with at least i hp
    //  Let D[i] be the number of missing monsters before i
    // Damage2 = sum to mex-1 (S[i] - D[i])
    //  when a monster is added, we use range update to update S[i] - D[i]
    //  then we range query
    //  range update and range query is supported by a lazy segment tree}}}
    ll d2 = query_rurq(1, mex-1);

    ln();
    pr("MEX: ", mex);
    ln();
    For(i, 1, n) {
        pr(query_rurq(1, i));
    }
    ln();

    ll res = curSum - d2;
    return res;

    // now I need the min cost to set up mex{{{
    //  this can be found as follows:
    //      every value after the first zero is shifted down by 1
    //          note that this shifts down the second zero
    //      every value after the second zero is shifted down by 1
    //


    //  for each missing hp, I would like to take the smallest repeated hp above it
    // the min cost to set up mex can be calculated by
    //
    //  sort(a)
    //  ll tmp = 0; int i=0;
    //  for(int j=1; j<mex; ++j) {
    //      while(a[i] < j) ++i;
    //      tmp += a[i++];
    //  }
    //  return tmp - sum(1, mex-1);
    //
    //
    //  when a new hp is added, how does this sum change?
    //      the sum below its hp is the same
    //      if we skip hp, nothing changes
    //          that is a mex of hp+1 is acheviable with elements at most hp before adding hp
    //      if hp has not been added yet,
    //
    //


    // Alternatively to all these bits, we could try an do the following:
    //  Maintain a maximal sorted list of minimal sum (one indexed) V for which
    //      V[i] >= i;
    //
    //  If we have a new value x that we would like to consider adding
    //    if V[x] == x, there is nothing to do
    //  if V[x] > x
    //    insert x into V such that the order is maintained
    //    if for some y, V[y] < y,
    //      remove the first such instance
    //
    // To enable these operations, we maintain a bit of the array C, where C[x] is the number of x's in V
    //  When we insert an x, we simply increment C[x]
    //      Then, we binary search for the smallest i such that sum(0, i) > i, and decrement i}}}
}/*}}}*/


void solve() {
    re(n);
    a.rsz(n);
    each(v, a) re(v);

    init_bits();

    each(x, a) {
        update_bits(x);
        ll res = query_bits();
        pr(res);
    }

    ln();
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
