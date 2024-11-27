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


// for each position, I could binary search for the longest palindrome cenetered at it
//  via string hashing to tell if a substring is a plidrome in O(1)
//  from here, I can binary search again to find the largest string one removed form this largest palindrome that is the same


int n;
string s;


int const Mod = 1e9+7, A = 101;


vll apows;
void init_apows() {
    apows.assign(n+1, 1);
    for(int i=1; i<=n; ++i) apows[i] = apows[i-1]*A%Mod;
}


vll fwd_hsh, bwd_hsh;

void init_hsh() {
    fwd_hsh.resize(n);
    ll h = 0;
    for(int i=0; i<n; ++i) h = (h*A+(s[i]-'A'+1))%Mod, fwd_hsh[i] = h;

    bwd_hsh.resize(n);
    ll t = 0;
    for(int i=n-1; i>=0; --i) t = (t*A+(s[i]-'A'+1))%Mod, bwd_hsh[i] = t;
}

ll query_fwd_hsh(int l, int r) { // inclusive
    return (fwd_hsh[r] - (l>0 ? fwd_hsh[l-1] * apows[r-l+1] % Mod : 0) + Mod) % Mod;
}

ll query_bwd_hsh(int l, int r) { // inclusive
    return (bwd_hsh[l] - (r+1<n ? bwd_hsh[r+1] * apows[r-l+1] % Mod : 0) + Mod) % Mod;
}


void solve() {
    re(s), n = s.size();

    init_apows();
    init_hsh();


    vpi good;

    // odd length palindromes
    for(int i=0; i<n; ++i) {
        // binary search on radius of palindrome
        int l=0, r=min(i, n-i-1);
        while(l < r) {
            int m = (l+r+1)/2;
            ll fh = query_fwd_hsh(i-m, i+m), bh = query_bwd_hsh(i-m, i+m);
            if(fh == bh) l = m;
            else r = m-1;
        }

        int mir = l;

        if (i-mir == 0 || i+mir == n-1) { good.pb({i-mir, i+mir}); continue; }

        int ls = i-mir-2, rs = i+mir+2;
        if (ls < 0 || rs > n-1 || s[ls] != s[rs]) { good.pb({i-mir-1, i+mir+1}); continue; }

        // binary search on diamater of surrounding match
        l = 0, r = min(ls, n-rs-1);
        while(l < r) {
            int m = (l+r+1)/2;
            ll lsh = query_fwd_hsh(ls-m, ls), rsh = query_bwd_hsh(rs, rs+m);
            if(lsh == rsh) l = m;
            else r = m-1;
        }

        good.pb({ ls-l, rs+l });
    }


    // even length (i is the left position of the center)
    for(int i=0; i<n-1; ++i) {
        if (s[i] != s[i+1]) { good.pb({i, i+1}); continue; }

        // binary search on radius of palindrome
        int l=0, r=min(i, n-i-2);
        while(l < r) {
            int m = (l+r+1)/2;
            ll fh = query_fwd_hsh(i-m, i+m+1), bh = query_bwd_hsh(i-m, i+m+1);
            if(fh == bh) l = m;
            else r = m-1;
        }

        int mir = l;

        if (i-mir == 0 || i+mir+1 == n-1) { good.pb({i-mir, i+mir+1}); continue; }

        int ls = i-mir-2, rs = i+mir+3;
        if (ls < 0 || rs > n-1 || s[ls] != s[rs]) { good.pb({i-mir-1, i+mir+2}); continue; }

        // binary search on diamater of surrounding match
        l = 0, r = min(ls, n-rs-1);
        while(l < r) {
            int m = (l+r+1)/2;
            ll lsh = query_bwd_hsh(ls-m, ls), rsh = query_fwd_hsh(rs, rs+m);
            if(lsh == rsh) l = m;
            else r = m-1;
        }

        good.pb({ ls-l, rs+l });
    }

    int best_length = transform_reduce(all(good), 0, [](int l, int r){ return max(l, r); }, [](auto v){ return v.se-v.fi+1; });
    vpi best;
    copy_if(all(good), back_inserter(best), [&](auto v){ return v.se-v.fi+1 == best_length; });
    sort(all(best));
    auto [rl, rr] = best[0];
    ps(s.substr(rl, rr-rl+1));
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
