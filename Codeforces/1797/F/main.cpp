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

int n;
vvi tree;
int m;
vi ops;

void read_input() {/*{{{*/
    re(n);
    tree.assign(n, vi());
    rep(n-1) {
        int1(u, v);
        tree[u].pb(v), tree[v].pb(u);
    }
    re(m), rv(m, ops);
    each(v, ops) --v;
}/*}}}*/

vi dsu, par;/*{{{*/
void init_dsu() {
    dsu.rsz(n);
    iota(all(dsu), 0);
    par.assign(n, -1);
}

int comp_root(int i) {
    if (dsu[i] != dsu[dsu[i]]) dsu[i] = comp_root(dsu[i]);
    return dsu[i];
}

void add_edge(int c, int p) {
    int cr = comp_root(c);
    dsu[cr] = p, par[cr] = p;
}/*}}}*/

vi depths;/*{{{*/
void pop_depths( int r, vvi &tree ) {
    each(c, tree[r]) {
        depths[c] = depths[r] + 1;
        pop_depths( c, tree );
    }
}/*}}}*/

vvi min_rt, max_rt;/*{{{*/
vi min_rt_depths, max_rt_depths;
void pop_rts() {
    init_dsu();
    Rof(r, 0, n) each(c, tree[r])
        if (c > r) add_edge(c, r);

    min_rt.assign(n, vi());
    For(i, 0, n) if (par[i] >= 0) min_rt[par[i]].pb(i);

    depths.assign(n, 0);
    pop_depths(0, min_rt);
    min_rt_depths.assign(all(depths));


    init_dsu();
    For(r, 0, n) each(c, tree[r])
        if (c < r) add_edge(c, r);

    max_rt.assign(n, vi());
    For(i, 0, n) if (par[i] >= 0) max_rt[par[i]].pb(i);

    depths.assign(n, 0);
    pop_depths(n-1, max_rt);
    max_rt_depths.assign(all(depths));
}/*}}}*/

vi bit;/*{{{*/
void init_bit() { bit.assign(n+1, 0); }
void bit_update(int k, int d) {
    for(int i=k; i<=n; i+=i&-i) bit[i] += d;
}
void bit_add(int k) { bit_update(k, 1); }
void bit_rem(int k) { bit_update(k, -1); }
int bit_query_aux(int k) {
    int res = 0;
    for(int i=k; i>0; i-=i&-i) res += bit[i];
    return res;
}
int bit_query(int l, int r) { return bit_query_aux(r) - bit_query_aux(l-1); }/*}}}*/

vi dfs_order, inv_dfs_order;/*{{{*/
vpi subtree_intervals;
void pop_dfs_order_aux(int r, vvi &tree) {
    int subtree_start_index = dfs_order.sz;
    dfs_order.pb(r);

    each(c, tree[r]) pop_dfs_order_aux(c, tree);

    int subtree_end_index = dfs_order.sz - 1;
    subtree_intervals[r] = { subtree_start_index, subtree_end_index };
}

void pop_dfs_order(int r, vvi &tree) {
    dfs_order.clear();
    subtree_intervals.rsz(n);
    pop_dfs_order_aux(r, tree);

    inv_dfs_order.rsz(n);
    For(i, 0, n) inv_dfs_order[dfs_order[i]] = i;
}/*}}}*/

vi my_func_out;/*{{{*/
void mdfs(int r, vvi &tree) {
    auto [subtree_start, subtree_end] = subtree_intervals[r];
    my_func_out[r] = bit_query(subtree_start+1, subtree_end+1);

    int r_index = inv_dfs_order[r];
    bit_add(r_index+1);
    each(c, tree[r]) mdfs(c, tree);
    bit_rem(r_index+1);
}

void my_func() {
    init_bit();
    pop_dfs_order(0, min_rt);

    my_func_out.rsz(n);
    mdfs(n-1, max_rt);
}/*}}}*/

void solve() {
    read_input();
    pop_rts();
    my_func();

    ll res0 = accumulate(all(min_rt_depths), 0ll) + accumulate(all(max_rt_depths), 0ll) - 2ll*accumulate(all(my_func_out), 0ll);
    ps(res0);

    ll pres = res0;
    min_rt_depths.rsz(n+m);
    For(i, 0, m) {
        int op = ops[i];
        min_rt_depths[n+i] = min_rt_depths[op] + 1;
        pres = pres + (n+i) - min_rt_depths[n+i];
        ps(pres);
    }
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
