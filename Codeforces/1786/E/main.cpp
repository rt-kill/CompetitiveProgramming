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
vi a;


vll mexbit;
vll mexve;
vll mexsum1;
vll mexsum2;

vll csum1;
vll csum2;

ll monsterSum;

void update_bit(vll &bit, int ind, int diff) {/*{{{*/
    for(int i=ind; i<=n; i += (i&-i))
        bit[i] += diff;
}

void range_update_bit(vll &bit1, vll&bit2, int l, int r, int diff) {
    update_bit(bit1, l, diff);
    update_bit(bit1, r+1, -diff);
    update_bit(bit2, l, (l-1)*diff);
    update_bit(bit2, r+1, -r*diff);
}

ll query_bit(vll &bit, int a) {
    ll res = 0;
    for(int i=a; i>0; i-=(i&-i))
        res += bit[i];
    return res;
}

ll query_bit(vll &bit, int l, int r) {
    ll res = query_bit(bit, r) - query_bit(bit, l-1);
    return res;
}

ll range_query_bit(vll &bit1, vll &bit2, int l, int r) {
    ll lh = (l-1)*query_bit(bit1, l-1) - query_bit(bit2, l-1);
    ll rh = r*query_bit(bit1, r) - query_bit(bit2, r);
    return rh - lh;
}/*}}}*/

void init_bits() {
    monsterSum = 0;
    mexbit.assign(n+1, 0);
    mexve.assign(n+1, 0);
    mexsum1.assign(n+1, 0);
    mexsum2.assign(n+1, 0);
    csum1.assign(n+1, 0);
    csum2.assign(n+1, 0);
}

void update_mexbits(ll hp) {
    // there is no 0 in mexve[1:hp]
    ll exitCond = query_bit(mexbit, 1, hp);
    if (exitCond == hp) return;

    /* int l=1, r=hp; */
    /* while(l < r) { */
    /*     int m = (l + r + 1)/2; */
    /*     ll msum = r-m+1; */
    /*     ll csum = query_bit(mexbit, m, r); */

    /*     if (msum == csum) { */
    /*         r = m-1; */
    /*     } else { */
    /*         l = m; */
    /*     } */
    /* } */

    /* // first 0 value at or below hp */
    int ind = hp;
    /* if (mexve[ind]) return; */

    mexve[ind] = 1;
    update_bit(mexbit, ind, 1);
    // sum[1:i] is mex[1:i]
    // so we range increment all values >= ind
    range_update_bit(mexsum1, mexsum2, ind, n, 1);
}

void update_cbits(ll hp) {
    range_update_bit(csum1, csum2, 1, hp, 1);
}


void update_bits(ll hp) {
    monsterSum += hp;
    update_mexbits(hp);
    update_cbits(hp);
}

ll query_bits() {
    ll mex = query_bit(mexbit, 1, n) + 1;

    // this is mex[1:1] + mex[1:2] + ... + mex[1:mex-2]
    ll mexsum = range_query_bit(mexsum1, mexsum2, 1, mex-2) + (mex-2);


    // sum_{1, mex-1} D[x] = sum_{2, mex-1} (x - mex[1:(x-1)]) = ...
    ll dsum = ((mex-1)*(mex)/2 - 1) - mexsum;

    ll csum = range_query_bit(csum1, csum2, 1, mex-1);

    ll spell2Dmg = csum - dsum;
    ll totDmg = monsterSum;

    ll casts = totDmg - spell2Dmg;
    return casts;
}



void solve() {
    re(n);
    a.rsz(n);
    each(x, a) re(x);

    init_bits();
    each(x, a) {
        update_bits(x);
        ll res = query_bits();
        pr(res);
    }
    ln();

    // we would like to calculate the max number of damage that spell 2 can d
    //  For each x, it will deal 1 damage to all mosters with at least x hp
    //      minus the number of monsters with more than x hp needed to fill in the gaps before hand
    //
    //  let S[x] be the number of monsters with at least x hp
    //      we will have a range update and range query to maintain and query S
    //
    //  let T[x] be the maximum number of gaps that can be filled in using monsters leq x
    //      when we add y,
    //
    //  let D[x] be the number of monsters needed to fill in all gaps before x that can not be filled in by monsters with hp less than x
    //      aka the number of monsters with hp >= x that will be brought below x
    //  when we add a monster with hp y:
    //      let z>=x be minimal such that D[z] = 0
    //      we decrement the range D[y:z-1] by 1
    //  how do we find z quickly?
    //
    //  alternatively, we can notice that D[x] = x - mex[1:x-1]
    //  so sum(D) = x*n - sum(mex[1:i])
    //      we already know we can maintain a mex in a bit that only supports point update
    //      if instead, we support range update, this seems possible
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
