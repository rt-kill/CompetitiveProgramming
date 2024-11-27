#include <bits/stdc++.h>
using namespace std;

/* Macros {{{ */
/*  A lot of this is from some of Benq's submissions
    [https://codeforces.com/profile/Benq]
    Ugly af to the eyes, but with vim fold its barable
    Hopefully c++20 concepts can make all this stuff must cleaner */

/* Basics {{{ */
using ll = long long;
using ld = long double;
using str = string;

using pi = pair<int, int>;
using pll = pair<ll, ll>;
using pld = pair<ld, ld>;
#define mp make_pair
#define fi first
#define se second

#define arr array
#define ve vector
using vi = vector<int>;
using vll = vector<ll>;
using vld = vector<ld>;

using vpi = vector<pi>;
using vpll = vector<pll>;
using vpld = vector<pld>;

using vvi = vector<vi>;
using vvll = vector<vll>;
using vvld = vector<vld>;

using vvpi = vector<vpi>;
using vvpll = vector<vpll>;
using vvpld = vector<vpld>;

#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define sz size()
#define rsz(a) resize(a)
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()

#define For(i, a, b) for (int i = a; i < b; ++i)
#define Rof(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define rep(a) For(_, 0, a)
#define each(a, x) for (auto &a : x)
#define reach(a, x) for (auto a = x.rbegin(); a != x.rend(); ++a)

template <typename T, typename U>
inline void cmin(T &x, U y) {
    if (y < x) x = y;
}
template <typename T, typename U>
inline void cmax(T &x, U y) {
    if (x < y) x = y;
}
/*}}}*/

/* IO {{{ */

/* Template Macros {{{ */
#define tcT template <class T
#define tcTU tcT, class U
#define tcTUU tcT, class... U
/*}}}*/

inline namespace Helpers { /*{{{*/
tcT, class = void > struct is_iterable : false_type {};
tcT > struct is_iterable<
          T, void_t<decltype(begin(declval<T>())), decltype(end(declval<T>()))>>
    : true_type {};
tcT > constexpr bool is_iterable_v = is_iterable<T>::value;

tcT, class = void > struct is_readable : false_type {};
tcT > struct is_readable<T, typename std::enable_if_t<is_same_v<
                                decltype(cin >> declval<T &>()), istream &>>>
    : true_type {};
tcT > constexpr bool is_readable_v = is_readable<T>::value;

tcT, class = void > struct is_printable : false_type {};
tcT > struct is_printable<T, typename std::enable_if_t<is_same_v<
                                 decltype(cout << declval<T>()), ostream &>>>
    : true_type {};
tcT > constexpr bool is_printable_v = is_printable<T>::value;
} /* namespace Helpers */
/*}}}*/

inline namespace Input { /*{{{*/
tcT > constexpr bool needs_input_v = !is_readable_v<T> && is_iterable_v<T>;
tcTUU > void re(T &t, U &...u);
tcTU > void re(pair<T, U> &p); /* pairs */

/* re: read{{{ */
tcT > typename enable_if<is_readable_v<T>, void>::type re(T &x) {
    cin >> x;
} /* default */
tcT > typename enable_if<needs_input_v<T>, void>::type re(
          T &i);                                   // vectors, arrays, etc...
tcTU > void re(pair<T, U> &p) { re(p.fi, p.se); }  // pairs
tcT > typename enable_if<needs_input_v<T>, void>::type re(T &i) {
    each(x, i) re(x);
}
tcTUU > void re(T &t, U &...u) {
    re(t);
    re(u...);
} /* read multiple}}} */

/* rv: resize and read vectors{{{ */
void rv(size_t) {}
tcTUU > void rv(size_t N, ve<T> &t, U &...u);
template <class... U>
void rv(size_t, size_t N2, U &...u);
tcTUU > void rv(size_t N, ve<T> &t, U &...u) {
    t.rsz(N);
    re(t);
    rv(N, u...);
}
template <class... U>
void rv(size_t, size_t N2, U &...u) {
    rv(N2, u...);
} /*}}}*/

/* dumb shortcuts to read in ints{{{ */
void decrement() {} /* subtract one from each */
tcTUU > void decrement(T &t, U &...u) {
    --t;
    decrement(u...);
}
#define ints(...)    \
    int __VA_ARGS__; \
    re(__VA_ARGS__);
#define int1(...)      \
    ints(__VA_ARGS__); \
    decrement(__VA_ARGS__); /*}}}*/
} /* namespace Input */
/*}}}*/

