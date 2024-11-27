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
    int const Mod = 1e9 + 7;
    int my_ctz(ll k) {
        if (k == 0) return -1;
        int res = 0;
        while(k&1^1) ++res, k>>=1;
        return res;
    }

public:
    int numberOfWays(string s, string t, long long k) {
        // any operation on s corresponds to a non-trivial cyclic shift
        //  a state of s corresponds to some index

        // we can view the states of s as a graph, and opperations as edges
        //  this forms a complete graph over s.sz nodes
        //  the question becomes how many walks of length k are there from 0 to i
        //      let dp[i][j][k] be the number of walks from i to j of length k
        //          dp[i][j][k] = sum{m} dp[i][m][k/2] + dp[m][j][k/2]

        // since the graph is complete, there is a nice symetry, where dp[i][j][k] = dp[i][j'][k]
        //  one problem, however, is that dp[i][i][k] != dp[i][j][k]

        // so, we would like to know, for powers of 2, two numbers:
        //  the number of walks from a node to itself in k steps
        //  the number of walks from a node to another node in k steps
        //      these numbers are easyish to calculate
        //          to_itself[k] = to_itself[k/2]*to_itself[k/2] + ((n-1)*to_others[k/2])*to_others[k/2]
        //          to_others[k] = to_itself[k/2]*to_others[k/2] + ((n-1)*to_others[k/2])*(to_itself[k/2] + (n-2)*to_others[k/2]))

        // this is great -- if k is a power of 2

        if (k == 0) return s == t;

        int n = s.sz;

        auto get_ts = [&](ll fts, ll fto, ll sts, ll sto) {
            ll self_first =     fts*sts %Mod;
            ll other_first =    fto*sto%Mod * (n-1) %Mod;
            return self_first + other_first;
        };

        auto get_to = [&](ll fts, ll fto, ll sts, ll sto) {
            ll self_first = fts*sto%Mod;
            ll other_then_self = fto*sts%Mod;
            ll other_then_other = fto*sto%Mod * (n-2) %Mod;
            return self_first + other_then_self + other_then_other;
        };

        vpll dp(log2(k)+5);
        dp[0] = { 0, 1 };
        For(i, 1, dp.sz) {
            auto [ps, po] = dp[i-1];
            ll ts = get_ts(ps, po, ps, po), to = get_to(ps, po, ps, po);
            dp[i] = { ts, to };
        }

        if (k == 0) ps("SPOT 1");
        auto [cts, cto] = dp[my_ctz(max(k, 1ll))];
        k -= (k&-k);

        while(k > 0) {
            if (k == 0) ps("SPOT 2");
            auto [ots, oto] = dp[my_ctz(max(k, 1ll))];
            ll nts = get_ts(cts, cto, ots, oto);
            ll nto = get_to(cts, cto, ots, oto);
            cts = nts, cto = nto;
            k -= (k&-k);
        }

        // We are almost done!!!
        //  we now need to know how many of the nodes represent target
        //  that is, how many unique permutations of s create target
        //  first I would like to know what is the smallest string that generates s

        ll A = 31;

        vll powers(n);
        powers[0] = 1;
        For(i, 1, n) powers[i] = powers[i-1]*A%Mod;

        vll hv(n);
        For(i, 0, n) hv[0] = (hv[0] * A + (s[i]-'a')) % Mod;

        For(i, 1, n) hv[i] = ( (hv[i-1] - (powers[n-1] * (s[i-1]-'a'))%Mod + Mod)*A + (s[i-1]-'a') )%Mod;

        ll thv = 0;
        For(i, 0, n) thv = (thv * A + (t[i] - 'a')) % Mod;

        int repeats = transform_reduce(all(hv), 0, plus{}, [&](auto v){ return v == thv; });
        ps(repeats);


        // if (tflag == 0) return 0;
        return ((s == t)*cts + (repeats - (s == t))*cto) % Mod;
    }
};

// int main() {
//     auto sol = Solution();
//     string s, t;
//     ll k;
//
//     s = "abcd", t = "cdab", k = 2;
//     ps("Got", sol.numberOfWays(s, t, k));
//     ps("Expected ", 2);
//
//     s = "ababab", t = "ababab", k = 1;
//     ps("Got", sol.numberOfWays(s, t, k));
//     ps("Expected ", 2);
//
//     s = "goxoq", t = "dfqgl", k = 244326024901249;
//     ps("Got", sol.numberOfWays(s, t, k));
//     // ps("Expected ", 2);
//
//     return 0;
// }
