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

// heavy light decomposition
//  want to know the sum of values from a vertex to the root
//  and can update the values of a vertex

int const Mod = 998244353;

// Actually this will be a BIT
struct SEG {/*{{{*/
    int n;
    vll bit;
    ll sum;

    SEG(int n0) : n(n0) {
        bit.assign(n, 0);
        sum = 0;
    }

    void update(int i, int d) {
        sum = (sum+d)%Mod;
        for(int j=(i+1); j<=n; j+=(j&-j)) bit[j-1] += d;
    }

    int query_aux(int r) {
        ll res=0;
        for(int j=(r+1); j>0;  j-=(j&-j)) res = (res + bit[j-1])%Mod;
        return res;
    }

    // query sum from l to end
    int query(int l) {
        if (l == 0) return sum;
        return (sum - query_aux(l-1) + Mod) % Mod;
    }
};/*}}}*/

struct HLD {/*{{{*/
    int n;
    vvi adj;

    int root;

    vi par;
    vi heavy;
    vi sub_siz;

    // initializes heavy
    void init0(int u, int p=-1) {
        par[u] = p;
        sub_siz[u] = 1;
        int mxc=-1, mxv=-1;

        for(auto v : adj[u]) {
            if (v == p) continue;
            init0(v, u);
            sub_siz[u] += sub_siz[v];
            if(sub_siz[v] > mxv) mxc=v, mxv=sub_siz[v];
        }

        if(mxc != -1) heavy[mxc]=1;
    }


    vi seg_id;
    vi seg_root, seg_leaf;
    ve<SEG> segs;
    vi seg_ind;

    void init1() {
        int cid=0;

        seg_id.assign(n, -1);

        queue<int> q({ root });
        while(q.size()) {
            int u = q.front(); q.pop();

            if(!heavy[u]) {
                seg_id[u] = cid++;
                seg_root.pb(u);
            } else seg_id[u] = seg_id[par[u]];

            if (sub_siz[u] == 1) seg_leaf[seg_id[u]] = u;

            for(int v : adj[u]) {
                if (seg_id[v] >= 0) continue;
                q.push(v);
            }
        }

        segs.resize(cid);
        seg_ind.assign(n, -1);
        for(int u : seg_leaf) {
            int diff = 0, cur = u;

            while(heavy[cur]) {
                seg_ind[cur] = diff++;
                cur = par[cur];
            } seg_ind[cur] = diff++;

            segs[seg_id[u]] = SEG(diff);
        }
    }


    void update_node(int u, int d) {
        segs[seg_id[u]].update(seg_ind[u], d);
    }


    int query_to_root(int u) {
        ll res = 0;

        while(u >= 0) {
            res += segs[seg_id[u]].query(seg_ind[u]);
            u = par[seg_root[seg_id[u]]];
        }

        return res%Mod;
    }


    HLD(vvi adj0) : adj(adj0) {
        root = 0;
        n = adj.size();
        par.assign(n, -1), heavy.assign(n, 0), sub_siz.assign(n, -1);
        init0(root);
        init1();
    }
};/*}}}*/


int n, q;
vpi edges;

int root;
vvi adj;
vi sub_siz;
void init0(int u, int p=-1) {
    sub_siz[u] = 1;
    for(auto v : adj[u]) {
        if(v == p) continue;
        init0(v, u);
        sub_siz[u] += sub_siz[v];
    }
}

void solve() {
    re(n, q), rv(n-1, edges);
    adj.assign(n, vi());
    for(auto [u, v] : edges) adj[u-1].pb(v-1), adj[v-1].pb(u-1);


    root = 0;
    sub_siz.assign(n, 0);
    init0(root);


    HLD hld(adj);


    for(int _=0; _<q; ++_) {
        int t, v; cin >> t >> v; --v;
        if (t == 1) {
            int d; cin >> d;
            // change to ev below is equal to d times probability of above ( d*(n-subsiz[u])/n )
            // change to ev above is equal to d time probability of below ( d*(subsiz[u]/n) )
        } else {

        }
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
