#include <bits/stdc++.h>
using namespace std;

/* Macros {{{ */
// A lot of this is from some of Benq's submissions [https://codeforces.com/profile/Benq]
//  Ugly af to the eyes, but with vim fold its barable
//  Hopefully c++20 concepts can make all this stuff must cleaner

/* Basics {{{ */
using ll    = long long;
using ld    = long double;
using str   = string;

using pi    = pair<int,int>;
using pll   = pair<ll, ll>;
using pld   = pair<ld, ld>;
#define mp  make_pair
#define fi  first
#define se  second

#define arr array
#define ve  vector
using vi    = vector<int>;
using vll   = vector<ll>;
using vld   = vector<ld>;

using vpi   = vector<pi>;
using vpll  = vector<pll>;
using vpld  = vector<pld>;

using vvi   = vector<vi>;
using vvll  = vector<vll>;
using vvld  = vector<vld>;

using vvpi  = vector<vpi>;
using vvpll = vector<vpll>;
using vvpld = vector<vpld>;

#define pb      push_back
#define lb      lower_bound
#define ub      upper_bound
#define sz      size()
#define rsz(a)  resize(a)
#define all(x)  x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()

#define For(i, a, b)    for(int i=a; i<b; ++i)
#define Rof(i, a, b)    for(int i = (b)-1; i >= (a); --i)
#define rep(a)          For(_, 0, a)
#define each(a, x)      for(auto &a : x)
#define reach(a, x)     for(auto a = x.rbegin(); a != x.rend(); ++a)

template<typename T, typename U> inline void cmin(T &x, U y) { if(y < x) x = y; }
template<typename T, typename U> inline void cmax(T &x, U y) { if(x < y) x = y; }
/*}}}*/

/* IO {{{ */

/* Template Macros {{{ */
#define tcT template <class T
#define tcTU tcT, class U
#define tcTUU tcT, class... U
/*}}}*/

inline namespace Helpers {/*{{{*/
tcT, class = void > struct is_iterable : false_type {};
tcT > struct is_iterable<T, void_t<decltype(begin(declval<T>())), decltype(end(declval<T>()))>> : true_type {};
tcT > constexpr bool is_iterable_v = is_iterable<T>::value;

tcT, class = void > struct is_readable : false_type {};
tcT > struct is_readable<T, typename std::enable_if_t<is_same_v<decltype(cin >> declval<T &>()), istream &>>> : true_type {};
tcT > constexpr bool is_readable_v = is_readable<T>::value;

tcT, class = void > struct is_printable : false_type {};
tcT > struct is_printable<T, typename std::enable_if_t<is_same_v<decltype(cout << declval<T>()), ostream &>>> : true_type {};
tcT > constexpr bool is_printable_v = is_printable<T>::value;
}/*}}}*/

inline namespace Input {/*{{{*/
tcT > constexpr bool needs_input_v = !is_readable_v<T> && is_iterable_v<T>;
tcTUU > void re(T &t, U &...u);
tcTU > void re(pair<T, U> &p);  // pairs

// re: read{{{
tcT > typename enable_if<is_readable_v<T>, void>::type re(T &x) { cin >> x; }           // default
tcT > typename enable_if<needs_input_v<T>, void>::type re(T &i);                        // vectors, arrays, etc...
tcTU > void re(pair<T, U> &p) { re(p.fi, p.se); }                                         // pairs
tcT > typename enable_if<needs_input_v<T>, void>::type re(T &i) { each(x, i) re(x); }
tcTUU > void re(T &t, U &...u) { re(t); re(u...); }                                     // read multiple}}}

// rv: resize and read vectors{{{
void rv(size_t) {}
tcTUU > void rv(size_t N, ve<T> &t, U &...u);
template <class... U> void rv(size_t, size_t N2, U &...u);
tcTUU > void rv(size_t N, ve<T> &t, U &...u) {
	t.rsz(N);
	re(t);
	rv(N, u...);
}
template <class... U> void rv(size_t, size_t N2, U &...u) { rv(N2, u...); }/*}}}*/

// dumb shortcuts to read in ints{{{
void decrement() {}  // subtract one from each
tcTUU > void decrement(T &t, U &...u) {
	--t;
	decrement(u...);
}
#define ints(...)                                                              \
	int __VA_ARGS__;                                                           \
	re(__VA_ARGS__);
#define int1(...)                                                              \
	ints(__VA_ARGS__);                                                         \
	decrement(__VA_ARGS__);/*}}}*/
}/*}}}*/

