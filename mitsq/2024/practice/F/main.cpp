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


// the last query will nessesarily be on adjacent elements of the permutation
//  every other element will either be before or after the pair

// the second to last query will either be adjacent elements not containing one of the last queries elements
//  or an element before the query or after the query


// from the back of the edges to the front
//  do a union find with a map from root to options
//  if we add an edge with no values,


// Question: does the collection of valid permutations induce an equivalence relation on the orderings?
//  that is, if two orders share a single permutation, must they share all permutations?







int n;
vpi pairs;

vvi graph, in_nodes, out_nodes;


int dfs(int i) {
    if (i == pairs.size()) return 1;

    auto [a, b] = pairs[i]; --a, --b;

    int f0 = 1, f1 = 1;

    // Every node before a is already known to be before b
    //  otherwise adding the edge a->b will cause problems when we compare this node before a to b
    for(auto v : in_nodes[a])   f0 &= (graph[v][b] == 1);
    for(auto v : out_nodes[b])  f0 &= (graph[a][v] == 1);

    // Every node before b is already known to be before a
    //  otherwise adding the edge b->a will cause problems when we compare this node before b to a
    for(auto v : in_nodes[b])   f1 &= (graph[v][a] == 1);
    for(auto v : out_nodes[a])  f1 &= (graph[b][v] == 1);

    // ps(in_nodes[a]);

    int res = 0;

    // a is before b
    if(f0) {
        // ps(i, 0);
        graph[a][b] = 1;
        out_nodes[a].push_back(b);
        graph[b][a] = 0;
        in_nodes[b].push_back(a);

        res += dfs(i+1);

        graph[a][b] = -1;
        out_nodes[a].pop_back();
        graph[b][a] = -1;
        in_nodes[b].pop_back();
    }


    // b is before a
    if(f1) {
        // ps(i, 1);
        graph[b][a] = 1;
        out_nodes[b].push_back(a);
        graph[a][b] = 0;
        in_nodes[a].push_back(b);

        res += dfs(i+1);

        graph[b][a] = -1;
        out_nodes[b].pop_back();
        graph[a][b] = -1;
        in_nodes[a].pop_back();
    }

    return res;
}


void solve() {
    re(n), rv(n*(n-1)/2, pairs);

    graph.assign(n, vi(n, -1));
    in_nodes.assign(n, vi());
    out_nodes.assign(n, vi());


    auto [a, b] = pairs[0];
    --a, --b;
    graph[a][b] = 1;
    out_nodes[a].push_back(b);
    graph[b][a] = 0;
    in_nodes[b].push_back(a);

    int res = dfs(1)%Mod*2%Mod;

    ps(res);

    // suppose my sequence is something like
    //  (1, 2) (1, 3) (1, 4) (1, 5) ... (2, 3) (2, 4) ... (n-1, n)
    // then there are only 2 permutations where I need to ask every question:
    //  (1 2 3 4 5 6 ... n) (n n-1 ... 1)

    // after I've asked all questions containing some number x, I will know exactly where x is in the permutation
    //  so I will not ask any more question relating elements to opposite sides of x

    // suppose I make a query (a, b) and a query (b, c)
    //  then I will only make the query (a, c) if either
    //      (p(a) < p(b) && p(c) < p(b))
    //      (p(a) > p(b) && p(c) > p(b))

    // that is, i will only create cycles in the graph of asked questions


    // lets build a graph as we ask questions
    //  the graph will have n nodes
    //  when we ask a question, we will add an edge from either a to b or b to a depending on larger/smaller
    //      lets say a points to b if b comes after a
    //      that is, nodes point to larger indes elements, and are pointed to by smaller index elements

    //  we notice that this is a transitive relation
    //  that is, if there is already some path from a to b, then we should never ask the question (a, b)

    //  note, if some permutation works, then its reverse will also always work
    //      that is, our solution is always even

    // so we have a recursive backtracking solution:
    //  to query (a, b):
    //      res = 0
    //      if all nodes with a path to a already point to b:
    //          add the edge
    //          recurse and add the solution to res
    //          remove the edge
    //      if all nodes with a path to b already point to a:
    //          add the edge
    //          recurse and add the solution to res
    //          remove the edge
    //      return res

    // this will be wayyy to slow if the solution gets very large


    // if we have an edge from a to b
    //  then we can not add any edges out of b until we add them out of a
    //  similarly we can not add any edges into a until we add them into b
    //  we can freely add edges into b and out of a

    // there will be
    //      some node with in degree 0
    //      some node with indegree 1
    //      etc...

    // a node can have indegree 0 only if
    //  before it is connected to some node b, b is connected to all other nodes it is connected to
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
