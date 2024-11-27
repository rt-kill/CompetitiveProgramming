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

string s;
int n, k;
ve<str> p;


vi SA;/*{{{*/
void suffix_array() {
    ve<arr<int, 3>> parts(n);
    For(i, 0, n) {
        parts[i][0] = s[i] - 'a';
        parts[i][1] = (i+1 < n) ? s[i+1] - 'a' : -1;
        parts[i][2] = i;
    }
    sort(all(parts));

    vi indices(n);
    for(int j=2; j<n; j<<=1) {
        // currently parts is sorted by the first j characters
        // Compress positions
        int new_bucket = 0;
        pi previous_bucket = {parts[0][0], parts[0][1]};
        For(i, 0, n) {
            if (previous_bucket == mp(parts[i][0], parts[i][1]))
                parts[i][0] = new_bucket;
            else {
                previous_bucket = {parts[i][0], parts[i][1]};
                parts[i][0] = ++new_bucket;
            }

            indices[parts[i][2]] = i;
        }

        // Update positions
        For(i, 0, n) {
            int ind = parts[i][2] + j;
            parts[i][1] = (ind < n) ? parts[indices[ind]][0] : -1;
        }

        sort(all(parts));
    }

    transform(all(parts), back_inserter(SA), [](auto v){ return v[2]; });
}/*}}}*/


vvi sparse;
vi lp2;
void init_sparse() {
    lp2.assign(n+1, 0);
    int cur = 1;
    for(int i=1, e=0; i<=n; ++i) {
        e +=    ((cur << 1) <= i);
        cur <<= ((cur << 1) <= i);
        lp2[i] = e;
    }

    sparse.assign(n, vi(lp2[n] + 1));
    For(i, 0, n) sparse[i][0] = SA[i];

    For(j, 0, sparse[0].sz-1) {
        For(i, 0, n) {
            sparse[i][j+1] = (i+(1<<j) < n) ? min(sparse[i][j], sparse[i+(1<<j)][j]) : sparse[i][j];
        }
    }
}


int qs(int l, int r) {
    int is = r - l + 1;
    int mp2 = lp2[is];

    int lh = sparse[l][mp2];
    int rh = sparse[r - (1<<mp2) + 1][mp2];

    return min(lh, rh);
}


void solve() {
    re(s, k);
    /* s += ('a' - 1); */
    n = s.sz;
    p.rsz(k);
    each(a, p) re(a);

    suffix_array();
    init_sparse();

    auto lbComp = [](int l, str r) {
        str suff = s.substr(l, r.sz);
        return suff < r;
    };

    auto ubComp = [](str l, int r) {
        str suff = s.substr(r, l.sz);
        return l < suff;
    };

    vi res;
    each(pat, p) {
        auto lb = lower_bound(all(SA), pat, lbComp);
        int li = lb - SA.begin(); // index of first term ge pat

        auto ub = upper_bound(all(SA), pat, ubComp);
        int ui = ub - SA.begin() - 1; // index of first term gt pat

        if (ui < li) res.pb(-1);
        else res.pb(qs(li, ui) + 1);
    }

    each(re, res) pln(re);
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
