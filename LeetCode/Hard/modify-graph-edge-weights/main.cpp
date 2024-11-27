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

class Solution {
private:
    ve<set<pi>> adj;
    int n, s, d, t;

    // O((E+N)log(N))
    int min_path() {
        // priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        // pq.push({ 0, s });

        set<pair<int, int>> pq;
        for(int i=0; i<n; ++i) pq.insert({ INT_MAX, i });
        vi min_dist(n, INT_MAX);
        pq.erase({ min_dist[s], s }), pq.insert({ 0, s });
        min_dist[s] = 0;

        while(pq.size()) {
            auto [d, u] = *pq.begin(); pq.erase(pq.begin());
            if (d == INT_MAX) { min_dist[u] = -1; continue; } // node is unrechable
            for(auto [v, dd] : adj[u]) if (d + abs(dd) < min_dist[v]) {
                pq.erase({ min_dist[v], v }), pq.insert({ d + abs(dd), v });
                min_dist[v] = d+abs(dd);
            }
        }

        return min_dist[d];
    }
public:
    vector<vector<int>> modifiedGraphEdges(int nodes, vector<vector<int>>& edges, int source, int destination, int target) {
        n = nodes, s = source, d = destination, t = target;
        adj.assign(n, set<pi>());

        // O(E * log(N))
        for(auto e : edges) if (e[2] > 0) adj[e[0]].insert({ e[1], e[2] }), adj[e[1]].insert({ e[0], e[2] });
        if (min_path() != -1 && min_path() < target) return {}; // there exists an unchangable path with order less than target

        // O(E * log(N))
        for(auto e : edges) if (e[2] < 0) adj[e[0]].insert({ e[1], e[2] }), adj[e[1]].insert({ e[0], e[2] });
        if (min_path() == -1 || min_path() > target) return {}; // there either exists no paths, or all paths are invalid

        vector<vector<int>> res, todo;
        for(auto e : edges) {
            if (e[2] > 0) res.pb(e);
            if (e[2] < 0) {
                adj[e[0]].erase({ e[1], e[2] }), adj[e[1]].erase({ e[0], e[2] });
                int mp = min_path();
                if (mp == -1 || mp > target) todo.pb(e), adj[e[0]].insert({ e[1], e[2] }), adj[e[1]].insert({ e[0], e[2] });
                else res.pb({ e[0], e[1], (int) 2e9 });
            }
        }

        if (todo.size()) {
            int diff = target - min_path() + todo.size();
            for(int i=0; i<todo.size()-1; ++i) --diff, res.pb({ todo[i][0], todo[i][1], 1 });
            res.pb({ todo.back()[0], todo.back()[1], diff });
        }

        return res;



        // if there initially exists a shortest path of weight less than target, no solution exists

        // consider the set of all s-d paths S{{{

        //  define M(p) := |{ e ∈ p : |e| = -1 }|
        //  let S' := { p ∈ S : |p| + 2*M(p) <= t }
        //      that is S' is the set of all paths that can have weight leq target after some complete update
        //      clearly if S' = ∅  there is no solution, so assume that S' is non-empty

        //  let T := { p ∈ S' : M(p) = min{p∈S'}(M(p)) }
        //      that is T is the set of all paths in S' with min M(p)
        //      if S' is non-empty then so will be T

        //  let T' := { p ∈ T : |p| = min{p∈T}(|p|) }
        //      that is T' is the set of all paths in T with min weight
        //      if T is non-empty, then so will be T'

        // choose some p ∈ T', and
        //      set all edges not in p to 2e9
        //      set the edges in p to be anythin that satisfies the target

        //  clearly all paths in S-S' will not have a path less than target
        //  all paths in S'-T will have at least some edge of weight 2e9, and will not have weight less than target
        //  all paths in T-T' will have larger weight that p
        //  all paths in T' will have weight at least |p|
        //  so this is valid

        // so we would like to find some s-d path such that
        //  1) it can have a valid transformation
        //  2) the number of undefined edges is minimal given it satisfies 1
        //  3) its weight is minimal given it satisfies 2

        // if we initially set all edges to have weight 1
        //  a solution exists iff the min s-d path satisfies 1

        // if we initially set all edges to have weight larger than the sum of all initially defined edges
        //  the min path will always minimize the number of undefined edges

        // alternatively, we may find a path that only satisfies 1&2, and then find the min path that uses its undefined edges
        //  suppose we have a weighted graph for which each edge is colored in binary
        //  can we find, for fixed k, the shortest path such that exactly k edges are color 1
        //      if so we can iterate over k}}}

        // for each undefined edge, try and remove it and see if there is still a valid path
        //  if so, remove it
        //  otherwise keep it
        //  after this is done with every edge, we have a set of edges such that if any are removed, there is no longer a valid path
        //

    }
};
