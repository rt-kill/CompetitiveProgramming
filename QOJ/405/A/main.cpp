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

int n, t;
ve<arr<int, 4>> segs;
int sx, sy;

void solve() {
    re(n, t), rv(n, segs);
    sx = segs[0][0], sy = segs[0][1];
    int sd =    0 * (segs[0][1] == segs[0][3] && segs[0][0] < segs[0][2]) +
                1 * (segs[0][0] == segs[0][2] && segs[0][1] < segs[0][3]) +
                2 * (segs[0][1] == segs[0][3] && segs[0][0] > segs[0][2]) +
                3 * (segs[0][0] == segs[0][2] && segs[0][1] > segs[0][3]);

    vvpi ips_map(n); // map from a seg i to all intersection points along that seg sorted
    vpi pnts;

    for(int i=0; i<n; ++i) {
        auto [bx1, by1, ex1, ey1] = segs[i];
        pnts.pb({bx1, by1});
        pnts.pb({ex1, ey1});

        vpi ips = { {bx1, by1}, {ex1, ey1} };

        for(int j=0; j<n; ++j) {
            if(i == j) continue;
            auto [bx2, by2, ex2, ey2] = segs[j];

            if(bx1 == ex1 && bx2 == ex2) continue;
            else if (bx1 == ex1) {
                int x1 = bx1, y2 = by2;

                if(y2 <= min(by1, ey1) || y2 >= max(by1, ey1)) continue;
                if(x1 <= min(bx2, ex2) || x1 >= max(bx2, ex2)) continue;


                pnts.pb({ x1, y2 });
                ips.pb({ x1, y2 });
            }

            if(by1 == ey1 && by2 == ey2) continue;
            else if (by1 == ey1) {
                int y1 = by1, x2 = bx2;

                if(x2 <= min(bx1, ex1) || x2 >= max(bx1, ex1)) continue;
                if(y1 <= min(by2, ey2) || y1 >= max(by2, ey2)) continue;

                pnts.pb({ x2, y1 });
                ips.pb({ x2, y1 });
            }
        }

        sort(all(ips));
        ips_map[i] = ips;
    }

    sort(all(pnts));
    pnts.erase(unique(all(pnts)), pnts.end());

    map<pi, int> pnt_to_indx;
    for(int i=0; i<pnts.sz; ++i) pnt_to_indx[pnts[i]] = i;

    vvi nxt(4, vi(pnts.sz, -1)); // map from point direction pair (i,d) to index of next point hit

    for(int i=0; i<n; ++i) {
        auto [bx, by, ex, ey] = segs[i];

        if(by == ey) { // direciton is either 0 or 2
            for(int j=0; j<ips_map[i].sz; ++j) {
                if(j+1<ips_map[i].sz) nxt[0][pnt_to_indx[ips_map[i][j]]] = pnt_to_indx[ips_map[i][j+1]];
                else nxt[0][pnt_to_indx[ips_map[i][j]]] = pnt_to_indx[ips_map[i][j-1]];

                if(j > 0) nxt[2][pnt_to_indx[ips_map[i][j]]] = pnt_to_indx[ips_map[i][j-1]];
                else nxt[2][pnt_to_indx[ips_map[i][j]]] = pnt_to_indx[ips_map[i][j+1]];
            }
        }

        if(bx == ex) { // direction is either 1 or 3
            for(int j=0; j<ips_map[i].sz; ++j) {
                if(j+1<ips_map[i].sz) nxt[1][pnt_to_indx[ips_map[i][j]]] = pnt_to_indx[ips_map[i][j+1]];
                else nxt[1][pnt_to_indx[ips_map[i][j]]] = pnt_to_indx[ips_map[i][j-1]];

                if(j > 0) nxt[3][pnt_to_indx[ips_map[i][j]]] = pnt_to_indx[ips_map[i][j-1]];
                else nxt[3][pnt_to_indx[ips_map[i][j]]] = pnt_to_indx[ips_map[i][j+1]];
            }
        }
    }


    vi is_end_point(pnts.sz);
    for(auto [bx,by,ex,ey] : segs) {
        is_end_point[pnt_to_indx[{bx, by}]] = 1;
        is_end_point[pnt_to_indx[{ex, ey}]] = 1;
    }


    vvi seen(4, vi(pnts.sz, 0));
    int tot_time = 0, cn=pnt_to_indx[{sx, sy}], cd = sd, nn, nd;

    while(true) {
        if(seen[cd][cn] > 0) {
            t = (t-seen[cd][cn])%(tot_time-seen[cd][cn]) + seen[cd][cn];
            tot_time = seen[cd][cn];
            seen.assign(4, vi(pnts.sz, 0));
        } else {
            seen[cd][cn] = tot_time;
        }

        nn = nxt[cd][cn], nd = (cd + 1 + is_end_point[nn]) % 4;

        int dt;
        auto [cx, cy] = pnts[cn];
        auto [nx, ny] = pnts[nn];
        dt = abs(cx - nx) + abs(cy - ny);
        if(tot_time + dt >= t) break;

        tot_time += dt;
        cn = nn, cd = nd;
    }

    auto [cx, cy] = pnts[cn];
    cx += (t - tot_time) * (cd == 0) - (t - tot_time) * (cd == 2);
    cy += (t - tot_time) * (cd == 1) - (t - tot_time) * (cd == 3);
    ps(cx, cy);
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
