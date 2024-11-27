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
public:
    int minimumSum(vector<vector<int>>& grid) {

        // let vv1[r][c] be the soluiton for the top left rxc with 1 rectangle

        int n = grid.size(), m = grid[0].size();
        vvi vv1(n, vi(m)), vv2(n, vi(m)), vv3(n, vi(m)), vv4(n, vi(m));

        auto cvv1 = [&](auto r, auto c) {
            int vl = c, vr = 0, vu=r, vd=0;

            for(int i=0; i<=r; ++i) for(int j=0; j<=c; ++j) {
                if(grid[i][j] == 1) {
                    cmin(vu, i), cmax(vd, i);
                    cmin(vl, j), cmax(vr, j);
                }
            }

            if(vl > vr || vu > vd) return 1;
            return (vr - vl + 1) * (vd - vu + 1);
        };

        auto cvv2 = [&](auto r, auto c) {
            int vl = c, vr = 0, vu=n, vd=r;

            for(int i=r; i<n; ++i) for(int j=0; j<=c; ++j) {
                if(grid[i][j] == 1) {
                    cmin(vu, i), cmax(vd, i);
                    cmin(vl, j), cmax(vr, j);
                }
            }

            if(vl > vr || vu > vd) return 1;
            return (vr - vl + 1) * (vd - vu + 1);
        };

        auto cvv3 = [&](auto r, auto c) {
            int vl = m, vr = c, vu=r, vd=0;

            for(int i=0; i<=r; ++i) for(int j=c; j<m; ++j) {
                if(grid[i][j] == 1) {
                    cmin(vu, i), cmax(vd, i);
                    cmin(vl, j), cmax(vr, j);
                }
            }

            if(vl > vr || vu > vd) return 1;
            return (vr - vl + 1) * (vd - vu + 1);
        };

        auto cvv4 = [&](auto r, auto c) {
            int vl = m, vr = c, vu=n, vd=r;

            for(int i=r; i<n; ++i) for(int j=c; j<m; ++j) {
                if(grid[i][j] == 1) {
                    cmin(vu, i), cmax(vd, i);
                    cmin(vl, j), cmax(vr, j);
                }
            }

            if(vl > vr || vu > vd) return 1;
            return (vr - vl + 1) * (vd - vu + 1);
        };

        for(int r=0; r<n; ++r) for(int c=0; c<m; ++c) {
            vv1[r][c] = cvv1(r, c);
            vv2[r][c] = cvv2(r, c);
            vv3[r][c] = cvv3(r, c);
            vv4[r][c] = cvv4(r, c);
        }

        int res = INT_MAX;

        for(int r=1; r<n; ++r) for(int c=1; c<m; ++c) {
            int tv;

            // cut r then c on bottom
            tv = vv1[r-1][m-1] + vv2[r][c-1] + vv4[r][c];
            cmin(res, tv);

            // cut r then c on top
            tv = vv1[r-1][c-1] + vv3[r-1][c] + vv4[r][0];
            cmin(res, tv);

            // cut c then r on left
            tv = vv1[r-1][c-1] + vv2[r][c-1] + vv3[n-1][c];
            cmin(res, tv);

            // cut c then r on right
            tv = vv1[n-1][c-1] + vv3[r-1][c] + vv4[r][c];
            cmin(res, tv);
        }

        for(int r1=1; r1<n; ++r1) for(int r2=r1+1; r2<n; ++r2) {
            int tv = vv1[r1-1][m-1] + vv4[r2][0];


            int vl = m, vr = 0, vu=n, vd=0;
            for(int i=r1; i<r2; ++i) for(int j=0; j<m; ++j) {
                if(grid[i][j] == 1) {
                    cmin(vu, i), cmax(vd, i);
                    cmin(vl, j), cmax(vr, j);
                }
            }

            if(vl > vr || vu > vd) tv += 1;
            else tv += (vr - vl + 1) * (vd - vu + 1);
            cmin(res, tv);

        }

        for(int c1=1; c1<m; ++c1) for(int c2=c1+1; c2<m; ++c2) {
            int tv = vv1[n-1][c1-1] + vv4[0][c2];


            int vl = m, vr = 0, vu=n, vd=0;
            for(int i=0; i<n; ++i) for(int j=c1; j<c2; ++j) {
                if(grid[i][j] == 1) {
                    cmin(vu, i), cmax(vd, i);
                    cmin(vl, j), cmax(vr, j);
                }
            }

            if(vl > vr || vu > vd) tv += 1;
            else tv += (vr - vl + 1) * (vd - vu + 1);
            cmin(res, tv);
        }

        return res;
    }
};