inline namespace ToString {/*{{{*/
tcT > constexpr bool needs_output_v = !is_printable_v<T> && is_iterable_v<T>;

// ts: string representation to print
tcT > typename enable_if<is_printable_v<T>, str>::type ts(T v) {
	stringstream ss;
	ss << fixed << setprecision(15) << v;
	return ss.str();
}  // default
tcT > str bit_vec(T t) {  // bit vector to string
	str res = "{";
	For(i, 0, t.sz) res += ts(t[i]);
	res += "}";
	return res;
}
str ts(ve<bool> v) { return bit_vec(v); }
template <size_t SZ> str ts(bitset<SZ> b) { return bit_vec(b); }  // bit vector
tcTU > str ts(pair<T, U> p);                                      // pairs
tcT > typename enable_if<needs_output_v<T>, str>::type
      ts(T v);  // vectors, arrays
tcTU > str ts(pair<T, U> p) { return "(" + ts(p.f) + ", " + ts(p.s) + ")"; }
tcT > typename enable_if<is_iterable_v<T>, str>::type ts_sep(T v, str sep) {
	// convert container to string w/ separator sep
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

// for nested DS
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
}  // namespace ToString}}}

inline namespace Output {/*{{{*/
template <class T> void pr_sep(ostream &os, str, const T &t) { os << ts(t); }
template <class T, class... U>
void pr_sep(ostream &os, str sep, const T &t, const U &...u) {
	pr_sep(os, sep, t);
	os << sep;
	pr_sep(os, sep, u...);
}
// print w/ no spaces
template <class... T> void pr(const T &...t) { pr_sep(cout, "", t...); }
// print w/ spaces, end with newline
void ps() { cout << "\n"; }
template <class... T> void ps(const T &...t) {
	pr_sep(cout, " ", t...);
	ps();
}
// debug to cerr
template <class... T> void dbg_out(const T &...t) {
	pr_sep(cerr, " | ", t...);
	cerr << endl;
}
void loc_info(int line, str names) {
	cerr << "Line(" << line << ") -> [" << names << "]: ";
}
template <int lev, class T> void dbgl_out(const T &t) {
	cerr << "\n\n" << ts_sep(ts_lev<lev>(t), "\n") << "\n" << endl;
}
#ifdef LOCAL
#define dbg(...) loc_info(__LINE__, #__VA_ARGS__), dbg_out(__VA_ARGS__)
#define dbgl(lev, x) loc_info(__LINE__, #x), dbgl_out<lev>(x)
#else  // don't actually submit with this
#define dbg(...)
#define dbgl(lev, x)
#endif

// https://stackoverflow.com/questions/47980498/accurate-c-c-clock-on-a-multi-core-processor-with-auto-overclock?noredirect=1&lq=1
const auto beg = std::chrono::high_resolution_clock::now();
void dbg_time() {
	auto duration = chrono::duration<double>(
	    std::chrono::high_resolution_clock::now() - beg);
	dbg(duration.count());
}
}  // namespace Output}}}/*}}}*//*}}}*/

int n;
vi l, r;
vpi bnds;
vi x;
vll xadj;
void solve() {
    re(n);
    x.rsz(n);
    rv(n, bnds);

    sort(all(bnds));
    for(auto [lv, rv] : bnds) l.pb(lv), r.pb(rv);

    sort(all(bnds));
    sort(all(l));
    sort(all(r));

    For(i, 0, (n+1)/2 + 1) {
        int ind = lower_bound(all(l), r[i]) - l.begin(); // index of first person that will always be after person i
        if (n-ind >= (n+1)/2) x[i] = r[i];
        else x[i] = -1; // person i can be on the median point
    }

    Rof(i, (n+1)/2+1, n) {
        int ind = r.rend() - lower_bound(rall(r), l[i]) - 1; // index of last person that will always be before person i
        if (ind+1 >= (n+1)/2) x[i] = l[i];
        else x[i] = -1;
    }

    For(i, 0, n) ps(x[i]);

    vi tmp;
    For(i, 0, n) if (x[i] >= 0) tmp.pb(x[i]);
    sort(all(x));
    int med = (x[(x.sz-1)/2] + x[x.sz/2])/2;
    For(i, 0, n) if (x[i] < 0) x[i] = med;

    xadj.assign(all(x));
    For(i, 1, n) xadj[i] += xadj[i-1];

    ll res=0;
    For(i, 0, n-1) {
        ll afs = xadj[n-1] - xadj[i];
        ll mult = (n-1-i);
        res += afs - mult*x[i];
    }

    ps(res);


    // sort by Li
    //  person on left should stand either as far to the right if R0 < L1
    //  or at least as far as L1 (update L0 to be L1)
    //      in the latter, both of these people would like to stand as far right etc...

    // note that for a list xi, ∑|C-xi| is minimal when C is the median of xi
    //  in general, for some i, xi would like to be closer to the side that has more people
    //  this is seen by the fact that a single step in a direction increases the sum by 1 for every person you go away from and decreases it by 1 for every person you go towards
    // if there are the same number of people to the left and right, it does not matter where you stand between them
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    /* cout << fixed << setprecision(6); */
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

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
