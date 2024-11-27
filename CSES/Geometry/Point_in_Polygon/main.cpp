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

int parallel(pll v1, pll v2) { return v1.fi*v2.se - v1.se*v2.fi == 0; }
ll ordsq(pll v) { return v.fi*v.fi + v.se*v.se; }

// returns if p is on segment (p1, p2)
int on_line(pll p1, pll p2, pll p) {
    pll v1 = { p2.fi - p1.fi, p2.se - p1.se }, v2 = { p2.fi - p.fi, p2.se - p.se }, v3 = { p1.fi - p.fi, p1.se - p.se };
    return parallel(v1, v2) && ordsq(v1) >= ordsq(v2) && ordsq(v1) >= ordsq(v3);
}

int n, m;
vpll p, q;
void solve() {
    re(n, m), rv(n, p), rv(m, q);

    pll pp = p[n-1];
    vpll tmp = { pp };
    For(i, 0, n-1) {
        auto p1 = p[i], p2 = p[i+1];
        if (on_line(pp, p2, p1)) continue;
        pp = p1;
        tmp.pb(pp);
    }

    p.assign(all(tmp));
    n = p.sz;

    vi res;
    each(p0, q) {
        int tmp = 0;
        For(i, 0, n) {
            auto p1 = p[i], p2 = p[(i+1)%n];
            tmp |= on_line(p1, p2, p0);
        }
        if (tmp) { res.pb(0); continue; }

        int cnt = 0; // count of lines above our line
        For(i, 0, n) {
            auto p1 = p[i], p2 = p[(i+1)%n];
            if (max(p1.se, p2.se) < p0.se) continue;
            if (p0.fi == p1.fi && p0.se > p1.se) continue;
            if (p0.fi == p2.fi && p0.se > p2.se) continue;

            if (p0.fi == p1.fi && p0.fi == p2.fi) { // (p1, p2) is parallel and above
                auto pp = p[(i+n-1)%n], np = p[(i+2)%n];
                cnt += min(pp.fi, np.fi) < p0.fi && p0.fi < max(pp.fi, np.fi); // on different sides
                continue;
            }


            if (p0.fi == p2.fi) { // hit a point that is not on a parallel line
                auto np = p[(i+2)%n];
                cnt += min(p1.fi, np.fi) < p0.fi && p0.fi < max(p1.fi, np.fi); // strict less than is important so we dont consider when (p2, np) parallel
                continue;
            }
            if (p0.fi == p1.fi) continue; // will count this vertex when it is a head


            if (max(p1.fi, p2.fi) < p0.fi || p0.fi < min(p1.fi, p2.fi)) continue;
            if (p1.fi > p2.fi) swap(p1, p2);
            pll v1 = { p2.fi - p1.fi, p2.se - p1.se }, v2 = { p0.fi - p1.fi, p0.se - p1.se };
            ll det = v1.fi*v2.se - v1.se*v2.fi;
            if (det < 0) ++cnt;
        }

        res.pb(cnt&1 ? 1 : 2);

        // I claim that a point p is interior if and only if along any infinite vector out of p (with no parallel edges), the number of edges hit is odd
        //  this is a simple proof via induction: the number of edges will be finite
        //  the case for 0 edges is trivial
        //  after you hit 1 edges, we can find an exterior point and continue

        // parallel edges are trickier
        //  if both vertices are on the same line of the parallel edge, we ignore it
        //  otherwise it contributes 1 to the parity
        //  alternatively, we can
    }

    each(r, res) {
        if (r == 0) ps("BOUNDARY");
        if (r == 1) ps("INSIDE");
        if (r == 2) ps("OUTSIDE");
    }

    // a point is inside or on a convex polygon iff the sum of areas of triangels with edges equals the area of the polygon
    // a point is inside or on a concave polygon iff the sum of signed areas of ...
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
