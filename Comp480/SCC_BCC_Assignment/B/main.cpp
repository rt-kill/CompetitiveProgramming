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



class DSU {/*{{{*/
public:
    int V;
    vi par, siz;

    DSU(int V=0);
    int get_rep(int u);
    void dsu_union(int u, int v);
};

DSU::DSU(int V) {
    this->V = V;
    par.resize(V), iota(all(par), 0);
    siz.assign(V, 1);
}

int DSU::get_rep(int u) {
    if(par[u] != par[par[u]]) par[u] = get_rep(par[u]);
    return par[u];
}

void DSU::dsu_union(int u, int v) {
    int r1 = get_rep(u), r2 = get_rep(v);
    if(r1 == r2) return;
    if(siz[r1] < siz[r2]) swap(r1, r2);
    par[r2] = r1;
    siz[r1] += siz[r2];
}/*}}}*/


class SP {/*{{{*/
public:
    int V, r;
    vi p, weights, depth;
    vvi sp, ss;

    void init_depth_aux(int u);
    SP();
    SP(vi p, vi weights);

    int query_up_sum(int u, int d);
    int query_path_res(int u, int v);
};

void SP::init_depth_aux(int u) {
    if(depth[u] >= 0) return;
    if(u == p[u]) { depth[u] = 0; return; }
    init_depth_aux(p[u]);
    depth[u] = depth[p[u]] + 1;
}

SP::SP() {}

SP::SP(vi p, vi weights) {/*{{{*/
    V = p.sz;
    for(int u=0; u<V; ++u) if (u == p[u]) r = u;

    (this->p).assign(all(p));
    (this->weights).assign(all(weights));

    // initialize depths
    (this->depth).assign(V, -1);
    for(int u=0; u<V; ++u) if(p[u] >= 0) init_depth_aux(u);

    sp.assign(32, vi(V)), ss.assign(32, vi(V));

    // sp[i][u] = (1<<i) parrent of u
    sp[0].assign(all(p));

    // ss[i][u] = sum of all but last node on (1<<i) path from u upwards
    ss[0].assign(all(weights)), ss[0][r] = 0;

    for(int i=0; i+1 < 32; ++i) for(int u=0; u<V; ++u) {
        if(p[u] == -1) continue;
        sp[i+1][u] = sp[i][sp[i][u]];
        ss[i+1][u] = ss[i][u] + ss[i][sp[i][u]];
    }
}/*}}}*/

int SP::query_up_sum(int u, int d) {
    int res = 0;

    while(d > 0) {
        int diff = (d&-d), l2 = __builtin_ctz(diff);
        res += ss[l2][u], u = sp[l2][u];
        d -= diff;
    }

    return res;
}

int SP::query_path_res(int u, int v) {
    if(depth[u] < depth[v]) swap(u, v);

    int cu=u, cv=v;

    while(depth[cu] > depth[cv]) {
        int diff = (depth[cu] - depth[cv]), l2 = __builtin_ctz(diff&-diff);
        cu=sp[l2][cu];
    }

    for(int i=31; i>=0; --i) while(sp[i][cu] != sp[i][cv])
        cu = sp[i][cu], cv = sp[i][cv];

    int lca = cu != cv ? p[cu] : cu; // = p[cv]

    int res = query_up_sum(u, depth[u] - depth[lca]) + query_up_sum(v, depth[v] - depth[lca]) + weights[lca];

    return res;
}/*}}}*/


class Graph {/*{{{*/
public:
    int V, E;
    vvi adj;

    int t;
    vi enter_time, min_descendant_time, is_articulation_point;
    void init_articulation_points();
    void articulation_points_dfs(int r=0, int p=-1);

    vi articulation_par;
    DSU bcc_sets;
    vi seen;
    void init_bcc_sets();
    void bcc_sets_dfs(int r, int rep);

    SP sparse_par;
    void init_sparse_par();

    int query_res(int u, int v);

    Graph(int V);
    void add_edge(int u, int v);
};

Graph::Graph(int V) {
    this->V = V, this->E = 0;
    adj.assign(V, vi());
}

void Graph::add_edge(int u, int v) {
    adj[u].pb(v), adj[v].pb(u);
    ++E;
}


void Graph::init_articulation_points() {/*{{{*/
    t=0;
    enter_time.assign(V, -1);
    min_descendant_time.assign(V, -1);
    is_articulation_point.assign(V, 0);
    articulation_points_dfs();
}/*}}}*/

void Graph::articulation_points_dfs(int r, int p) {/*{{{*/
    if(enter_time[r] >= 0) return; // already seen this node

    enter_time[r] = t, min_descendant_time[r] = t, ++t;
    int number_of_children = 0;

    for(auto u : adj[r]) {
        if(u == p) continue;
        if(enter_time[u] < 0) ++number_of_children;
        articulation_points_dfs(u, r);
        cmin(min_descendant_time[r], min_descendant_time[u]);
    }

    if(r == 0 && number_of_children > 1) is_articulation_point[r] = 1;

    if(r != 0) {
        for(auto u : adj[r]) {
            if(u == p) continue;
            if(min_descendant_time[u] >= enter_time[r])
                is_articulation_point[r] = 1;
        }
    }
}/*}}}*/


void Graph::init_bcc_sets() {/*{{{*/
    init_articulation_points();

    bcc_sets = DSU(V);
    articulation_par.assign(V, -1);

    seen.assign(V, 0);

    int rep = find(all(is_articulation_point), 1) - is_articulation_point.begin();

    if(rep == V) {
        for(int u=1; u<V; ++u) bcc_sets.dsu_union(0, u);
        return;
    }

    bcc_sets_dfs(rep, rep);
}/*}}}*/

void Graph::bcc_sets_dfs(int r, int rep) {/*{{{*/
    if(seen[r]) return;
    seen[r] = 1;

    if(is_articulation_point[r]) articulation_par[r] = rep, rep = r;

    bcc_sets.dsu_union(rep, r);
    for(auto u : adj[r])  bcc_sets_dfs(u, rep);
}/*}}}*/


void Graph::init_sparse_par() {/*{{{*/
    init_bcc_sets();
    sparse_par = SP(articulation_par, bcc_sets.siz);
}/*}}}*/


int Graph::query_res(int u, int v) {
    int r1 = bcc_sets.get_rep(u), r2 = bcc_sets.get_rep(v);

    int res = sparse_par.query_path_res(r1, r2);
    int off = (r1 != r2) * ((u == r1) * (bcc_sets.siz[r1]-1) + (v == r2) * (bcc_sets.siz[r2]-1));
    res -= off;
    return res;
}

/*}}}*/



int n, m, q;
vpi edges, quer;


void solve() {
    re(n, m), rv(m, edges), re(q), rv(q, quer);

    for(auto &[u, v] : edges) --u, --v;
    for(auto &[u, v] : quer) --u, --v;

    Graph graph(n);
    for(auto [u, v] : edges) graph.add_edge(u, v);
    graph.init_sparse_par();

    ps(graph.is_articulation_point, graph.articulation_par);

    for(auto [u, v] : quer) ps(graph.query_res(u, v));
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

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
