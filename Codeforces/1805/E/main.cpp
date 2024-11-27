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
vi a;
vpi edges;
vvi tree;
map<int, int> value_counts;

void read_input() {
    re(n);
    edges.clear();
    rep(n-1) { int1(u, v); edges.pb({u, v}); }
    tree.assign(n, vi());
    for( auto [u, v] : edges ) tree[u].pb(v), tree[v].pb(u);
    rv(n, a);
    each(v, a) ++value_counts[v];
}

vi path;
int build_path(int r, int p, int d) {
    if (r == d) { path.pb(r); return 1; }
    each(c, tree[r]) {
        if (c == p) continue;
        if (build_path(c, r, d)) { path.pb(r); return 1; }
    }

    return 0;
}

auto mycmp = [](pi l, pi r) {
    if (l.se <= 1 && r.se >= 2) return true;
    if (l.se >= 2 && r.se <= 1) return false;
    return (l.fi < r.fi);
};

void add_dfs(int r, int p, set<pi, decltype(mycmp)> &S) {
    if (S.count({ a[r], 1 })) {
        S.erase({ a[r], 1 });
        S.insert({ a[r], 2 });
    } else if (S.count({ a[r], 2 })) {
        int cc = S.lb({ a[r], 2 })->se;
        S.erase({ a[r], 2 });
        S.insert({ a[r], cc+1 });
    } else {
        S.insert({ a[r], 1 });
    }

    each(c, tree[r]) {
        if (c == p) continue;
        add_dfs(c, r, S);
    }
}

void rem_dfs(int r, int p, set<pi, decltype(mycmp)> &S) {
    if (S.count({ a[r], 1 })) {
        S.erase({ a[r], 1 });
    } else if (S.count({ a[r], 2 })) {
        int cc = S.lb({ a[r], 2 })->se;
        S.erase({ a[r], 2 });
        S.insert({ a[r], cc-1 });
    }

    each(c, tree[r]) {
        if (c == p) continue;
        rem_dfs(c, r, S);
    }
}

set<pi, decltype(mycmp)> S1(mycmp), S2(mycmp);
map<pi, int> pevs;
void traverse_path() {
    add_dfs(path[0], path[1], S1);
    add_dfs(path[1], path[0], S2);

    int mv1 = (S1.rbegin()->se >= 2) ? S1.rbegin()->fi : 0;
    int mv2 = (S2.rbegin()->se >= 2) ? S2.rbegin()->fi : 0;
    pevs[{ path[0], path[1] }] = max(mv1, mv2);
    pevs[{ path[1], path[0] }] = max(mv1, mv2);

    For(i, 1, path.sz-1) {
        int cn = path[i], pn = path[i-1], nn = path[i+1];
        each(c, tree[cn]) {
            if (c == pn || c == nn) continue;
            add_dfs(c, cn, S1);
            rem_dfs(c, cn, S2);
        }

        if (S1.count({ a[cn], 1 })) {
            S1.erase({ a[cn], 1 });
            S1.insert({ a[cn], 2 });
        } else if (S1.count({ a[cn], 2 })) {
            int cc = S1.lb({ a[cn], 2 })->se;
            S1.erase({ a[cn], 2 });
            S1.insert({ a[cn], cc+1 });
        } else {
            S1.insert({ a[cn], 1 });
        }

        if (S2.count({ a[cn], 1 })) {
            S2.erase({ a[cn], 1 });
        } else if (S2.count({ a[cn], 2 })) {
            int cc = S2.lb({ a[cn], 2 })->se;
            S2.erase({ a[cn], 2 });
            S2.insert({ a[cn], cc-1 });
        }

        mv1 = (S1.rbegin()->se >= 2) ? S1.rbegin()->fi : 0;
        mv2 = (S2.rbegin()->se >= 2) ? S2.rbegin()->fi : 0;
        pevs[{ path[i], path[i+1] }] = max(mv1, mv2);
        pevs[{ path[i+1], path[i] }] = max(mv1, mv2);
    }
}

void solve() {
    read_input();

    int mv=0, mvc=3;
    reach(vcp, value_counts) {
        if (vcp->se >= 2) {
            tie(mv, mvc) = *vcp;
            break;
        }
    }

    if (mvc > 2) {
        rep(n-1) ps(mv);
        return;
    }

    int i1 = find(all(a), mv) - a.begin(), i2 = a.rend() - find(rall(a), mv) - 1;
    build_path(i2, -1, i1);
    traverse_path();
    for(auto [a, b] : edges) {
        if (pevs.count({ a, b })) ps(pevs[{ a, b }]);
        else ps(mv);
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
