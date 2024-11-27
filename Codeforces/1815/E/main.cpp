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

// Let 0 and n+1 have the Oscillators 1
// Let i be the first non-zero oscillator with only 1's
//  delete all oscillators below it
//  the validity of this should be clear

// We are dealing with a deterministic finite dynamic system:
//  Deterministic: From any single state, there is a unique next state that we can determine
//  Finite: The number of total states is finite

// A state can be defined as follows:
//      The current point our particle is on
//      The current direction of the particle (either up or down)
//      The index of each oscillators state

// We can make the following observations
//  As long as an Oscillator is rechable and has a 0, the Oscillator below it is rechable
//  If an Oscillator is rechable, then all indices of the Oscillator are rechable

// We now define an equivalence relation on states:
//  Two states are equivalent IFF for all k≥0
//      Nᵏ(S₁).pos = Nᵏ(S₂).pos
//  Where N is the map from a state to the next state and pos is the partical position of a state
// It should be clear that this is a valid equivalence relation

// We can come up with an intuitive method of comparing states (Post initial modification)
//  Two states S₁, S₂ are equivalent IFF
//      S₁.pos = S₂.pos
//      S₁.dir = S₂.dir
//      For all 0≤i≤n+1, (oscillator indices) 0≤k
//          osc[i][S₁.ind[i] + k] = osc[i][S₂.ind[i] + k] (with wrapping)
//
//  [ ⇐ ] Should be clear via a contradiction
//  [ ⇒ ] Should be clear via the contrapositive

// I am going to refrain from inserting (Post initial modification) from now on

// Let now consider the following equivalence relation on (o, i) pairs -- (oscillator, index)
//  (o₁, i₁) ≡ (o₂, i₂) ↔ (o₁ = o₂) && o[i₁:]+o[:i₁] == o[i₂:] + o[:i₂]
//
// Again, this should clearly be an equivalence relation
//  Additionally, S₁ ≡ S₂ ↔ ... && ∀[0≤o≤n+1], (o, S₁.ind[o]) ≡ (o, S₂.ind[o])
//
// We also see that (o₁, i₁) ≡ (o₂, i₂) ↔ (o₁, i₁+1) ≡ (o₂, i₂+1)

// Intuitively, we can modify all oscillators by taking the min index neq 0 and deleting all values after that
// DO THIS! (can be done via zalgo, proof at end)
// Afterwards, S₁≡S₂ ↔ S₁=S₂

// So we have found the set of states modded by our equivalence relation

// Since N is a bijection, all states will eventually return to themselfs
// any state will eventually reach some state with arbitrary pos
//  thus before any state returns to itself, it will touch every pos some positive multiple of osc.sz times
//  additionally, every pos except for the start and end will shift an even number of times


// The cycle must have even length
//  Oscillators with an even number of ones have a direction attributed to each index
//  Let dp[i] be the number of times i is hit if osc[i] = '1', and start = i

// dp[n] = 2


int const Mod = 998244353;

int n;
ve<str> osc;

str osc_reduce(str osc) {/*{{{*/
    if (*min_element(all(osc)) == *max_element(all(osc)))
        return osc.substr(0, 1);

    int k = osc.sz;
    vi zarr(k, 0);

    int l=1, d=0;
    For(i, 1, k) {
        if (i + zarr[i-l] < l+d ) {
            zarr[i] = zarr[i-l];
            continue;
        }

        d=max(l+d-i, 0), l=i;
        while(d < k && osc[d] == osc[(l+d)%k]) ++d;
        zarr[i] = d;
    }

    int ind = find(all(zarr), k) - zarr.begin();
    return osc.substr(0, ind);
}/*}}}*/

ll gcd(ll a, ll b) {/*{{{*/
    if (a < b) swap(a, b);
    if (b == 0) return a;
    return gcd(b, a%b);
}/*}}}*/

// dp[i] := number of edges out of i if osc[i] = '1' and we start at i (going down)
//  osc[i+1].sz must divide the number of edges out of (i+1)
//  if osc[i+1] has an odd number of zeros, then 2*osc[i+1].sz must divide number of edges out of (i+1)
//  number of edges out of osc going down must divide dp[i+1]

ve<map<ll, ll>> oszfact, oszdfact, ndfact, dpfact;
void pop_facts() {
}

vll dp, dp2;
void pop_dp(int i) {
    int zpar=0;
    each(c, osc[i+1]) zpar ^= (c == '0');

    int osz = osc[i+1].sz;
    ll ncl = dp[i+1];

    auto oszf = oszfact[i+1], nclf = dpfact[i+1];

    if (zpar) {
        // k = 2*m*osz = number of edges out of i+1
        // m*osz | ncl

        ll m = ncl/gcd(osz, ncl);
        dp[i] = m*osz;

        for(auto [ k, v ] : nclf) cmax(dpfact[i][k], v);
        for(auto [ k, v ] : oszf) cmax(dpfact[i][k], v);

        // dp2[i] = (dp2[i+1]*((dp[i]/dp[i+1])%Mod) + dp[i]*2)%Mod;
    }

    if (zpar^1) {
        int nd=0, side=0;
        each(c, osc[i+1]) {
            side ^= (c == '0');
            nd += side;
        }

        // k = m*osz = number of edges out of i+1
        // m*nd | ncl

        ll m = ncl/gcd(nd, ncl);
        dp[i] = m*(osz-nd);

        for(auto [ k, v ] : nclf) {
            ll tmp = min(nclf[k], ndfact[i+1][k]);
            if ( v > tmp ) dpfact[i][k] += v - tmp;
        }

        for(auto [ k, v ] : oszdfact[i+1] )  dpfact[i][k] += v;

        // dp2[i] = (dp2[i+1]*(((m*nd)/dp[i+1])%Mod) + dp[i]*2)%Mod;
    }
}

void solve() {
    re(n);
    osc.rsz(n+2);
    osc[0] = "1";
    For(i, 1, n+1) cin >> osc[i];
    osc[n+1] = "1";

    auto tmp = osc.begin();
    do ++tmp; while(*min_element(all((*tmp))) == '0');

    osc.erase(++tmp, osc.end());
    n = osc.sz-2;
    each(v, osc) v = osc_reduce(v);

    dpfact.assign(n+1, map<ll, ll>());
    dp2.assign(n+1, -1);
    dp2[n] = 2;
    Rof(i, 0, n) pop_dp(i);
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
