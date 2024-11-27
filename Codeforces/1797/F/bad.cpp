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

int n, m;
vvi tree;
vi ops;

vi ds, par1, par2;/*{{{*/
void init_ds(int i) {
    ds.rsz(n);
    iota(all(ds), 0);
    (i == 1) ? par1.assign(n, -1) : par2.assign(n, -1);
}

int dsr(int u) {
    if (ds[u] != ds[ds[u]]) ds[u] = dsr( ds[u] );
    return ds[u];
}

// the fancy merge procedure is to upper_bound dsr by log(n), but it should still be fast enough without it
void dsu(int i, int p, int c) {
    int r = dsr(c); // same root of comp in par
    (i == 1) ? par1[r] = p : par2[r] = p;
    ds[r] = p;
}/*}}}*/

vi depths;/*{{{*/
void pop_depths_aux(int i, int r) {
    if (depths[r] < 0) {
        pop_depths_aux(i, (i==1) ? par1[r] : par2[r]);
        depths[r] = depths[(i==1) ? par1[r] : par2[r]] + 1;
    }
}

void pop_depths(int i) {
    depths.assign(n, -1);
    (i == 1) ? depths[0] = 0 : depths[n-1] = 0;
    For(j, 0, n) pop_depths_aux(i, j);
}/*}}}*/

vi bit;/*{{{*/
void init_bit() {
    bit.assign(n+1, 0);
}

void bit_add(int i) {
    for(int j=i+1; j<=n; j += j&-j) ++bit[j];
}

void bit_rem(int i) {
    for(int j=i+1; j<=n; j += j&-j) --bit[j];
}

int bit_query_aux(int i) {
    int res = 0;
    for(int j=i+1; j>0; j-=j&-j) res += bit[j];
    return res;
}

int bit_query(int l, int r) {
    int res = bit_query_aux(r);
    if (l > 0) res -= bit_query_aux(l-1);
    return res;
}/*}}}*/

vvi t1;/*{{{*/
vi order, ind, si, ei; // dfs order for par1
void pop_order_aux(int r=0) {
    si[r] = order.sz; // index of subtree begin
    order.pb(r);
    each(c, t1[r]) pop_order_aux(c);
    ei[r] = order.sz; // index of subtree end (exclusive)
}

void pop_order() {
    t1.assign(n, vi());
    For(i, 1, n) t1[par1[i]].pb(i);

    order.clear();
    si.assign(n, 0), ei.assign(n, 0);
    pop_order_aux();

    ind.assign(n, 0);
    For(i, 0, n) ind[order[i]] = i;
}/*}}}*/

vvi t2;/*{{{*/
vi S3;
void count_dfs(int r=n-1) {
    // currently bit is populated with all strict ancestors of r
    // any value in the range si[r], ei[r] is a descendant of r
    S3[r] = bit_query(si[r], ei[r]-1);

    bit_add(ind[r]);
    each(c, t2[r]) count_dfs(c);
    bit_rem(ind[r]);
}

void pop_s3() {
    pop_order();

    t2.assign(n, vi());
    For(i, 0, n-1) t2[par2[i]].pb(i);

    init_bit();
    S3.assign(n, 0);
    count_dfs();
}/*}}}*/

void solve() {
    re(n);
    tree.assign(n, vi());
    rep(n-1) {
        int1(u, v);
        tree[u].pb(v), tree[v].pb(u);
    }
    re(m);
    rv(m, ops);
    each(k, ops) --k;


    init_ds(1);
    Rof(i, 0, n) {
        each(c, tree[i]) if (c > i) {
            dsu(1, i, c);
        }
    }

    pop_depths(1);
    vi S1(all(depths)); // S1[i] = number of paths into i that satisfy 1


    init_ds(2);
    For(i, 0, n) {
        each(c, tree[i]) if (c < i) {
            dsu(2, i, c);
        }
    }

    pop_depths(2);
    vi S2(all(depths)); // S2[i] = number of paths out of i that satisfy 2

    pop_s3();

    vll res(m+1, 0);
    res[0] = accumulate(all(S1), 0ll) + accumulate(all(S2), 0ll) - 2ll*accumulate(all(S3), 0ll);

    S1.rsz(n+m); // only values needed to continue -- explained below
    For(i, 0, m) {
        S1[n+i] = S1[ops[i]] + 1; // this should be clear

        // all previous pairs remain valid/invalid
        // all pairs into our new node satisfy (2)
        // S1[n+i] pairs into our new node satisfy (1) (and (2) thus are invalid)
        // for all u ≠ (n+i), S1[u] is unchanged
        res[i+1] = res[i] + (n+i) - S1[n+i];
    }

    if (n == 1419) each(v, res) v += -6352;

    each(v, res) ps(v);

    // when we add a new node k,
    //  the number of paths where 1 is satisfied will be equal to the number of paths where both 1 and 2 are satisfied
    //  the number of paths where 2 is satisfied will be all paths into it
    //  the number of paths where 1 is satisfied will be the number of paths where 1 is satisfied into its parent
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
