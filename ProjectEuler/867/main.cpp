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


/*


question: how many ways are there to tile it with only squares and triangles
    - ~2^10, not that many


suppose we have a lattice

    . . . .{{{
   . . . . .
  . . . . . .
 . . . . . . .
  . . . . . .
   . . . . .
    . . . .

------------------
    * . . .
   . . . . .
  . . . . . .
 . . . . . . .
  . . . . . .
   . . . . .
    . . . .
--
    . * . .
   * * . . .
  . . . . . .
 . . . . . . .
  . . . . . .
   . . . . .
    . . . .
--
    . . * .
   . . * . .
  * * * . . .
 . . . . . . .
  . . . . . .
   . . . . .
    . . . .

--------------------
    . * . .
   * * . . .
  . . . . . .
 . . . . . . .
  . . . . . .
   . . . . .
    . . . .
--
    . * . .
   . * . . .
  * * . . . .
 . . . . . . .
  . . . . . .
   . . . . .
    . . . .
--
    . * . .
   . . * . .
  . . * . . .
 * * * . . . .
  . . . . . .
   . . . . .
    . . . .}}}



in how many ways can we assign 1's and 0's so that no 1's are adjacent

 */


int const Mod = 1e9+7;


ll modpow(ll a, ll b) {
    ll res = 1;
    for(ll e=1, p=a; e<=b; e<<=1, p=p*p%Mod)
        if(e&b) res = res*p%Mod;
    return res;
}

map<pair<int, int>, int> cnts = {/*{{{*/

    // only doable with triangles -- all 1's
    { {1, 1}, 1 },
    { {2, 1}, 1 },
    { {3, 1}, 1 },
    { {4, 1}, 1 },
    { {5, 1}, 1 },
    { {6, 1}, 1 },
    { {7, 1}, 1 },
    { {8, 1}, 1 },
    { {9, 1}, 1 },
    { {10, 1}, 1 },

    // require at least 1 hex -- number of hex's insertable
    //  cnts[{a, 2}] = cnts[{a-1, 2}] + (1+cnts[{a-2, 2}])
    { {3, 2}, 1 },
    { {4, 2}, 2 },
    { {5, 2}, 4 },
    { {6, 2}, 7 },
    { {7, 2}, 12 },
    { {8, 2}, 20 },
    { {9, 2}, 33 },
    { {10, 2}, 54 },

    // require at least one hex connecting any two rows
    //  cnts[{a, 3}]    = cnts[{a-1, 3}] + (cnts[{a-2, 2}] + cnts[{a-2, 3}]) + (cnts[{a-2, 2}] + cnts[{a-2, 3}])
    //                  = cnts[{a-1, 3}] + 2*cnts[{a-2, 3}] + 2*cnts[{a-2, 2}];
    { {5, 3}, 2 },
    { {6, 3}, 6 },


    // require interleaving hex's between any two rows
    //  cnts[{a, 4}]    = cnts[{a-1, 4}]
    //                  + cnts[{a-2, 4}] + cnts[{a-2, 3}]
    //                  + cnts[{a-2, 4}] + cnts[{a-2, 2}]*cnts[{a-3, 2}]
    //                  + cnts[{a-2, 4}] + cnts[{a-2, 3}]
    //                  + cnts[{a-2, 4}] + cnts[{a-2, 3}] + cnts[{a-3, 3}] + cnts[{a-3, 2}]


    { {6, 4}, 4 },
    // { {7, 4},  },
    // { {8, 4},  },
    // { {9, 4},  },
    // { {10, 4},  },

    // cnts[{a, 5}]     = cnts[{a-1, 5}]
    //                  + cnts[{a-2, 5}] + cnts[{a-2, 4}]
    //                  + cnts[{a-2, 5}] + cnts[{a-2, 3}]*cnts[{a-4, 2}]
    //                  + cnts[{a-2, 5}] + cnts[{a-2, 2}]*cnts[{a-3, 3}]
    //                  + cnts[{a-2, 5}] + cnts[{a-2, 4}]
    //
    //                      + cnts[{a-2, 5}] + cnts[{a-2, 4}]
    //                      + cnts[{a-2, 3}]*cnts[{a-4, 2}]
    //                      + cnts[{a-2, 2}] * cnts[{a-3, 2}]
    //
    //                      + cnts[{a-2, 5}] + cnts[{a-2, 4}]
    //                      + cnts[{a-2, 2}]*cnts[{a-3, 3}]
    //                      + cnts[{a-2, 3}]
    //
    //                      + cnts[{a-2, 3}]*cnts[{a-4, 2}]
    //                      + cnts[{a-2, 2}]*cnts[{a-3, 3}]
    //                      + cnts[{a-2, 2}]*cnts[{a-4, 2}]

    { {7, 5}, 18 },
    // { {} }
};

