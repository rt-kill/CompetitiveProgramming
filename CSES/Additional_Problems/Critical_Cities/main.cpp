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

// a node is critical if and only if it appears on every route from 1 to n
//  if and only if it can't be "skipped"

// wlog, the root has outdeg at least 2
//  at most one of it's children can be on every route from 1 to n


// we are free to remove nodes from the graph that are not on every path from 1 to n


// find the shortest path from 1 to n
//  any nodes not on this path are not critical
//  a node on this path is critical if and only if it can not be skipped
//      -- that is, there is not path from a prior node to a node after it without using the node
//  a node is critical if and only if when it is removed, there is no path from 1 to n
//  so critical nodes are almost cut nodes


// find the shortest path from 1 to n
//  remove all edges in this path from our graph
//  let u be the furthest node along this path we can reach
//      all nodes in the interval (p[0], u) are not critical

// if we add the first edge from our "shortest path", what is the furthest node we can reach now
//  all nodes inte interval (p[1], u) are not critical

// after all of these, we have a collection of intervals describing non-critical nodes
//  claim: all nodes along our path not in any of these intervals are critical
//      suppose there exists a path from 1 to n not using a node u, and u is in our shortest path
//      works out right


// find a smallest path from 1 to n
//  remove all edges in this path from our graph
//  find all reachable nodes from 1
//  one by one add back edges and find all reachable nodes from 1

int n, m;
vpi edges;
vvi adj;


vi path;/*{{{*/
void get_shortest_path() {

    vi par(n, -1);

    queue<int> q({ 0 });
    par[0] = 0;

    while(q.size()) {
        int u = q.front(); q.pop();

        for(auto v : adj[u]) {
            if(par[v] >= 0) continue;
            par[v] = u;
            q.push({ v });
        }
    }

    path.clear();

    int cv = n-1;
    while(par[cv] != cv) {
        path.pb(cv);
        cv = par[cv];
    }
    path.pb(0);

    reverse(all(path));
}/*}}}*/


set<pi> bad_edges;
vvi nadj;
void init_nadj() {
    get_shortest_path();

    for(int i=0; i+1<path.sz; ++i) bad_edges.insert({ path[i], path[i+1] });

    nadj.assign(n, vi());
    for(auto [u, v] : edges) if(!bad_edges.count({u, v})) nadj[u].pb(v);
}


map<int, int> path_idx;
vi seen;
int mydfs(int u) {
    int res = path_idx.count(u) ? path_idx[u] : -1;

    if(seen[u]) return res;
    seen[u] = 1;

    for(auto v : nadj[u]) cmax(res, mydfs(v));

    return res;
}


vi res;
void get_thngs() {
    init_nadj();

    path_idx.clear();
    for(int i=0; i<path.sz; ++i) path_idx[path[i]] = i;


    vi bad_thngs = { -1 };

    seen.assign(n, 0);
    for(auto v : path) seen[v] = 1;

    seen[path[0]] = 0;
    int mxp = mydfs(path[0]);
    bad_thngs.pb(mxp);

    // largest thing we can reach without any edges in our shortest path
    //  if node 1 is less than it, node 1 is not critical

    for(int i=1; i<path.sz; ++i) {
        seen[path[i]] = 0;
        nadj[path[i-1]].pb(path[i]);
        cmax(mxp, mydfs(path[i]));

        // largest thing we can reach with only first i edges from our shortest path
        //  if node (i+1) is less than it, node 1 is not critical

        bad_thngs.pb(mxp);
    }

    for(int i=0; i<path.sz; ++i) {
        if(i < bad_thngs[i]) continue;
        res.pb(path[i]);
    }
}





set<int> reachable;


void solve() {
    re(n, m), rv(m, edges);
    for(auto &[u, v] : edges) --u, --v;

    adj.assign(n, vi());
    for(auto [u, v] : edges) adj[u].pb(v);

    get_thngs();
    sort(all(res));
    res.erase(unique(all(res)), res.end());

    ps(res.sz);
    for(auto v : res) cout << v+1 << ' ';
    cout << '\n';
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
