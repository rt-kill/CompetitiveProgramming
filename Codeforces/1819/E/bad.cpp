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

int n, m;
vpi edges;
vvpi graph;

void block_road(int x) { /*{{{*/
    cout << '-' << ' ' << x+1 << '\n';
    cout.flush();
}

void unblock_road(int x) {
    cout << '+' << ' ' << x+1 << '\n';
    cout.flush();
}

int path_query(int y) {
    cout << '?' << ' ' << y+1 << '\n';
    cout.flush();

    ints(x);
    return x;
}

void answer(vi &res) {
    cout << '!' << ' ';
    each(v, res) cout << v << ' ';
    cout << '\n';
    cout.flush();

    ints(x);
    if (x == 0) exit(0);
}/*}}}*/

// randomly path queries on either u or v and returns the value{{{
int rand(int u, int v) {
    int choice = rand()%2 ? u : v;
    return path_query(choice);
}

// runs rand a sufficient number of times and returns whether all values were 1
int many_rand(int u, int v) {
    int res = 1;
    for(int k=0; res && k<40; ++k) res &= rand(u, v);
    // for(int k=0; res && k<1; ++k) res &= rand(u, v); // testing
    return res;
}/*}}}*/

vi good, dead;/*{{{*/
set<int> A;
set<pi> ES;

void init_cp() {
    good.assign(n, -1);
    dead.assign(n, 0);
    A.clear(); A.insert(0);
    ES.clear(); ES.insert(all(graph[0]));
}/*}}}*/

void collapse_cut(int u) {/*{{{*/
    if (dead[u]) {
        for(auto [v, j] : graph[u])
            if (A.count(v)) ES.insert({ u, j });
        dead[u] = 0;
    }

    vi eiq;
    // XXX: Slow if ES is large
    for(auto [v, i] : ES) if (v == u) eiq.pb(i);
    For(i, 0, eiq.sz) ES.erase({ u, eiq[i] });

    // XXX: Many unnessesary block/unblock but should be fine
    For(i, 0, eiq.sz) block_road(eiq[i]);
    For(i, 0, eiq.sz) {
        unblock_road(eiq[i]);
        good[eiq[i]] = many_rand(0, u);
        block_road(eiq[i]);
    }
    For(i, 0, eiq.sz) unblock_road(eiq[i]);

    A.insert(u);
    for(auto [v, j] : graph[u]) {
        if (!A.count(v)) ES.insert({ v, j });
    }
}/*}}}*/

void cut_step() {/*{{{*/
    int u = ES.begin()->fi;

    vi eiq;
    for(auto it=ES.begin(); it!=ES.end() && it->fi==u; ++it)
        eiq.pb(it->se);

    For(i, 0, eiq.sz) block_road(eiq[i]);
    dead[u] = many_rand(0, u);
    if (dead[u]) {
        For(i, 0, eiq.sz) ES.erase({ u, eiq[i] });
    } else {
        collapse_cut(u);
    }
}/*}}}*/

void step() {/*{{{*/
    if (ES.begin()->fi == ES.rbegin()->fi) {
        collapse_cut(ES.begin()->fi);
        return;
    } else if(ES.sz) {
        cut_step();
    }
}/*}}}*/

void my_loop() {
    init_cp();
    while(A.sz < n) step();
    answer(good);
}

void solve() {
    re(n, m);
    edges.clear();
    graph.assign(n, vpi());
    rep(m) {
        int1(u, v);
        graph[u].pb({v, edges.sz});
        graph[v].pb({u, edges.sz});
        edges.pb({u, v});
    }
    my_loop();

    // if a node has degree 1, its edge must be good
    // if a node has degree 2:
    //      turn off one edge
    //

    // any cut edge must be good
    // any cut set must contain at least 1 good edge
    // we may assume the graph has no leafs

    // suppose for some node partition (A, B) we know that A and B are both connected in our good graph
    //  then we can find all good edges between them relatively easily
    // We can actually do this as long as we know A is connected (B need not be connected)

    // Algorithm:
    //  Let A := { 0 }, and B := G\A
    //  While(|B| > 0) {
    //      If there is only one edge from A -> B:
    //          mark the edge as good and add its end to A
    //          continue
    //
    //      If all edges from A go to the same node in B:
    //          block all edges between A and B
    //          for each edge:
    //              unblock it
    //              repeat a few times
    //                  choose some node with a 50/50 chance of being in A or B
    //                  query it
    //
    //              if all of the queries were 1, mark the edge as good
    //              otherwise as bad
    //              reblock it if good
    //
    //          unblock all edges and add the node to A
    //          continue
    //
    //      Choose some node u in B with an edge from A into it
    //      block all edges between u and A
    //          repeat a few times
    //              choose some node with a 50/50 chance of being in A or u
    //              query it
    //
    //          if any were 0, at least one of the edges must be good
    //              run our loop thingy and add u to A
    //
    //          otherwise the graph is still connected, and we can repeat on another edge until we get a split
    //  }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    srand (time(NULL));

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