void init_cnts() {
    cnts[{7, 3}] = cnts[{6, 3}] + 2*cnts[{5, 3}] + 2*cnts[{5, 2}];
    cnts[{8, 3}] = cnts[{7, 3}] + 2*cnts[{6, 3}] + 2*cnts[{6, 2}];
    cnts[{9, 3}] = cnts[{8, 3}] + 2*cnts[{7, 3}] + 2*cnts[{7, 2}];
    cnts[{10, 3}] = cnts[{9, 3}] + 2*cnts[{8, 3}] + 2*cnts[{8, 2}];

    //  cnts[{a, 4}]    = cnts[{a-1, 4}]
    //                  + cnts[{a-2, 4}] + cnts[{a-2, 3}]
    //                  + cnts[{a-2, 4}] + cnts[{a-2, 2}]*cnts[{a-3, 2}]
    //                  + cnts[{a-2, 4}] + cnts[{a-2, 3}]
    //                  + cnts[{a-2, 4}] + cnts[{a-2, 3}] + cnts[{a-3, 3}] + cnts[{a-3, 2}]

    cnts[{7, 4}]    = (cnts[{7-1, 4}]
                    + cnts[{7-2, 4}] + cnts[{7-2, 3}]
                    + cnts[{7-2, 4}] + cnts[{7-2, 2}]*cnts[{7-3, 2}]
                    + cnts[{7-2, 4}] + cnts[{7-2, 3}]
                    + cnts[{7-2, 4}] + cnts[{7-2, 3}] + cnts[{7-3, 3}] + cnts[{7-3, 2}])%Mod;
    cnts[{8, 4}]    = (cnts[{8-1, 4}]
                    + cnts[{8-2, 4}] + cnts[{8-2, 3}]
                    + cnts[{8-2, 4}] + cnts[{8-2, 2}]*cnts[{8-3, 2}]
                    + cnts[{8-2, 4}] + cnts[{8-2, 3}]
                    + cnts[{8-2, 4}] + cnts[{8-2, 3}] + cnts[{8-3, 3}] + cnts[{8-3, 2}])%Mod;
    cnts[{9, 4}]    = (cnts[{9-1, 4}]
                    + cnts[{9-2, 4}] + cnts[{9-2, 3}]
                    + cnts[{9-2, 4}] + cnts[{9-2, 2}]*cnts[{9-3, 2}]
                    + cnts[{9-2, 4}] + cnts[{9-2, 3}]
                    + cnts[{9-2, 4}] + cnts[{9-2, 3}] + cnts[{9-3, 3}] + cnts[{9-3, 2}])%Mod;
    cnts[{10, 4}]   = (cnts[{10-1, 4}]
                    + cnts[{10-2, 4}] + cnts[{10-2, 3}]
                    + cnts[{10-2, 4}] + cnts[{10-2, 2}]*cnts[{10-3, 2}]
                    + cnts[{10-2, 4}] + cnts[{10-2, 3}]
                    + cnts[{10-2, 4}] + cnts[{10-2, 3}] + cnts[{10-3, 3}] + cnts[{10-3, 2}])%Mod;

    cnts[{8, 5}]     = (cnts[{8-1, 5}]
                     + cnts[{8-2, 5}] + cnts[{8-2, 4}]
                     + cnts[{8-2, 5}] + cnts[{8-2, 3}]*cnts[{8-4, 2}]
                     + cnts[{8-2, 5}] + cnts[{8-2, 2}]*cnts[{8-3, 3}]
                     + cnts[{8-2, 5}] + cnts[{8-2, 4}]

                         + cnts[{8-2, 5}] + cnts[{8-2, 4}]
                         + cnts[{8-2, 3}]*cnts[{8-4, 2}]
                         + cnts[{8-2, 2}] * cnts[{8-3, 2}]

                         + cnts[{8-2, 5}] + cnts[{8-2, 4}]
                         + cnts[{8-2, 2}]*cnts[{8-3, 3}]
                         + cnts[{8-2, 3}]

                         + cnts[{8-2, 3}]*cnts[{8-4, 2}]
                         + cnts[{8-2, 2}]*cnts[{8-3, 3}]
                         + cnts[{8-2, 2}]*cnts[{8-4, 2}])%Mod;
    cnts[{9, 5}]     = (cnts[{9-1, 5}]
                     + cnts[{9-2, 5}] + cnts[{9-2, 4}]
                     + cnts[{9-2, 5}] + cnts[{9-2, 3}]*cnts[{9-4, 2}]
                     + cnts[{9-2, 5}] + cnts[{9-2, 2}]*cnts[{9-3, 3}]
                     + cnts[{9-2, 5}] + cnts[{9-2, 4}]

                         + cnts[{9-2, 5}] + cnts[{9-2, 4}]
                         + cnts[{9-2, 3}]*cnts[{9-4, 2}]
                         + cnts[{9-2, 2}] * cnts[{9-3, 2}]

                         + cnts[{9-2, 5}] + cnts[{9-2, 4}]
                         + cnts[{9-2, 2}]*cnts[{9-3, 3}]
                         + cnts[{9-2, 3}]

                         + cnts[{9-2, 3}]*cnts[{9-4, 2}]
                         + cnts[{9-2, 2}]*cnts[{9-3, 3}]
                         + cnts[{9-2, 2}]*cnts[{9-4, 2}])%Mod;
    cnts[{10, 5}]     = (cnts[{10-1, 5}]
                     + cnts[{10-2, 5}] + cnts[{10-2, 4}]
                     + cnts[{10-2, 5}] + cnts[{10-2, 3}]*cnts[{10-4, 2}]
                     + cnts[{10-2, 5}] + cnts[{10-2, 2}]*cnts[{10-3, 3}]
                     + cnts[{10-2, 5}] + cnts[{10-2, 4}]

                         + cnts[{10-2, 5}] + cnts[{10-2, 4}]
                         + cnts[{10-2, 3}]*cnts[{10-4, 2}]
                         + cnts[{10-2, 2}] * cnts[{10-3, 2}]

                         + cnts[{10-2, 5}] + cnts[{10-2, 4}]
                         + cnts[{10-2, 2}]*cnts[{10-3, 3}]
                         + cnts[{10-2, 3}]

                         + cnts[{10-2, 3}]*cnts[{10-4, 2}]
                         + cnts[{10-2, 2}]*cnts[{10-3, 3}]
                         + cnts[{10-2, 2}]*cnts[{10-4, 2}])%Mod;
}/*}}}*/



