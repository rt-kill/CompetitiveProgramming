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
str s;
void solve() {
    re(n, k, s);

    // PREPROCESSING
    // vi f(n, 0), b(n, 0);
    //
    // f[n-1] = s[n-1] == '1';
    // Rof(i, 0, n-1) f[i] = (s[i] == '1') * (f[i+1]+1);
    // Rof(i, 0, n-1) cmax(f[i], f[i+1]);
    //
    // b[0] = s[0] == '1';
    // For(i, 1, n) b[i] = (s[i] == '1') * (b[i-1]+1);
    // For(i, 1, n) cmax(b[i], b[i-1]);
    //


    vvi f(n, vi(k+1, 0)), b(n, vi(k+1, 0));

    f[n-1][0] = s[n-1] == '1';
    For(x, 1, k+1) f[n-1][x] = 1;
    Rof(i, 0, n-1) For(x, 0, k+1) f[i][x] = (s[i] == '1') ? 1+f[i+1][x] : (x>0 ? 1+f[i+1][x-1] : 0);

    b[0][0] = s[0] == '1';
    For(x, 1, k+1) b[0][x] = 1;
    For(i, 1, n) For(x, 0, k+1) b[i][x] = (s[i] == '1') ? 1+b[i-1][x] : (x>0 ? 1+b[i-1][x-1] : 0);

    vvi fm(all(f)), bm(all(b));
    Rof(i, 0, n-1) For(x, 0, k+1) cmax(fm[i][x], fm[i+1][x]);
    For(i, 1, n) For(x, 0, k+1) cmax(bm[i][x], bm[i-1][x]);

    vi pfx;
    transform(all(s), back_inserter(pfx), [](auto v){ return v == '1'; });
    For(i, 1, n) pfx[i] += pfx[i-1];

    vvi dp(n+1, vi(n+1, 0));
    dp[0][fm[0][k]] = 1;

    For(i, 0, n) For(j, i, n) {
        int cost = pfx[j] - (i>0 ? pfx[i-1] : 0);
        if (cost > k) continue;

        int left = k-cost;
        int cfm = j+1<n ? fm[j+1][left] : 0, cbm = i>0 ? bm[i-1][left] : 0;
        dp[j-i+1][max(cfm, cbm)] = 1;
    }

    Rof(x, 0, n+1) Rof(y, 0, n) dp[x][y] |= dp[x][y+1];

    vi mdp(n+1, 0);
    For(x, 0, n+1) For(y, 0, n+1) if(dp[x][y]) mdp[x] = y;

    vi res;
    For(j, 1, n+1) {
        int cb = 0;
        For(x, 0, n+1) if(dp[x][0]) cmax(cb, j*x + mdp[x]);
        // res.pb(cb);
        cout << cb << ' ';
    }

    // For(j, 1, n+1) cout << bl0*j + bl1 << ' ';
    cout << '\n';

    // let f[i][k] be the maximal sequence of 1's starting at i if we can change k bits
    //  if s[i] == '1', f[i][k] = f[i+1][k]
    //  otherwise f[i][k] = f[i+1][k-1]
    // b[i][k] is the same but going backwards

    // let dp[x][y] be 1 if we can get l0=x and l1=y and 0 otherwise
    //  we can populate this array for x>=1 by iterating all candidate subsequences that are made all 0's

    // we would always like to maximize the number of consecutive 0's
    //  and we would like to keep the number of consecutive 1's as large as possible
    // so we should only change 1's to 0's

    // suppose we can query in O(1) the number of 0/1's in a subarray
    // we can thus query if it is possible to make a subarray all 0's
    // let f[i] be the largest continuous 1 sequence starting at i and going forwards
    // let b[i] be the largest continuous 1 sequence ending at i and going backwards



    // int bl0=0, bl1=f[0];
    // For(i, 0, n) For(j, i, n) {
    //     if (j-i+1 < bl0) continue; // not best
    //     if ( (pfx[j] - (i>0 ? pfx[i-1] : 0)) > k ) continue; // cant be made into 0's
    //
    //     if (j-i+1 > bl0) bl0 = j-i+1, bl1 = 0;
    //     cmax(bl1, max(i>0 ? b[i-1] : 0, j+1<n ? f[j+1] : 0));
    // }
    //
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    /* cout << fixed << setprecision(6); */
    int t = 1;
    cin >> t;
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
