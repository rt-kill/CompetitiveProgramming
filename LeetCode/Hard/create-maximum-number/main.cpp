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
public:
    int numLess(vector<int>& numl, vector<int>& numr) {
        if (numl.sz != numr.sz) return (numl.sz < numr.sz);

        For(i, 0, numl.sz) if (numl[i] != numr[i])
            return (numl[i] < numr[i]);

        return 0;
    }

    vector<int> maxNumber(vector<int>& nums, int k) {
        int n = nums.sz;

        deque<int> deck;
        For(i, 0, n-k) {
            while(deck.sz && deck.back() < nums[i]) deck.pop_back();
            deck.pb(nums[i]);
        }

        vi res;
        For(i, n-k, n) {
            while(deck.sz && deck.back() < nums[i]) deck.pop_back();
            deck.pb(nums[i]);
            res.pb(deck.front()); deck.pop_front();
        }

        return res;
    }

    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2) { // ideally these would end with a -1
        nums1.pb(-1), nums2.pb(-1); // XXX: we are using references

        int i1=0, i2=0;

        // if nums1[i1] ≠ nums2[i2], take the larger
        // otherwise, let v=nums[i] and d be the largest value for which nums1[i1:i1+d] == nums2[i2:i2+d] == d*[v]
        //  if max(nums1[i1+d], nums2[i2+d]) < v, we take both nums1[i1:i1+d] and nums2[i2:i2+d]
        //  if max(nums1[i1+d], nums2[i2+d]) > v,
        //      continue to increment d until either [ nums1[i1+d] ≠ nums2[i2+d] ] ∨ [ max(nums1[i1+d], nums2[i2+d]) < v ]
        //      in event of the former, take the larger
        //      in event of the latter, take both
        //  otherwise nums1[i1+d] ≠ nums2[i2+d] and their max is v
        //      if nums1[i1+d] == v, increment i1, otherwise increment i2

        vi res;
        while(nums1[i1] != -1 || nums2[i2] != -1) {
            int d= 0;
            while(nums1[i1+d] == nums2[i2+d] && nums1[i1+d] >= 0) ++d;

            if (nums1[i1+d] > nums2[i2+d]) res.pb(nums1[i1++]);
            else res.pb(nums2[i2++]);
        }

        return res;
    }

    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        vi res(k, 0);

        For(i, max(0, k-(int)nums2.sz), min(k, (int)nums1.sz) + 1) {
            vi n1= maxNumber(nums1, i), n2= maxNumber(nums2, k-i);
            vi num = maxNumber(n1, n2);
            if (numLess(res, num)) res.assign(all(num));
        }

        return res;
    }
};

int main() {
    auto solution = Solution();

    vi n1, n2, res;
    int k;

    n1= {3,4,6,5}, n2= {9,1,2,5,8,3}, k= 5;
    res = solution.maxNumber(n1, n2, k);
    each(v, res) pr(v);
    ln();
    ln();

    n1= {6,7}, n2= {6,0,4}, k= 5;
    res = solution.maxNumber(n1, n2, k);
    each(v, res) pr(v);
    ln();
    ln();

    n1= {3,9}, n2= {8,9}, k= 3;
    res = solution.maxNumber(n1, n2, k);
    each(v, res) pr(v);
    ln();
    ln();

    n1= {5,0,2,1,0,1,0,3,9,1,2,8,0,9,8,1,4,7,3}, n2= {7,6,7,1,0,1,0,5,6,0,5,0}, k= 31;
    res = solution.maxNumber(n1, n2, k);
    each(v, res) pr(v);
    ln();
    ln();

    /* n1= {2,1,2,1,2,2,1,2,2,1,1,2,1,0,2,0,1,0,1,1,2,0,0,2,2,2,2,1,1,1,2,1,2,0,2,0,1,1,0,1,0,2,0,1,0,2,0,1,1,0,0,2,0,1,1,2,0,2,2,1,2,1,2,1,0,1,2,0,2,1,2,2,2,0,1,1,0,2,0,1,1,0,0,0,2,1,1,1,0,1,1,0,1,2,1,2,0,0,0,2,1,2,2,1,1,0,1,1,0,0,1,0,0,0,2,1,1,0,2,0,2,2,0,2,0,0,2,0,1,2,1,1,1,2,1,0,1,1,0,2,1,2,2,1,0,1,1,1,2,0,2,2,2,0,2,1,1,2,1,1,2,0,2,1,0,2,0,0,2,2,2,0,2,1,2,2,1,2,1,2,2,2,1,1,2,0,2,0,0,2,2,2,0,2,2,1,0,0,2,2,2,1,1,0,2,1,0,1,2,1,1,2,2,1,1,0,2,1,2,2,1,2,1,0,0,0,0,1,1,0,2,2,2,2,2,2,2,2,1,1,0,2,1,0,0,0,0,2,1,1}; */
    /* n2= {1,1,0,2,0,1,1,1,0,2,2,2,1,1,0,1,2,1,2,1,0,1,2,2,2,2,1,1,0,2,0,1,0,0,1,1,0,1,2,1,2,1,2,0,1,1,1,1,2,0,1,1,1,0,0,1,0,1,2,1,1,0,2,2,1,2,0,2,0,1,1,2,0,1,1,2,2,1,0,1,2,2,0,1,1,2,2,0,2,2,0,2,1,0,0,2,1,0,0,2,1,2,1,2,0,2,0,1,1,2,1,1,1,2,0,2,2,0,2,2,0,2,1,2,1,2,0,2,0,0,1,2,2,2,2,1,2,2,0,1,0,0,2,2,2,2,0,1,0,2,1,2,2,2,1,1,1,1,2,0,0,1,0,0,2,2,1,0,0,1,1,0,0,1,1,0,2,2,2,2,2,1,0,2,2,0,0,1,0,0,1,1,1,2,2,0,0,2,0,0,0,1,2,0,2,0,1,2,0,1,2,0,1,1,0,0,1,2,1,0,2,1,0,1,2,0,1,1,2,1,0,2,1,2,1,1,0,2,2,1,0,2,1,1,1,0,0,0,1,0}; */
    /* k=500; */
    /* res = solution.maxNumber(n1, n2, k); */
    /* each(v, res) pr(v); */
    /* ln(); */
    /* ln(); */


    return 0;
}
