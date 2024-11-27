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




// We have some remainder r
// At any point, we either roll a 5 or 6 sided dice, call this d
//  the new remainder will be r*d % desired roll

// Let dp[w][r] be the expected number of rolls to simulate 'w' if we get one r-sided dice roll
//  we would like to solve for dp[w][1]

//  rolling a d-sided dice would give us:
//      if r*d < w, 1 + dp[w][r*d]
//      if r*d >= w, 1 + (r*d%w)/w dp[w][r*d%w]
//  that is,
//      dp[w][r] = 1 + min(
//          5*r < w ? dp[w][r*5] : (r*5%w)/w dp[w][r*5%w],
//          6*r < w ? dp[w][r*6] : (r*6%w)/w dp[w][r*6%w],
//      )
//
//      if we ever hit a remainder we have already hit, that is
//          dp[w][r] = min(..., c1 + c2*dp[w][r], ...)
//      we can replace this with
//          dp[w][r] = min(..., c1/(1-c2), ...)
//
//      There are some problems here, where this is very dependent on there being no parenthesis
//      Ideally we can find some order of solving for dp[w][r] so that this doesn't occur at a different depth in our recurence
//
//      We have the base case dp[w][0] = 0
//      also if for d ∈ {5,6}, d|w, we have dp[w][w/d] = 1
//
//      We will build a graph, the nodes will be (w, r) pairs
//      There is an edge between (w, r1) and (w, r2) if r1*5%w = r2 or r1*6%w = r2
//          NO
//
//      Is it okay for a node to point to itself?
//          r = r*5%w ⇒ r*4 = 0
//          Answer: YES
//
//          If some node is in a cycle (5,6,...) with itself, we have
//          EV[u] = min(EV[u], (1 + p₁(1 + p₂(1 + …))))
//                = ... (1 + p1 + p1p2 + ... + p1p2p3p4... )
//
//      What nodes can point to itself?
//          when r=0, the node will point to itself
//
//      For each node, we build a vector of the lengths of all cycles it is in

int n = 1000;
int k;


vvpld adj, adj_rev;
map<pi, ld> prob;

// get all cycles in a dag rooted at 1


vvi cycles;
vi color; // color 0 means untouched, color 1 means in current path, color 2 means all cycles containing that node have been taken already
vi cur_path, inv_cur_path;
void dfs(int u) {
    if (color[u] == 2) return;
    if (color[u] == 1) {
        cycles.pb(vi());
        for(auto it = cur_path.begin() + inv_cur_path[u]; it != cur_path.end(); ++it)
            cycles.back().pb(*it);
        cycles.back().pb(u);
        return;
    }

    color[u] = 1;
    inv_cur_path[u] = cur_path.size();
    cur_path.pb(u);

    for(auto [v, _] : adj[u]) dfs(v);

    color[u] = 2;
    // if u has color 2 return
    // if u has color 1, find it's index in our current path, and copy all nodes
    // if u has color 0, set it's color to 1, push it to our vector, and iterate
}

vld cycle_ev;
vld ev;

vi seen;
ld dfs2(int u) {
    if (seen[u]) return 1e7;
    seen[u] = 1;

    ld &res = ev[u];
    for(auto [v, p] : adj[u])
        cmin(res, 1 + p*dfs2(v));

    seen[u] = 0;

    return res;
}


void init(int k) {
    adj.assign(k, vpld());

    for(int r=1; r<k; ++r) {
        adj[r].pb({ r*5%k, r*5 >= k ? ld(r*5%k)/ld(k) : 1 });
        prob[mp(r, r*5%k)] = r*5 >= k ? ld(r*5%k)/ld(k) : 1;

        adj[r].pb({ r*6%k, r*6 >= k ? ld(r*6%k)/ld(k) : 1 });
        prob[mp(r, r*6%k)] = r*6 >= k ? ld(r*6%k)/ld(k) : 1;
    }

    cycles.clear();
    color.assign(k, 0);
    cur_path.clear();
    inv_cur_path.rsz(k);
    dfs(1);

    cycle_ev.assign(k, 1e7);

    for(auto cycle : cycles) {
        ps(cycle);

        ld prob_prod = 1;
        for(int i=0; i<cycle.sz-1; ++i) prob_prod *= prob[{cycle[i], cycle[i+1]}];

        ld cur = 1;
        for(int i=cycle.sz-2; i>0; --i) cur = 1 + cur * prob[{cycle[i], cycle[i+1]}];

        ps(prob_prod, cur);

        for(int i=cycle.sz-1; i>0; --i) {
            cmin(cycle_ev[cycle[i]], cur/(ld(1) - prob_prod));
            ps(cur/(ld(1) - prob_prod));
            cur = 1 + cur * prob[{cycle[i-1], cycle[i]}] - prob_prod;
        }
    }

    adj_rev.assign(k, vpld());
    for(int r=1; r<k; ++r) for(auto [v, p] : adj[r])
        adj_rev[v].pb({ r, p });


    ev.assign(all(cycle_ev));
    seen.assign(k, 0);
    ld bev = dfs2(1);
    ps(bev);



    // there will be some repeating tail in our rolls
    //  the solution will either be a cycle from 1 to itself
    //  or it will be a path from 1 to some other node, and a cycle from that node to itself

    //  For each node, what is the min expected value to itself
    //  That is, for what cycle it is in is (1 + p1(1 + p2(1 + p3(1 + …)))) minimized
    //      we can reverse the edges, and bfs
    //          for nodes that are 1 away, the min path is (1 + p1)



    // want to find min (1+p0(1+p1(1+p2(...(1+p{k-1})))))/(1-(1+p0(1+p1(1+p2(...(1+p{k-1}pk))))))


    // for each node
    // for(int r=1; r<k; ++r) {
    // for(int r=1; r<k; ++r) {
    //     // initialize values from children to it to large values
    //     dists.assign(k, 1e7);
    //     dists[r] = 1;
    //
    //     queue<int> q({ r });
    //     while(q.size()) {
    //         int u = q.front(); q.pop();
    //
    //         ld nmd = dists[u];
    //         for(auto [v, p] : adj_rev[u])
    //             cmin(nmd, (1+p*dists[v]));
    //
    //         if (nmd >= dists[u]) continue;
    //         dists[u] = nmd;
    //         for(auto [v, _] : adj[u]) if (v != r) q.push(v);
    //     }
    //
    //     ld &mcr = lev[r];
    //     for(auto [v, p] : adj[r]) cmin(mcr, 1 + p*dists[v]);
    // }
    //
    // cout << lev[1] << '\n';


    // in the event of the former, we iterate over all cycles from 1 to itself
    // in the event of the later, we may discard 1 after stepping off of it

    //
}



void solve() {
    init(8);

    ps();

    init(28);

    ps();

    // for(int i=2; i<=n; ++i) {
    //     cout << i << '\n';
    //     init(i);
    // }
}

int main() {
    solve();

    return 0;
}