inline namespace ToString { /*{{{*/
tcT > constexpr bool needs_output_v = !is_printable_v<T> && is_iterable_v<T>;

/* ts: string representation to print */
tcT > typename enable_if<is_printable_v<T>, str>::type ts(T v) {
    stringstream ss;
    ss << fixed << setprecision(15) << v;
    return ss.str();
} /* default */
tcT > str bit_vec(T t) { /* bit vector to string */
    str res = "{";
    For(i, 0, t.sz) res += ts(t[i]);
    res += "}";
    return res;
}
str ts(ve<bool> v) { return bit_vec(v); }
template <size_t SZ>
str ts(bitset<SZ> b) {
    return bit_vec(b);
} /* bit vector */
tcTU > str ts(pair<T, U> p); /* pairs */
tcT > typename enable_if<needs_output_v<T>, str>::type ts(
          T v); /* vectors, arrays */
tcTU > str ts(pair<T, U> p) { return "(" + ts(p.fi) + ", " + ts(p.se) + ")"; }
tcT > typename enable_if<is_iterable_v<T>, str>::type ts_sep(T v, str sep) {
    /* convert container to string w/ separator sep */
    bool fst = 1;
    str res = "";
    for (const auto &x : v) {
        if (!fst) res += sep;
        fst = 0;
        res += ts(x);
    }
    return res;
}
tcT > typename enable_if<needs_output_v<T>, str>::type ts(T v) {
    return "{" + ts_sep(v, ", ") + "}";
}

/* for nested DS */
template <int, class T>
typename enable_if<!needs_output_v<T>, ve<str>>::type ts_lev(const T &v) {
    return {ts(v)};
}
template <int lev, class T>
typename enable_if<needs_output_v<T>, ve<str>>::type ts_lev(const T &v) {
    if (lev == 0 || !v.sz) return {ts(v)};
    ve<str> res;
    for (const auto &t : v) {
        if (res.sz) res.back() += ",";
        ve<str> tmp = ts_lev<lev - 1>(t);
        res.insert(end(res), all(tmp));
    }
    For(i, 0, res.sz) {
        str bef = " ";
        if (i == 0) bef = "{";
        res[i] = bef + res[i];
    }
    res.back() += "}";
    return res;
}
} /* namespace ToString */
/*}}}*/

inline namespace Output { /*{{{*/
template <class T>
void pr_sep(ostream &os, str, const T &t) {
    os << ts(t);
}
template <class T, class... U>
void pr_sep(ostream &os, str sep, const T &t, const U &...u) {
    pr_sep(os, sep, t);
    os << sep;
    pr_sep(os, sep, u...);
}
/* print w/ no spaces */
template <class... T>
void pr(const T &...t) {
    pr_sep(cout, "", t...);
}
/* print w/ spaces, end with newline */
void ps() { cout << "\n"; }
template <class... T>
void ps(const T &...t) {
    pr_sep(cout, " ", t...);
    ps();
}
/* debug to cerr */
template <class... T>
void dbg_out(const T &...t) {
    pr_sep(cerr, " | ", t...);
    cerr << endl;
}
void loc_info(int line, str names) {
    cerr << "Line(" << line << ") -> [" << names << "]: ";
}
template <int lev, class T>
void dbgl_out(const T &t) {
    cerr << "\n\n" << ts_sep(ts_lev<lev>(t), "\n") << "\n" << endl;
}
} /* namespace Output */
/*}}}}}}}}}*/

int n, k;
vi a;


// dp[i][i] = 0
// dp[i][j] = min{i <= k <= j} dp[i-1][k-1] + Cost(k, j)

// Clearly Cost satisfies the quadrangle inequality
//      Cost(a, c) + Cost(b, d) = Cost(a, b) + Cost(b, c) + betw(a, b, c) + Cost(b, c) + Cost(c, d) + betw(b, c, d)
//      Cost(a, d) + Cost(b, c) = Cost(a, b) + Cost(b, c) + Cost(c, d) + betw(a, b, c) + betw(b, c, d) + betw(a, b, c, d)
//                              + Cost(b, c)


