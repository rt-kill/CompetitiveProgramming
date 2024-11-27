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
    vll nums1, nums2;
    vll n1, z1, p1, n2, z2, p2;
    ll ncnt, zcnt, pcnt;

    void init() {/*{{{*/
        n1.clear(), z1.clear(), p1.clear(), n2.clear(), z2.clear(), p2.clear();

        copy_if(all(nums1), back_inserter(n1), [](auto v){ return v < 0; });
        copy_if(all(nums1), back_inserter(z1), [](auto v){ return v == 0; });
        copy_if(all(nums1), back_inserter(p1), [](auto v){ return v > 0; });

        copy_if(all(nums2), back_inserter(n2), [](auto v){ return v < 0; });
        copy_if(all(nums2), back_inserter(z2), [](auto v){ return v == 0; });
        copy_if(all(nums2), back_inserter(p2), [](auto v){ return v > 0; });

        ncnt = (ll) n1.sz * (ll) p2.sz + (ll) n2.sz * (ll) p1.sz;
        zcnt = (ll) z1.sz * (ll) nums2.sz + (ll) z2.sz * (ll) nums1.sz - (ll) z1.sz * (ll) z2.sz;
        pcnt = (ll) p1.sz * (ll) p2.sz + (ll) n1.sz * (ll) n2.sz;
    }/*}}}*/

    ll cnt_nleq(ll v) {/*{{{*/
        if (v >= 0) return ncnt;
        ll res = 0;

        For(i, 0, n1.sz) {
            if (p2.sz == 0) continue;
            if (n1[i] * p2[p2.sz-1] > v) continue;
            int l=0, r=p2.sz-1;

            while(l < r) {
                int m = (l+r)/2;
                if (n1[i] * p2[m] <= v) r = m;
                else l = m+1;
            }

            res += p2.sz - r;
        }

        For(i, 0, n2.sz) {
            if (p1.sz == 0) continue;
            if (n2[i] * p1[p1.sz-1] > v) continue;
            int l=0, r=p1.sz-1;

            while(l < r) {
                int m = (l+r)/2;
                if (n2[i] * p1[m] <= v) r = m;
                else l = m+1;
            }

            res += p1.sz - r;
        }

        return res;
    }/*}}}*/

    ll cnt_zleq(ll v) {/*{{{*/
        if (v >= 0) return zcnt;
        return 0;
    }/*}}}*/

    ll cnt_pleq(ll v) {/*{{{*/
        if (v <= 0) return 0;
        ll res = 0;

        For(i, 0, n1.sz) {
            if (n2.sz == 0) continue;
            if (n1[i] * n2[n2.sz - 1] > v) continue;
            int l=0, r=n2.sz - 1;

            while(l < r) {
                int m = (l+r)/2;
                if (n1[i] * n2[m] <= v) r = m;
                else l = m+1;
            }

            res += n2.sz - l;
        }

        For(i, 0, p1.sz) {
            if (p2.sz == 0) continue;
            if (p1[i] * p2[0] > v) continue;
            int l=0, r=p2.sz - 1;

            while(l < r) {
                int m = (l+r+1)/2;
                if (p1[i] * p2[m] <= v) l = m;
                else r = m-1;
            }

            res += l+1;
        }

        return res;
    }/*}}}*/

    pll cnt(ll v) {
        ll lt=  cnt_nleq(v-1) + cnt_zleq(v-1) + cnt_pleq(v-1);
        ll leq= cnt_nleq(v) +   cnt_zleq(v) +   cnt_pleq(v);
        return { lt, leq };
    }

public:
    long long kthSmallestProduct(vector<int>& _nums1, vector<int>& _nums2, long long k) {
        nums1.assign(all(_nums1)), nums2.assign(all(_nums2));
        init();

        ll l=-1e10, r=1e10;
        while(l < r) {
            ll m = (l+r)/2;
            auto [lt, leq] = cnt(m);

            if (leq < k) l = m + 1;
            else if (lt >= k) r = m - 1;
            else l=m, r=m;
        }

        return l;
    }

    int findKthNumber(int m, int n, int k) {
        vi n1(m), n2(n);
        iota(all(n1), 1), iota(all(n2), 1);
        return kthSmallestProduct(n1, n2, k);
    }
};
