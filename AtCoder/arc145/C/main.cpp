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
tcTU > str ts(pair<T, U> p) { return "(" + ts(p.fi) + ", " + ts(p.se) + ")"; }
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

int const M = 998244353;

ll modpow(int a, int b) {
    ll res = 1;
    for(ll e=1, v=a; e<=b; e<<=1, v=v*v%M)
        if (b&e) res = res * v % M;
    return res;
}

vll fmem = {1};
ll fact(int a) {
    while(fmem.sz <= a) fmem.pb(fmem.back() * int(fmem.sz) % M);
    return fmem[a];
}

ll moddiv(int a, int b) {
    ll num=a, den=modpow(b, M-2);
    ll res = num*den%M;
    return res;
}

ll choose(int a, int b) {
    ll num=fact(a), den=fact(a-b)*fact(b)%M;
    ll res = moddiv(num, den);
    return res;
}


int n;
void solve() {
    re(n);

    ll mult = (choose(2*n, n) - choose(2*n, n+1) + M)%M;
    ll ac = modpow(2, n) * fact(n) % M;
    ll res = ac * mult % M;

    ps(res);



    // how many n-lists are there of elements in [1,2n] such that for all i, v[i] ≥ 2*i (1-indexed)
    //  if some list v does not satisfy this, then for some smallest i, v[i] < 2*i
    //  since i is minimal, for all j < i, v[j] ≥ 2*j, and so in particular, 2(i-1) ≤ v[i-1] < v[i] < 2*i
    //      thus v[i] = 2*i-1
    // so it would be the total number of lists (2n, n) minus the number for which this is true

    //  this is true for ∑{1, n}( (2n-(2i-1)) choose (n-i) )
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