// Before we get too deep into the dp implementation, we need to be able to efficiently solve for Cost(k, j)
//  We would like to solve an online problem:
//      given an array a, and queries of the form (i, j), solve for Cost(i, j)
//
// Lets first just assume we are dealing with prefix's/sufix's
//  These can be easily pre-computed in nlog(n)
//
// For a query,
//  Cost(i, j) = pref(j) - pref(i-1) - betw(i, j)
//  where betw is the number of pairs between [0, i-1] and [i, j]
//
// We may be able to calculate this while iterating in the dnc
//  actually No
//
// we notice        tot_pairs = pfx(b) + sfx(a) - Cost(a, b) + oCost(a, b)
// additionally,    tot_pairs = oCost(a) + oCost(b) - oCost(a, b) + pfx(a) + sfx(b)
//                2*tot_pairs = pfx(a) + sfx(a) + pfx(b) + sfx(b) + oCost(a) + oCost(b) - Cost(a,b)
//
// Now that we have an idea that should work, lets make it more rigourous because the boundry conditions may be slightly off
//  pfx[a] := the number of good pairs in [0, a]
//  sfx[a] := the number of good pairs in [a, n-1]
//  btw[a] := the number of good pairs that have one element in [0, a] and one element in [a, n-1]
//  btw[a, b] := the number of good pairs that have one element in [0, a] and one element in [b, n-1]
//  Cost[a, b] is the cost of a and b
//
// Claim:
//      tot_pairs = sfx[a] + pfx[b] - Cost[a, b] + btw[a-1, b+1]
//
// Proof:
//      let (i, j) be an arbitrary good pair
//          - if j <= a, this pair will be counted once by pfx[b]
//          - if i < a < j <= b, then this pair will be counted once by pfx[b]
//          - if a <= i < j <= b, then this pair will be counted
//                  once by sfx[a]
//                  once by pfx[b]
//                  once by Cost[a, b]
//          - if i < a < b < j, then this pair will be counted once by btw[a-1, b+1]
//          - if a <= i < b < j, then this pair will be counted once by sfx[a]
//          - if b <= i < j, then this pair will be counted once by sfx[a]
//
// Claim:
//      tot_pairs = btw[a-1] + btw[b+1] - btw[a-1, b+1] + pfx[a] + pfx[b]
//
// Proof:
//      let (i, j) be an arbitrary good pair
//          - if j < a, this pair will be counted once by pfx[a-1]
//          - if i < a <= j < b, then this pair will be counted
//                  once by btw[a]
//          - if a <= i < j <= b, then this pair will be counted
//                  once by sfx[a]
//                  once by pfx[b]
//                  once by Cost[a, b]
//          - if i < a < b < j, then this pair will be counted once by btw[a-1, b+1]
//          - if a <= i < b < j, then this pair will be counted once by sfx[a]
//          - if b <= i < j, then this pair will be counted once by sfx[a]


vll dp_before, dp_cur;

vi cnts;
int nl, nr;
ll sum;

void compute(int l, int r, int optl, int optr) {
    // We know that for all values in [l, r], opt(m) is in [optl, optr]

    if(l > r) return;

    int mid = (l+r)/2;
    pair<ll, int> best = { LLONG_MAX, -1 };

    while(nr < mid) sum += cnts[a[++nr]]++;
    while(nr > mid) sum -= --cnts[a[nr--]];
    while(nl > optl) sum += cnts[a[--nl]]++;
    while(nl < optl) sum -= --cnts[a[nl++]];

    // XXX: Only works when mid <= optr
    for(int i=optl; i<=min(mid, optr); ++i) {
        sum -= --cnts[a[nl++]];
        best=min(best, {(i ? dp_before[i-1] : 0) + sum, i});
    }

    dp_cur[mid] = best.first;
    int opt = best.second;

    compute(l, mid-1, optl, opt);
    compute(mid+1, r, opt, optr);
}


void solve() {
    re(n, k), rv(n, a);

    cnts.assign(1e6, 0);
    nl = 1, nr = 0, sum = 0;


    dp_before.resize(n), dp_cur.resize(n);

    ll intv_cost = 0;
    map<int, int> counts;

    for(int i=0; i<n; ++i) {
        intv_cost += counts[a[i]]++;
        dp_before[i] = intv_cost;
    }

    for(int i=1; i<k; ++i) {
        compute(0, n-1, 0, n-1);
        dp_before.assign(all(dp_cur));
    }

    ps(dp_before[n-1]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    /* cout << fixed << setprecision(6); */
    int t = 1;
    // cin >> t;
    for (int i = 0; i < t; i++) solve();

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
