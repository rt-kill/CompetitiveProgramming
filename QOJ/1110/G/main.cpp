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

#include <bits/stdc++.h>
using namespace std;

// Computes the strongly connected components of a directed graph using
//     Tarjan's algorithm
// Vertices are 0-indexed
// Constructor Arguments:
//     G: a generic directed graph structure which can be weighted or unweighted,
//             though weights do not change the components
//         Required Functions:
//             operator [v] const: iterates over the adjacency list of vertex v
//                 (which is a list of ints for an unweighted graph, or a list of
//                 pair<int, T> for a weighted graph with weights of type T)
//             size() const: returns the number of vertices in the graph
//     condensationEdges: a reference to a vector of pairs that will store the
//         edges in the condensation graph when all vertices in an scc are
//         condensed into a single vertex (with an index equal to its scc id),
//         and it is guaranteed that this list of edges is sorted by the first
//         element in the pair in non decreasing order
// Fields:
//     id: a vector of the index of the scc each vertex is part of
//     components: a vector of vectors containing the vertices in each scc and
//         is sorted in reverse topological order
// In practice, has a moderate constant, faster than Kosaraju
// Time Complexity:
//     constructor: O(V + E)
// Memory Complexity: O(V)
// Tested:
//     Stress Tested
//     https://judge.yosupo.jp/problem/scc
//     https://dmoj.ca/problem/acc2p2
//     https://open.kattis.com/problems/watchyourstep
struct SCC {
    int ind, top; vector<int> id, low, stk; vector<vector<int>> components;
    int getTo(int e) { return e; }
    template <class T> int getTo(const pair<int, T> &e) { return e.first; }
    template <class Digraph> void dfs(const Digraph &G, int v) {
        id[stk[top++] = v] = -1; int mn = low[v] = ind++; for (auto &&e : G[v]) {
            int w = getTo(e); if (id[w] == -2) dfs(G, w);
            mn = min(mn, low[w]);
        }
        if (mn < low[v]) { low[v] = mn; return; }
        int w; components.emplace_back(); do {
            id[w = stk[--top]] = components.size() - 1; low[w] = INT_MAX;
            components.back().push_back(w);
        } while (w != v);
    }
    template <class Digraph> SCC(const Digraph &G)
            : ind(0), top(0), id(G.size(), -2), low(G.size()), stk(G.size()) {
        for (int v = 0; v < (int)G.size(); v++) if (id[v] == -2) dfs(G, v);
    }
    template <class Digraph>
    SCC(const Digraph &G, vector<pair<int, int>> &condensationEdges) : SCC(G) {
        vector<int> last(components.size(), -1);
        for (auto &&comp : components) for (int v : comp) for (auto &&e : G[v]) {
            int w = getTo(e); if (id[v] != id[w] && last[id[w]] != id[v])
                condensationEdges.emplace_back(last[id[w]] = id[v], id[w]);
        }
    }
};

int const D = 7;
int n;

arr<int, D> ds;
arr<int, 8> dpfx;

ve<arr<int, D>> friends;
arr<int, 2> my_guess;

vvi implications;

void solve() {
    re(n, ds), rv(n, friends), re(my_guess);

    dpfx[0] = 0;
    for(int i=1; i<=D; ++i) dpfx[i] = dpfx[i-1]+ds[i-1]+1;

    // implications for const i winning on day d is
    // implications[i + dpfx[d]]

    // implications for const i losing on day d is
    // implications[i + dpfx[d] + dpfx[7]]

    // implications for const i not winning on day d is
    // implications[i + dpfx[d] + 2dpfx[7]]

    // implications for const i not losing on day d is
    // implications[i + dpfx[d] + dpfx[7] + 2dpfx[7]]

    int siz = 4*dpfx[7] + 100;

    implications.assign(siz, vi());

    for(int d=0; d<D; ++d) {
        for(int i=1; i<=ds[d]; ++i) {
            int i1 = abs(i) + dpfx[d] + (i < 0)*dpfx[7];
            int i2 = abs(-i) + dpfx[d] + (-i < 0)*dpfx[7];
            int i3 = abs(i) + dpfx[d] + (i < 0)*dpfx[7] + 2*dpfx[7];
            int i4 = abs(-i) + dpfx[d] + (-i < 0)*dpfx[7] + 2*dpfx[7];

            // winning is the same as not losing
            implications[i1].pb(i4);
            implications[i4].pb(i1);

            // losing is the same as not winning
            implications[i2].pb(i3);
            implications[i3].pb(i2);
        }
    }

    for(auto f : friends) {
        for(int d=0; d<D; ++d) {
            for(int bd=0; bd<D; ++bd) {
                if(d == bd) continue;

                int dind = abs(f[d]) + dpfx[d] + (f[d] < 0)*dpfx[7];
                int nbdind = abs(f[bd]) + dpfx[bd] + (f[bd] < 0)*dpfx[7] + 2*dpfx[7];
                implications[dind].pb(nbdind);
            }
        }
    }

    for(int d=5; d<D; ++d) {
        // I must be correct
        int right = abs(my_guess[d-5]) + dpfx[d] + (my_guess[d-5] < 0)*dpfx[7];
        int not_right = abs(my_guess[d-5]) + dpfx[d] + (my_guess[d-5] < 0)*dpfx[7] + 2*dpfx[7];
        implications[not_right].pb(right);
    }

    SCC my_scc(implications);


    for(int i=0; i+2*dpfx[7]<implications.sz; ++i) {
        int good = i;
        int bad = (i+2*dpfx[7]);
        if(my_scc.id[good] == my_scc.id[bad]) { ps("impossible"); return; }
    }

    ps("possible");
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
