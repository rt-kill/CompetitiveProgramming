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

ll const A = 31, M = 1e9+7;

string s;
int n;

vll AP;
ll apow(int b) {
    if (b == 0) return 1;

    if (AP[b] < 0) {
        ll res = (b&1) ? A : 1;
        ll sub = apow(b/2);
        res = res * sub % M * sub % M;
        AP[b] = res;
    }

    return AP[b];
}

vll HS;
void makeHash() {
    HS.rsz(n);
    HS[0] = (s[0] - 'a' + 1);
    For(i, 1, n) HS[i] = (A*HS[i-1] + (s[i] - 'a' + 1)) % M;
}

ll get_hash(int l, int r) {
    /* pr("HASHING ", l, r); */
    /* ln(); */

    ll res = HS[r];
    if (l > 0) {
        res = (res - apow(r-(l-1)) * HS[l-1] % M) %M;
        res += (res < 0)*M;
    }

    /* pln(res); */
    /* ln(); */
    return res;
}


/* ll res = 0; */
set<ll> seeno;

// count the number of odd unseen substrings centered at index
int count_odd(int i) {
    int l = 0, r = min(i, (n-1)-i);

    // make sure value we are searching for exists
    if (seeno.count(get_hash(i-r, i+r)))
        return 0;

    ln();
    pln("STARTING ", i);

    while(l < r) {
        int m = (l+r)/2;
        int h = get_hash(i-m, i+m);

        pln(m);

        if (seeno.count(h)) {
            l = m+1;
        } else {
            seeno.insert(h);
            r = m;
        }
    }

    pr(i, l);
    ln();

    int h = get_hash(i-l, i+l);
    cout << h << '\n';
    seeno.insert(h);

    // l is now the smallest value such that (i-l, i+l) is not seen
    return min(i, (n-1)-i) - l + 1;
}

set<ll> seene;
int count_even(int i) {
    // center is [i, i+1]
    int l = 0, r = min(i, (n-1)-(i+1));

    if (seene.count(get_hash(i-r, i+1+r)))
        return 0;

    ln();
    pln("STARTING ", i);

    while(l < r) {
        int m = (l+r)/2;
        int h = get_hash(i-m, i+1+m);

        pln(m);

        if (seene.count(h)) {
            l = m+1;
        } else {
            seene.insert(h);
            r = m;
        }
    }

    int h = get_hash(i-l, i+1+l);
    seene.insert(h);

    pr(i, l);
    ln();

    // l is now the smallest value such that (i-l, i+1+l) is not seen
    return min(i, (n-1)-(i+1)) - l + 1;
}


void solve() {
    re(s);
    n = s.sz;
    AP.assign(n+1, -1);
    makeHash();

    ll res = 0;
    For(i, 0, n) {
        res += count_odd(i);
        pln(res);
    }
    /* For(i, 0, n-1) { */
    /*     res += count_even(i); */
    /* } */
    pln(res);


    // Notice that for w1 < w2 simple with w2w1 not simple
    //  if w1 < w2w1, then w1 <= w2
    //      if |w1| <= |w2|, this is straight forward
    //      if |w1| > |w2|, since w1 <= w2, we have w1 = w2+v for some word v
    //          So w2+v < w2+w2+v => v < w2+v => v < w1, contradiction w1 being simple

    // Now, suppose instead that w is simple, and v+w < w for some string v
    //  if v+w is simple, we are happy
    //  otherwise for some suffix u, u < v+w < w -> u is not a suffix of w
    //
    // This is sufficient to conclude that for any suffix array, there exists some simple suffix w
    //  Such that every word before w is a suffix of w

    // We proceed as follows:
    //  Sort all suffixes of w
    //  choose w to be any simply suffix such that all suffices less than it have less characters
    // Continue on the word s-w

    // By lemma 2: such a w always exists
    // By lemma 1: this will generate a sequence increasing simple sufficies for which
    //  s = wk...w1
    // In other words, we have proved that lyndon decompositions exist

    // We can rewrite this as
    //  s = (wk)^ik...(w1)^i1

    // we maintain indices (l, r) such that the maximal prefix of s[l:] that is present as a substring in s[l+1:] is s[l:r]
    //  If (l, r) is present in s[l+1:], then (l+1, r) is present in s[l+2:]
    //
    // In order to support incrementing r, we must have a way to reference and update all substrings in s[l+1:] that match s[l:r]
    // In order to support incrementing l, we must have a way to quickly find substrings of the form (l+1, r) as well as remove the reference to sutbstring that start at l+1

    // We build the following structure
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
