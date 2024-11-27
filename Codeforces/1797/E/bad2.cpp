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

int const N = 1e5;

int n, m;/*{{{*/
vi a;
ve<arr<int, 3>> quer;

void read_input() {
    re(n, m);
    rv(n, a);
    rv(m, quer);
    for(auto &[t, l, r] : quer) --l, --r;
}/*}}}*/

vi spd, prs;/*{{{*/
void init_spd() {
    int ma = *max_element(all(a));
    spd.assign(ma+1, 0);
    spd[1] = 1;
    prs.clear();

    For(i, 2, ma+1) {
        if (spd[i] == 0) {
            spd[i] = i;
            prs.pb(i);
        }

        each(p, prs) {
            if (p > spd[i] || p*i > ma) break; // shouldn't overflow
            spd[p*i] = p;
        }
    }
}/*}}}*/

vi phi; // phi[x] = ϕ(x){{{
void init_phi() {
    int ma = *max_element(all(a));
    phi.assign(ma+1, 1);
    For(i, 2, ma+1) {
        if (i == spd[i]) { phi[i] = i-1; }
        else {
            int tmp=1, ci=i;
            for(; ci/spd[i]*spd[i]==ci; ci/=spd[i]) tmp *= spd[i];
            phi[i] *= tmp - tmp/spd[i];
            phi[i] *= phi[i/tmp];
        }
    }
}/*}}}*/


int seg[4*N], lazy[4*N]; // seg[i] = endvalue for op2

void prop_lazy(int i, int l, int r) {/*{{{*/
    if (lazy[i] == 0) return;

    int clv = lazy[i]; lazy[i] = 0;
    if (l < r) lazy[2*i] += clv, lazy[2*i+1] += clv;

    int &cv = seg[i];
    For(i, 0, clv) {
        if (cv == 1) break;
        cv = phi[cv];
    }
}/*}}}*/

void update_node(int i, int l, int r) {/*{{{*/
    if (l == r) return;

    int lv = seg[2*i], rv = seg[2*i+1];
    while(lv != rv) {
        if (lv > rv) lv = phi[lv];
        if (lv < rv) rv = phi[rv];
    }

    seg[i] = lv; // = rv
}/*}}}*/

void init_seg(int i=1, int l=0, int r=n-1) {/*{{{*/
    lazy[i] = 0;
    if (l == r) {
        seg[i] = a[l];
        return;
    }

    int m = (l+r)/2;
    init_seg(2*i, l, m);
    init_seg(2*i+1, m+1, r);
    update_node(i, l, r);
}/*}}}*/

void update_seg(int ql, int qr, int i=1, int l=0, int r=n-1) {/*{{{*/
    if (l == r) {
        seg[i] = phi[seg[i]];
        return;
    }

    if (ql <= l && r <= qr) {
        ++lazy[i];
        return;
    }

    int m = (l+r)/2;
    update_seg(ql, qr, 2*i, l, m);
    update_seg(ql, qr, 2*i+1, m+1, r);
    update_node(i, l, r);
}/*}}}*/

int query_seg(int ql, int qr, int i=1, int l=0, int r=n-1) {/*{{{*/
    if (ql <= l && r <= qr) return seg[i];

    int m = (l+r)/2;
    if (m+1 > qr) return query_seg(ql, qr, 2*i, l, m);
    if (m < ql) return query_seg(ql, qr, 2*i+1, m+1, r);

    int lv = query_seg(ql, qr, 2*i, l, m);
    int rv = query_seg(ql, qr, 2*i+1, m+1, r);

    while(lv != rv) {
        if (lv > rv) lv = phi[lv];
        if (lv < rv) rv = phi[rv];
    }

    return lv; // = rv
}/*}}}*/

void solve() {
    read_input();
    init_spd();
    init_phi();
    init_seg();

    for(auto [t, l, r] : quer) {
        if (t == 1) {
            update_seg(l, r);

        } else {
            int a = query_seg(l, r);
            // would like to know
            //  what is the sum of operations that have been preformed on each node in [l, r] (easy)
            //  what is the sum of operaitons that have been preformed on 1's in [l, r]

            //  what is the sum of the location of a in [l, r]

            // Q: what is the sum of operaitons that have been preformed on 1's in [l, r]
            //  we can initialize a rqru where rqru[i] = number of times i has been operated on

            // there are only nlog(n) (i, a) pairs where index i can reach a
        }
    }

    // for some f ∈ O(log(n)), φᶠ⁽ⁿ⁾(n) = 1
    //  so we can have a map S[i][k] -> ϕᵏ(a[i])

    // notice that ϕ(α) ≤ ϕ(ϕ(α))
    //  it follows that for query 2, after all operations, αᵢ will equal the largest next element in all of them
    //  this can be continued with a segment tree
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

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
