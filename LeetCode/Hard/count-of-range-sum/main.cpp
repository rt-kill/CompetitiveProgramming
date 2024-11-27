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
    vi bit;
    void update_bit(int k) {
        for(int i=k; i<bit.sz; i+=i&-i) ++bit[i];
    }

    int query_bit(int k) {
        int res=0;
        for(int i=k; i>0; i-=i&-i) res += bit[i];
        return res;
    }

    int query_bit(int l, int r) {
        int res = query_bit(r) - query_bit(l-1);
        return res;
    }

public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = nums.sz;

        vll pfx = {0};
        pfx.insert(pfx.end(), all(nums));
        For(i, 1, pfx.sz) pfx[i] += pfx[i-1];

        vll spfx(all(pfx));
        sort(all(spfx));
        spfx.erase(unique(all(spfx)), spfx.end());

        bit.assign(spfx.sz + 2, 0);
        int i0 = lower_bound(all(spfx), 0) - spfx.begin() + 1;
        update_bit(i0);

        ll res = 0;
        For(i, 1, pfx.sz) {
            ll v = pfx[i];

            // pfx[i] - upper <= pfx[j] <= pfx[i] - lower
            ll lb = v - lower, ub = pfx[i] - upper;
            int li = (spfx.rend() - lower_bound(rall(spfx), lb, [](auto l, auto r){ return l > r; }) - 1) + 1;
            int ui = lower_bound(all(spfx), ub) - spfx.begin() + 1;

            int diff = query_bit(ui, li);
            res += diff;

            int vi = lower_bound(all(spfx), v) - spfx.begin() + 1;
            update_bit(vi);
        }

        return res;
    }
};

int main() {
    vi nums;
    int lower, upper, res;
    auto solution = Solution();

    solution = Solution();
    nums = {-2, 5, -1};
    lower = -2, upper = 2;
    res = solution.countRangeSum(nums, lower, upper);
    pln(res);

    solution = Solution();
    nums = {0};
    lower = 0, upper = 0;
    res = solution.countRangeSum(nums, lower, upper);
    pln(res);

    return 0;
}
