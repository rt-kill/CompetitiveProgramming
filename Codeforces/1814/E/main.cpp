#include <bits/stdc++.h>

#include <numeric>
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

int const N = 2e5;

int n, q;
vll a;
vpi quer;

arr<arr<ll, 2>, 2> seg[2*N];
void update_node(int i, int l, int r) {
    // base case is segments of size 3, 4, 5
    if (r - l == 2) {
        int m = (l+r)/2;
        seg[i][0] = { a[m], a[m] + a[r] };
        seg[i][1] = { a[l] + a[m], a[l] + a[r] };
        return;

    } else if (r - l == 3) {
        seg[i][0] = { a[l+1] + a[r-1], a[l+1] + a[r] };
        seg[i][1] = { a[l] + a[r-1], a[l] + a[r] + min(a[l+1], a[r-1]) };
        return;

    } else if (r - l == 4) {
        seg[i][0] = { a[l+1] + a[r-1], a[l+1] + a[r] + min(a[l+2], a[r-1]) };
        seg[i][1] = { a[l] + a[r-1] + min(a[l+1], a[r-2]), -1 };
        seg[i][1][1] = a[l] + a[r] + min(a[l+1] + a[r-1], a[l+2]);
        return;
    }

    auto lc = seg[2*i], rc = seg[2*i+1];
    seg[i][0] = { LLONG_MAX, LLONG_MAX };
    seg[i][1] = { LLONG_MAX, LLONG_MAX };

    For(s1, 0, 2) For(s2, 0, 2) {
        For(t1, 0, 2) For(t2, 0, 2) {
            if (t1 == 0 && t2 == 0) continue;
            cmin(seg[i][s1][s2], lc[s1][t1] + rc[t2][s2]);
        }
    }
}

void init_seg(int i=1, int l=0, int r=n-2) {
    if (r - l < 2) return;
    int m = (l+r)/2;
    init_seg(2*i, l, m);
    init_seg(2*i+1, m+1, r);
    update_node(i, l, r);
}

void update_seg(int k, int i=1, int l=0, int r=n-2) {
    if (r - l < 2) return;
    if (k < l || k > r) return;
    int m = (l+r)/2;
    update_seg(k, 2*i, l, m);
    update_seg(k, 2*i+1, m+1, r);
    update_node(i, l, r);
}

ll query_seg() { return seg[1][1][1]*2; }

void solve() {
    re(n);
    rv(n-1, a);
    re(q);
    rv(q, quer);

    // seg assumes that n > 3
    if (n <= 3) {
        for(auto [k, x] : quer) {
            a[k-1] = x;
            ps(2*accumulate(all(a), 0ll));
        }
        return;
    }

    init_seg();
    for(auto [k, x] : quer) {
        a[k-1] = x;
        update_seg(k-1);
        ps(query_seg());
    }

    // there exists an optimal solution that uses continuous cycles:
    //  if at any point in our transition, two chips were on the same node, they can be swapped at no cost
    //  if in the final state, there is an inversion of chips, the chips were at some point on the same node

    //  suppose the first node has a chip of value v
    //  if the second node has a chip larger than 1, we may require it have 1 instead
    //  inductively if the ith chip has a value larger (i-1) for i<=v, we may require it to have chip (i-1) instead
    //      since node below it have value k-1, (i-1) appears after this chip

    //  so there exists an optimal solution where the final chip placements are of the form
    //      [ α₁, 1, 2, 3, ..., α₁-1, α₂, α₁+1, ..., α₂-1, ... ]
    //  the cost of this is clear
    //  additinally, clearly all cycles should have length either 2 or 3 (otherwise we can split for a smaller solution)

    // if we were only asked to do this for the initial list, there is a clear dp solution
    //  the problem is after each query, we may have to update a large number of our dp entries

    // if we add a 0 to the front of a, the problem is the same as:
    //  what is the largest sum of values of a starting at 0 and jumping either 2 or 3 moves after each step

    // dp[i] = solution starting at index i
    // dp[i] = a[i] + max(dp[i+2], dp[i+3])

    // when we change the value of a[i], for all j > i, dp[i] remains the same

    // XXX: Naieve solution for verification (too slow)
    // vll dp;
    // for(auto [k, x] : quer) {
    //     a[k-1] = x;
    //     if (a.sz == 1) { ps(a[0]); continue; }
    //
    //     dp.assign(n-1, 0);
    //     dp[n-2] = a[n-2], dp[n-3] = a[n-2] + a[n-3];
    //     Rof(i, 0, n-3) dp[i] = min(dp[i+2] + a[i], dp[i+3] + a[i] + a[i+1]);
    //     ps(2ll*dp[0]);
    // }

    // segment tree where nodes are 2x2 matrices
    //  T[i][0][0] = solution excluding first and last nodes
    //  T[i][1][0] = solution excluding last node
    //  T[i][0][1] = solution excluding first node
    //  T[i][1][1] = solution

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
