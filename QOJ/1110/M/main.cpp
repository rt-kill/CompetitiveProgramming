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

int n, m;
vpi vertices, points;
pi start;

vvi point_to_line_type;

ve<vvpi> mps;

void solve() {
    re(n, m), rv(n, vertices), re(start);

    // make all poins appear above the x axis
    int dy = -transform_reduce(all(vertices), INT_MAX, [](auto l, auto r){ return min(l, r); }, [](auto v){ return v.se; });
    for(auto &[x, y] : vertices) y+=dy;
    start.se += dy;

    // I would like all points to appear under the line y=x
    int dx = -transform_reduce(all(vertices), INT_MAX, [](auto l, auto r){ return min(l, r); }, [](auto v){ return v.fi - v.se; });
    for(auto &[x, y] : vertices) x+=dx;
    start.fi += dx;

    int sx = transform_reduce(all(vertices), INT_MIN, [](auto l, auto r){ return max(l, r); }, [](auto v){ return v.fi; })+1;
    int sy = transform_reduce(all(vertices), INT_MIN, [](auto l, auto r){ return max(l, r); }, [](auto v){ return v.se; })+1;
    point_to_line_type.assign(sx, vi(sy));

    vertices.pb(vertices[0]);
    for(int i=0; i<vertices.sz-1; ++i) {
        auto [x0, y0] = vertices[i];
        auto [x1, y1] = vertices[i+1];

        int line_type = (x0 == x1); // 1 means vertical

        while(x0 < x1) {
            points.pb({ ++x0, y0 });
            point_to_line_type[x0][y0] = line_type;
        }

        while(x0 > x1) {
            points.pb({ --x0, y0 });
            point_to_line_type[x0][y0] = line_type;
        }

        while(y0 < y1) {
            points.pb({ x0, ++y0 });
            point_to_line_type[x0][y0] = line_type;
        }

        while(y0 > y1) {
            points.pb({ x0, --y0 });
            point_to_line_type[x0][y0] = line_type;
        }
    }


    int siz = transform_reduce(all(points), 0, [](auto l, auto r){ return max(l, r); }, [](auto v){ return v.fi + v.se; }) + 1;
    mps.assign(2, vvpi(siz, vpi()));

    for(auto [x, y] : points) mps[0][x-y].pb({x, y}), mps[1][x+y].pb({x, y});

    // auto cmp1 = [](auto l, auto r) { return (l.se - l.fi) < (r.se - r.fi); };
    // auto cmp2 = [](auto l, auto r) { return (l.fi + l.se) < (r.fi + r.se); };

    for(int j=0; j<siz; ++j) sort(all(mps[0][j])), sort(all(mps[1][j]));

    vpi res;
    int dir = 0; // 0 up right, 1 up left, 2 down left, 3 down right
    pi cur = start;

    rep(m) {
        auto [cx, cy] = cur;
        int line_id = (dir%2) ? cx+cy : cx-cy;
        vpi &cur_line = mps[dir%2][line_id];

        // ps(cx, cy, dir, line_id);
        // ps(cx, cy, dir, cur_line);


        int nx, ny;

        if(dir == 0 || dir == 3) {
            auto nxt = ++lower_bound(all(cur_line), cur);
            nx = nxt->fi, ny = nxt->se;
        } else if (dir == 1 || dir == 2) {
            auto nxt = --lower_bound(all(cur_line), cur);
            nx = nxt->fi, ny = nxt->se;
        }

        res.pb({nx, ny});

        int tp = point_to_line_type[nx][ny];
        // ps(nx, ny, tp);

        if(dir == 0 && tp == 0) dir = 3;
        else if(dir == 0 && tp == 1) dir = 1;
        else if(dir == 1 && tp == 0) dir = 2;
        else if(dir == 1 && tp == 1) dir = 0;
        else if(dir == 2 && tp == 0) dir = 1;
        else if(dir == 2 && tp == 1) dir = 3;
        else if(dir == 3 && tp == 0) dir = 0;
        else if(dir == 3 && tp == 1) dir = 2;

        cur = { nx, ny };
    }

    for(auto [x, y] : res) ps(x-dx, y-dy);
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
