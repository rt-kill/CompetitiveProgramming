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


vi bit;
vi exists;
void init_bit() {
    bit.rsz(n+1);
    exists.rsz(n+1);
}

int aux_query_bit(int x) {
    int res = 0;
    for(int i=x; i>0; i-=(i&-i))
        res += bit[i];
    return res;
}

int query_bit(int l, int r) {
    return aux_query_bit(r) - aux_query_bit(l-1);
}

void update_bit(int x) {
    if (exists[x]) return;

    exists[x] = 1;
    for(int i=x; i<=n; i+=(i&-i))
        ++bit[i];
}

void my_update(int x) {
    int l = 1, r = x;
    while(l < r) {
        int m = (l+r+1)/2;

        int msum = r - m + 1;
        int csum = query_bit(m, r);

        if (msum == csum) {
            r = m-1;
        } else {
            l = m;
        }
    }

    update_bit(l);
}

int query_mex() {
    return query_bit(1, n) + 1;
}



vll bit2;
vll bit3;
vll counts;
void init_bit2() {
    bit2.rsz(n+1);
    bit3.rsz(n+1);
    counts.rsz(n+1);
}

ll aux_query_bit2(int x) {
    ll res = 0;
    for(int i=x; i>0; i-=(i&-i))
        res += bit2[i];
    return res;
}

ll aux_query_bit3(int x) {
    ll res = 0;
    for(int i=x; i>0; i-=(i&-i))
        res += bit2[i];
    return res;

}

ll query_bit2(int l, int r) {
    return aux_query_bit2(r) - aux_query_bit2(l-1);
}

void update_bit2(int x) {
    exists[x] = 1;
    for(int i=x; i<=n; i+=(i&-i))
        ++bit[i];
}

void my_update(int x) {
    int l = 1, r = x;
    while(l < r) {
        int m = (l+r+1)/2;

        int msum = r - m + 1;
        int csum = query_bit(m, r);

        if (msum == csum) {
            r = m-1;
        } else {
            l = m;
        }
    }

    update_bit(l);
}

int query_mex() {
    return query_bit(1, n) + 1;
}



vi maxMex;
void solve() {
    a.clear();
    bit.clear();
    exists.clear();
    maxMex.clear();
    bit2.clear();
    counts.clear();

    re(n);
    a.rsz(n);
    each(x, a) re(x);

    init_bit();

    maxMex.rsz(n);
    For(i, 0, n) {
        my_update(a[i]);
        maxMex[i] = query_mex();
    }




    // There is always an optimal solution where spell 2 is cast last --
    //  Denote a spell of type 1 as (1, k) (casting it on monster k)
    //  Denote a spell of type 2 as (2, 0)
    //      If we have some optimal solution [(1, k1), (1, k2), ..., (2, 0), ..., (1, kv)], then [(1, k1), ..., (1, kv), (2, 0)] is also valid
    //
    // Now, notice:
    //  We never want to cast a spell of type 1 on a monster with 1 hp
    //  We never want to cast a spell of type 1 on a monster with hp < mex(monsters) -- we exclude 0 from this mex
    //  If a monster exists, whose hp is at least 2 greater than any other moster, we always want to cast s1 on this monster
    //  We would like to cast s1 in a way such that mex is maximal
    //
    // This question can easily be solved if we can find the maximal acheivable mex
    //  Let M be arbitrary
    //      M is an acheivable mex if and only if for all i < M, the number of monsters with hp >= i is at least M-i
    //          only if is obvious
    //          if can be seen via induction
    //
    // if we add a monster whose hp we already have, we might as well replace it with the largest hp less than it that we don't have yet
    //  aka, we would like to have a range max missing query
    //  this can be supported in log^2 n with a bit
    //
    // We will need to store 2 things, natural mex, and best mex
    //  if a monster has hp less than natural mex, it can not contribute to best mex
    //  if a monster has hp natural mex, we update natural mex, and best mex accordingly
    //
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
