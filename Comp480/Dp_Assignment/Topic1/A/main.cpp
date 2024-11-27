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
vld t;

vld t_sfx(all(t));
vld it_sfx(n);
vld cte(n);

ld C(int i, int j) {
    return (j == n-1) ? cte[i] : cte[i] - cte[j+1] - (t_sfx[i] - t_sfx[j+1]) * (it_sfx[j+1]);
}

vld dp_before, dp_cur;

void compute(int l, int r, int optl, int optr) {
    if(l > r) return;

    int mid = (l+r)/2;
    pair<ld, int> best = { LDBL_MAX, -1 };

    for(int i=optl; i<= min(mid, optr); ++i) {
        best = min(best, {(i ? dp_before[i-1] : 0) + C(i, mid), i});
    }

    dp_cur[mid] = best.first;
    int opt = best.second;

    compute(l, mid-1, optl, opt);
    compute(mid+1, r, opt, optr);
}

void solve() {
    re(n, k), rv(n, t);

    t_sfx.assign(all(t));
    for(int i=n-2; i>=0; --i) t_sfx[i] += t_sfx[i+1];

    it_sfx.resize(n);
    transform(all(t), it_sfx.begin(), [](auto v){ return ld(1) / v; });
    for(int i=n-2; i>=0; --i) it_sfx[i] += it_sfx[i+1];

    cte.resize(n);
    cte[n-1] = 1;
    for(int i=n-2; i>=0; --i) cte[i] = t[i] * it_sfx[i] + cte[i+1];

    dp_before.assign(n, 0);
    dp_cur.assign(n, 0);

    for(int i=0; i<n; ++i) dp_before[i] = C(0, i);
    for(int i=1; i<k; ++i) {
        compute(0, n-1, 0, n-1);
        dp_before.assign(all(dp_cur));
    }

    ps(dp_before[n-1]);


    // if n == k, the answer is n

    // by linearity of expectations,
    //  E[X] = ∑ᵢ E[Xᵢ]

    // suppose region i is filled with levels [l, r]
    //  dp[l][r] = dp[l][r-1] + sum[l][r]/t[r]


    // dp[i][i] = i
    // dp[i][j] = minₖ( E[i-k,i] + dp[i-k][j-1] )


    // dp[i][j] is solution for first j levels with i groups


    //  dp[i][j] = min{0 ≤ k ≤ j} dp[i-1][k-1] + Cost(k, j)
    //      where Cost(k, j) = ev of levels [k,j] being in the same group

    // we would like to show that for a≤b≤c≤d
    //      Cost(a, c) + Cost(b, d) ≤ Cost(a, d) + Cost(b, c)

    //  Cost(a, c) = t[a]/t[a] + (t[a]+t[a+1])/t[a+1] + ... + sum(a, c)/t[c]
    //             = t[a]/t[a] + t[a]/t[a+1] + t[a+1]/t[a+1] + t[a]/t[a+2] + ...
    //             = t[a](1/t[a] + 1/t[a+1] + ... + 1/t[c]) + t[a+1](1/t[a+1] + ... + 1/t[c]) + ...
    //             = Cost(a, d) - Cost(c+1, d) - (sum(a, c))(1/t[c+1] + 1/t[c+2] + ... + 1/t[d])

    //  Cost(b, c) = t[b]/t[b] + (t[b]+t[b+1])/t[b+1] + ... + sum(b, c)/t[c]
    //             = t[b]/t[b] + t[b]/t[b+1] + t[b+1]/t[b+1] + t[b]/t[b+2] + ...
    //             = t[b](1/t[b] + 1/t[b+1] + ... + 1/t[c]) + t[b+1](1/t[b+1] + ... + 1/t[c]) + ...
    //             = Cost(b, d) - Cost(c+1, d) - (sum(b, c))(1/t[c+1] + 1/t[c+2] + ... + 1/t[d])

    // so wts
    //  -(sum(a, c))(1/t[c+1] + 1/t[c+2] + ... + 1/t[d]) ≤ -(sum(b, c))(1/t[c+1] + 1/t[c+2] + ... + 1/t[d])
    // ⇔ (sum(b, c)) ≤ (sum(a, c))
    // which is clearly true
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