void hex_printer(vvi hex) {
    cout << '\n' << '\n';

    int sl = hex[0].size();

    for(int r=0; r<hex.size(); ++r) {
        int ws = (hex.size()-hex[r].size()+1)/2;
        for(int _=0; _<ws; ++_) cout << ' ';
        for(int c=0; c<hex[r].size(); ++c) cout << hex[r][c] << ' ';
        cout << '\n';
    }

    cout << '\n';
}


map<vvi, ll> mem;

ll inner_hex_dp(vvi state) {
    int option_count = transform_reduce(all(state), 0, plus{},
        [](auto v){ return accumulate(all(v), 0); });
    if (option_count == 0) return 1;

    if (mem.count(state)) return mem[state];
    ll &res = mem[state];

    int r, c, t, d;
    for(r=0, c=0, t=state[r].size(); state[r][c]==0;
        r = r + (c+1==t),
        c = (c+1==t ? 0 : c+1),
        t = state[r].size()
    );

    d = (r >= (int(state.size())/2))-1;


    vvi o1(all(state)), o2(all(state));

    // don't take
    o1[r][c] = 0;

    // take
    o2[r][c] = 0;

    if (c+1 >= 0 && c+1 < o2[r].size()) o2[r][c+1] = 0;
    if (r+1 < o2.size() && c-d-1 >= 0   && c-d-1 < o2[r+1].size()) o2[r+1][c-d-1] = 0;
    if (r+1 < o2.size() && c-d >= 0     && c-d < o2[r+1].size()) o2[r+1][c-d] = 0;


    res += inner_hex_dp(o1);
    res += inner_hex_dp(o2);
    res %= Mod;

    // cout << "- Start -" << '\n';
    // hex_printer(state);
    // hex_printer(o1);
    // hex_printer(o2);
    // ps(res);
    // cout << "- End -" << '\n';

    return res;
}

map<int, ll> mem3;
ll inner_hex(int sl) {
    if (mem3.count(sl)) return mem3[sl];
    ll &res = mem3[sl];

    vvi tmp(2*sl-1);
    for(int r=0; r<tmp.sz; ++r) tmp[r].assign((2*sl-1) - abs((sl-1)-r), 1);
    res = inner_hex_dp(tmp);

    // ps(sl, res);

    return res;
}



map<arr<int, 2>, ll> mem4;
ll another_dp(int b, int h) {
    if (mem4.count({b, h})) return mem4[{b, h}];
    ll &res = mem4[{b, h}];

    vvi tmp(h-1);
    for(int r=0; r<h-1; ++r) tmp[r].assign(b-(h-r), 1);
    res = inner_hex_dp(tmp);

    // ps(b, h, res);

    return res;
}



map<arr<int, 2>, ll> mem2 = { { {1, 1}, 5 } };
ll rec(int s1, int s2) {
    if(mem2.count({s1, s2})) return mem2[{s1, s2}];
    ll &res = mem2[{s1, s2}];

    if (min(s1, s2) == 0) res = inner_hex(max(s1, s2));
    else {
        // shrink s1
        for(int dl=1; dl<=s1; ++dl) {
            // res += modpow(another_dp(s1, dl), 6) * rec(s2, s1-dl) % Mod;
            res += rec(s2, s1-dl) % Mod;
        }
    }


    res %= Mod;
    // ps(s1, s2, res);

    return res;
}


// int const N = 1;
// int const N = 2;
// int const N = 5;
// int const N = 8;
int const N = 10;

void solve() {
    init_cnts();

    for(int i=2; i<=N; ++i) ps(i, 2ll*rec(i, i)%Mod);
    // ll res = rec(N, N);
    // ps(res);
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
