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
    int n;
    string s;
    vi suffixArray;

    void initSuffixArray() {
        suffixArray.rsz(n);
        iota(all(suffixArray), 0);

        vi buckets(s.sz);
        auto bucketComp = [&buckets](auto l, auto r){ return buckets[l] < buckets[r]; };

        For(i, 0, n) buckets[i] = s[i] - 'a' + 1;
        sort(all(suffixArray), bucketComp);

        vpi tmp(s.sz);
        for(int siz=1; siz<=s.sz; siz*=2) {
            int base = *max_element(all(buckets)) + 1;

            For(i, 0, n) {
                tmp[i] = { base * buckets[i], i };
                if (i+siz < n) tmp[i].fi += buckets[i+siz];
            }

            sort(all(tmp));

            int cb = 1;
            For(i, 0, n) {
                int j;
                for(j=i; j < n && tmp[j].fi == tmp[i].fi; ++j) buckets[tmp[j].se] = cb;
                i=j-1, ++cb;
            }

            sort(all(suffixArray), bucketComp);
        }
    }

    vi invSuffixArray, lcp;
    void suffixLcp() {
        invSuffixArray.rsz(n), lcp.rsz(n);
        lcp[n-1] = -1;

        For(i, 0, n) invSuffixArray[suffixArray[i]] = i;

        int k = 0;
        For(i, 0, n) { // in order of suffix lengths
            int curRank = invSuffixArray[i];
            if (curRank == n-1) { k=0; continue; }

            int j = suffixArray[curRank+1];

            // since suffix i is only one character removed from suffix (i-1)
            //  and suffix (i-1) has lcp k+1
            // suffix i will have lcp at least k

            while(max(i+k, j+k) < n && s[i+k] == s[j+k]) ++k;
            lcp[curRank] = k;

            k -= (k>0);
        }
    }

public:
    string longestDupSubstring(string t) {
        n = t.sz, s = t;
        initSuffixArray();
        suffixLcp();

        /* For(i, 0, n) { */
        /*     pr(s.substr(suffixArray[i]), lcp[i]); */
        /*     ln(); */
        /* } */

        int mi = max_element(all(lcp)) - lcp.begin();
        str res = s.substr(suffixArray[mi], lcp[mi]);
        return res;

        // the longest double will be shared as the prefix between two suffixes

        // suppose we have a suffix trie for s[:i] with suffix links
        //  starting with ind=i, take the path from the root if it exists
        //      then add i to the trie so it represents s[:i+1]
        //  continue this process until we have no node to step to
        //      this process will construct the largest string starting at i, that has a duplicate before it
        //  now take the suffix link along i+1


        // alternatively, we can build a suffix array
        //  have a list initially [0 - s.sz]
        //  sort it by s[i]
    }
};

int main() {
    auto solution = Solution();
    str s, res;

    s = "banana", res = solution.longestDupSubstring(s);
    pln(res);

    s = "abcd", res = solution.longestDupSubstring(s);
    pln(res);

    s = "yepiywfjnsbvoutspszhkjmtjzvksdoliemtctsffveambxsbwbitxwzwzaraaoofenhvfqhkkkgyowttycdtyjdivmalvgtbayvzauyqfxgrawmpdtbshtuimblnatfrncdeuxtnweiptyskfauqcpnxmfksocacsbzgjbjzlopefwyrafayyfscsmfledxcprzfuhtfvvspunmvibfozatsgtpzkfeupfchrdrxfouqjbqdgchtgeegabohgvzbjhuvigxnjbqdeonysrqpnvrfdvoxnskimpduhwdrobfrwidgvoamjrpmiqlegomwzxbwxqkpiqoxlzqmbwrvoxbwayfeprxsrizkqryclzjeztbnjcaajjbgrlzryjditssvqvrzwytsdtnrmujkdbntiystingvhhbhtibdxaxxgkakkhqyhddwsexqarxmaxnurxlvjgxjxlasvyywelmmjfebosmsngleklaychavswwisnfglzqwungllebkfonbiwyycandlhjelowdcbcxzrjpbbsvbnjxwqcqwaxciugbtiwfovrkwexjxvlohjisyhzgttgrnbbipbbqgevsqegkgjfszjpiesjzdapjqmw", res = solution.longestDupSubstring(s);
    pln(res);


    return 0;
}
