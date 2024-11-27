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

int const Mod = 1e9 + 7;

ll modpow(int a, int b) {
    ll res = 1;
    for(ll e=1, p=a; e <= b; e<<=1, p = p*p%Mod)
        if (e&b) res = res * p % Mod;
    return res;
}

ll moddiv(int a, int b) {
    ll num = a, den = modpow(b, Mod-2), res = num*den % Mod;
    return res;
}

vll factmem = { 1 };
ll fact(int a) {
    while(a >= factmem.sz) factmem.pb(factmem.back() * factmem.sz % Mod);
    return factmem[a];
}

ll choose(int a, int b) {
    if (a < b) return 0;
    ll num = fact(a), den = fact(a-b) * fact(b) % Mod, res = moddiv(num, den);
    return res;
}

int n, k;
vvi tree;

vll cnts;
void dfs1(int r=0, int p=-1) {
    cnts[r] = 1;
    each(c, tree[r]) {
        if (c == p) continue;
        dfs1(c, r);
        cnts[r] += cnts[c];
    }
}

// returns number of ways to assign k and k-1 to buckets so that no bucket has over k/2 items
//  instead, first count the total number of assignments (n-1 choose k) and (n-1 choose k-1) respectively
ll solve_buckets(vll &buckets) {
    ll tot1 = choose(n-1, k);
    each(b, buckets) {
        // how many ways to assign over k/2 items to b and the rest to other buckets
        ll obs = (n-1)-b;
    }

    ll tot2 = choose(n-2, k);

    return -1;
}

vll npaths;
void dfs2(int r=0, int p=-1) {

    vll buckets;
    each(c, tree[r]) buckets.pb(cnts[c]);
    npaths[r] = solve_buckets(buckets);

    each(c, tree[r]) {
        if (c == p) continue;

        cnts[r] -= cnts[c];
        cnts[c] += cnts[r];

        dfs2(c, r);

        cnts[c] -= cnts[r];
        cnts[r] += cnts[c];
    }
}

void solve() {
    re(n, k);

    tree.assign(n, vi());
    rep(n-1) {
        int1(u, v);
        tree[u].pb(v);
        tree[v].pb(u);
    }

    if (k&1) { ps(1); return; }

    // initially root tree arbitrarily at 0 to populate subtree counts
    cnts.assign(n, 0);
    dfs1();

    npaths.assign(n, 0);
    dfs2();

    int num = accumulate(all(npaths), 0ll) % Mod;
    int den = choose(n, k);
    int res = moddiv(num, den);
    ps(res);

    // Sample Space: Ω = { (i₁, …, iₖ) : iᵤ≠iᵥ, 0≤iᵤ<n }
    //  P is the discrete uniform distribution, P(v) = 1/|Ω| = 1/(k! * (n choose k))
    // X is the random variable that maps some (i₁, …, iₖ) to the number of good islands
    //  EV[X] := ∑{ v ∈ Ω }P(v)*X(v) = P₀*∑{v ∈ Ω}X(v)

    // define Ω' = { (i₁, …, iₖ) : < i₁<…<iₖ, 0≤iᵤ<n }
    //  We see that ∑{v \in Ω}X(v) = ∑{v ∈ Ω'}(k!)*X(v)
    //  and so EV[X] = EV'[X] = (1/(n choose k)) * ∑{ v ∈ Ω' } X(v)

    // The question becomes how can we quickly compute ∑{ v ∈ Ω' } X(v)

    // if K = 1, the anwer is clearly always 1

    // if K = 2, X(v) is simply the number of nodes on the path between i₁ and i₂
    //  computing this quickly still looks a little tricky
    //  it would be sufficient to know the distriution of path lengths
    //  alternatively, it would be sufficient to know how many paths a single node lies in

    // if K = 3, and all values lie on the same path, there is a single good island, specifically the center node
    // if K = 3, and not all value lie on the same path
    //  if the three share an lca, that is the unique good island
    //  otherwise, there is still only a single good island, the mode of the pairwise lcas
    // that is if K = 3, the answer is always 1

    // This worked for B1, but now for B2
    //  if k is odd, all selections should only have one corresponding good island
    //      Clearly there must be at least 1 good island
    //      suppose i is a good island: it follows that for none of its children c
    //          N(c) > k - N(c)
    //      as otehrwise c would have a strictly smaller sum
    //      since k is odd, this implies that N(c) < k - N(c)
    //      suppose there is a second good island j ≠ i
    //          then j must be in some subtree of i and we can reach a quick contraidction

    // Now, for k even
    //  as stated above, a node i can be good only if for all its children, N(c) ≤ k - N(c)
    //  an assignment can have multiple good nodes only if for each of them, there exists some child c such that N(c) = k - N(c)
    //  specifically, these form a path, and all nodes along it are good

    // So, a node is good if and only if for all its children, N(c) ≤ k - N(c) ↔ N(c) ≤ k/2
    //  the sum of assignments must be in either n or n-1

    // the question becomes given a vector of bucket sizes
    //  how many ways are there to assign k items such that no bucket has over k/2 items
    //  how many ways are there to assign (k-1) items such that no bucket has over k/2 items

    // we will have to solve this question n times, wehre the sum of the number of buckets is 2*(n-1)
    //  so we must solve it in O(|B|log(|B|))ish
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
