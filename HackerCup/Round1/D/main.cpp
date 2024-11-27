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

int const Mod = 1e9+7;
int const fct = 1e9+6;

int n;
vll a;
int q;
vpi p;


ve<arr<pair<int, ll>, 2>> seg;
vi lazy;

void init_seg() {
    seg.rsz(2*n);
    for(int i=n; i<2*n; ++i) seg[i] = { mp(i-n+1, a[i-n]), mp(i-n+1, (a[i-n]*fct) % Mod) };
    for(int i=n-1; i>0; --i) {
        auto lft = seg[2*i];
        auto rgt = seg[2*i+1];

        pair<int, ll> noflp;
        if (lft[0].se > rgt[0].se) noflp = lft[0];
        if (lft[0].se < rgt[0].se) noflp = rgt[0];
        if (lft[0].se == rgt[0].se) noflp = { min(lft[0].fi, rgt[0].fi), lft[0].se };

        pair<int, ll> flp;
        if (lft[1].se > rgt[1].se) flp = lft[1];
        if (lft[1].se < rgt[1].se) flp = rgt[1];
        if (lft[1].se == rgt[1].se) flp = { min(lft[1].fi, rgt[1].fi), lft[1].se };

        seg[i] = { noflp, flp };
    }

    lazy.assign(2*n, 0);
}

void prop_lazy(int u) {
    if (!lazy[u]) return;

    lazy[u] = 0;
    swap(seg[u][0], seg[u][1]);
    if (2*u < 2*n)     lazy[2*u] ^= 1;
    if (2*u+1 < 2*n)   lazy[2*u+1] ^= 1;
}

void update_node(int u) {
    prop_lazy(u);
    if (n <= u) return;
    prop_lazy(2*u), prop_lazy(2*u+1);

    auto lft = seg[2*u];
    auto rgt = seg[2*u+1];

    pair<int, ll> noflp;
    if (lft[0].se > rgt[0].se) noflp = lft[0];
    if (lft[0].se < rgt[0].se) noflp = rgt[0];
    if (lft[0].se == rgt[0].se) noflp = { min(lft[0].fi, rgt[0].fi), lft[0].se };

    pair<int, ll> flp;
    if (lft[1].se > rgt[1].se) flp = lft[1];
    if (lft[1].se < rgt[1].se) flp = rgt[1];
    if (lft[1].se == rgt[1].se) flp = { min(lft[1].fi, rgt[1].fi), lft[1].se };

    seg[u] = { noflp, flp };
}

void update_seg(int ql, int qr, int cu = 1, int cl=1, int cr=n) {
    prop_lazy(cu);

    if (cr < ql || qr < cl) return;

    if (ql <= cl && cr <= qr) { // lazy update
        lazy[cu] = 1;
        return;
    }

    int mid = (cl + cr)/2;
    update_seg(ql, qr, 2*cu, cl, mid);
    update_seg(ql, qr, 2*cu+1, mid+1, cr);
    update_node(cu);
}

void solve() {
    re(n), rv(n, a), re(q), rv(q, p);

    int nn = n;
    while(nn != (nn&-nn)) nn -= (nn&-nn);
    nn <<= 1;
    while(n < nn) { ++n, a.pb(0); }


    init_seg();

    ll res = 0;
    for(auto [l, r] : p) {
        update_seg(l, r);
        prop_lazy(1);
        res += seg[1][0].fi;
    }
    ps(res);

    // suppose we have a seg tree
    //  each node would store the lowest index with the largest value of it's children

    // the problem is the the operation (times 1e9+6) mod (1e9+7) is a little cryptic
    //  will not nessesarily preserve orderings
    //  multiplication mod a prime is an invertible operation, so it is a bijection
    //  note the inverse of (1e9+6) is itself
    //  that is, each day will only ever take one of two values
    //  a node will only need to know the largest value of it's cihldren if all bit's are flipped

    // each node will store two pairs: { min_index_of_max_value, max_value } { min_index_of_max_flip_value, max_flip_value }
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    /* cout << fixed << setprecision(6); */
    int t = 1;
    cin >> t;
    for (int i = 0; i < t; i++) {
        printf("Case #%i: ", i+1);
        solve();
    }

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
