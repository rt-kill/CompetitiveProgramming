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

int n, k;

ve<str> carton;





int const S = 27;
ve<vvi> state_map;
void init_state_map() {
    state_map.assign(S, vvi());

    for(int c1=0; c1<3; ++c1) for(int c2=0; c2<3; ++c2) for(int c3=0; c3<3; ++c3) {
        vvi tmp(3, vi(3, 0));
        tmp[0][c1] = 1, tmp[1][c2] = 1, tmp[2][c3] = 1;
        state_map[c1 + 3*c2 + 9*c3] = tmp;
    }
}


int inv_state_map(vvi state) {
    vi cols(3, 0);
    for(int r=0; r<3; ++r)
        for(int c=1; c<3; ++c)
            if(state[r][c])  cols[r] = c;

    int res = cols[0] + 3*cols[1] + 9*cols[2];
    return res;
}


int get_next_state(int cur_state, vi rows) {
    int res = 0;

    vvi tmp = state_map[cur_state];
    for(int r=0; r<3; ++r) tmp[r].pb(rows[r]);

    vvi tmp2(3, vi(3, 0));
    for(int r=0; r<3; ++r) {
        tmp2[r][0] = 1;
        for(int c=0; c<3; ++c) tmp2[r][c] = tmp[r][c+1];
    }

    return inv_state_map(tmp2);
}



int get_sqd(int x, int nx, int cur_state, vi ncols) {
    vi cols(3, 0);
    for(int r=0; r<3; ++r)
        for(int c=1; c<3; ++c)
            if(state_map[cur_state][r][c]) cols[r] = c;


    int res = INT_MAX;

    for(int r1=0; r1<3; ++r1) for(int r2=0; r2<3; ++r2) {
        if(!ncols[r2]) continue;
        int dx = (nx-(x - (2-cols[dx]))), dy = abs(r1-r2);
        cmin(res, dx*dx + dy*dy);
    }

    return res;
}


ve<ve<vvi>> dp; // dp[i][x][state] = solution to first i cols where there is a last egg on col x, and cols [x-2:x] follow state


int transition(int i, int x, int k, int state) {
    if(k <= 0) return INT_MAX;
    if(i == n) return INT_MIN;
    if(dp[i][x][k][state] >= 0) return dp[i][x][k][state];


    int &res = dp[i][x][k][state];

    // take nothing
    res = transition(i+1, x, k, state);

    for(int c1=0; c1<=1; ++c1)for(int c2=0; c2<=1; ++c2)for(int c3=0; c3<=1; ++c3) {
        if(c1 == 0 && c2 == 0 && c3 == 0) continue;

        vi cols = { c1, c2, c3 };

        int diff = get_sqd(x, i, state, cols);
        int new_state = get_next_state(state, cols);

        // cmax(res, min(transition(i+1, i, k-c1-c2-c3, new_state), diff));
    }

    return res;
}


void solve() {
    init_state_map();

    re(n, k), rv(3, carton);

    vi dots(n);
    for(int i=0; i<n; ++i) dots[i] = (carton[0][i] == '.') + (carton[1][i] == '.') + (carton[2][i] == '.');

    int dots_cnt = accumulate(all(dots), 0);
    if(k > dots_cnt) { ps(-1); return; }

    dp.assign(100, ve<vvi>(100, vvi(301, vi(30, -1))));


    int res = -1;
    for(int c=0; c<n; ++c) {
        if(dots[c] > 0) {
            for(int c1=0; c1<=(carton[0][c]=='.'); ++c1) for(int c2=0; c2<=(carton[1][c]=='.'); ++c2) for(int c3=0; c3<=(carton[2][c]=='.'); ++c3) {
                int mid = min(int(c2==1 && (c1 == 1 || c3 == 1)), 4*(c1 == 1 && c3 == 1)) + (c1+c2+c3 == 1)*INT_MAX;
                cmax(res, min(mid, transition(c+1, c, k-c1-c2-c3, 2*c1 + 6*c2 + 18*c3)));
            }

            break;
        }
    }

    ps(sqrt(res)); return;

    // vi dots_sfx(all(dots));
    // for(int i=n-2; i>=0; ++i) dots_sfx[i] += dots_sfx[i+1];





    // make sure number of dots is at least k

    // dp[i][x][state] = solution to first i cols where there is a last egg on col x, and cols [x-2:x] follow state


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
