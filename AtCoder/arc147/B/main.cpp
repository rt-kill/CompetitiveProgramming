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
tcTU > void re(pair<T, U> &p) { re(p.f, p.s); }                                         // pairs
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
vi p;
void solve() {
    re(n);
    rv(n, p);

    // with hop swaps, we can swap elements that are a distance of d>2 apart at a cost of
    //  f(0) = 1
    //  f(1) = 1
    //  f(2) = 3
    //  f(3) = 3
    //  f(4) = 5
    //  f(5) = 5
    //  f(k) = k + 1 - (k&1)

    // would it be optimal to coutinuously swap x with the first element before it larger than it?
    //  not really: [ 5, 4, 3, 2, 1 ]
    // what about swapping x with the value in his position?
    //  no: [ 3, 4, 5, 2, 1 ]
    // what about swapping x with the value in his position, and only counting swaps we make an odd number of times
    //  probably not: [ 3, 4, 2, 5, 1 ] depending on the order, if we do 1 first, then 2, etc...

    // we can do O(n³)
    // suppose a < b
    //  would we ever want to swap a and b?
    //  suppose some optimal solution at some point swaps two elements that are in order
    //      eventually a will need to get back in front of b
    //      the elements should not be directly swapped again, as then we could have just not swapped them in the first place
    //          COROLLARY: no swap should happen between two elements twice
    //              this already gets us to (n choose 2) which is in the bounds of this problem
    //      so the only option would be to move a over b for some c
    //          this chould have been done with two in order adj swaps
    //      so there must exist an optimal solution where no swap breaks order
    //  suppose some optimal solution at some point moves a smaller element over a larger element
    //      at some point they will need to be swapped back
    //          an adj swap between them may as well be done immediately
    //              or, this could have been avoided by doing 2 adj swaps instead of a hop swap
    //          a hop swap is the same -- unnessesary if we just immediately swapped them
    //          an over swap may have merit:
    //              [ 4, 2, 3, 1 ] -> [ 1, 2, 3, 4 ] with (2, 1), (4, 2), (4, 1)
    //                                               or   (2, 4), (4, 1), (2, 1)
    //              [ 5, 2, 3, 4, 1 ] with (3, 1), (5, 1), (5, 3) or (5, 3), (5, 1), (3, 1)
    //              [ 7, 2, 3, 4, 5, 6, 1 ] with (5, 1), (3, 1), (7, 1), (7, 3), (7, 5)
    //              [ 7, 3, 2, 4, 5, 6, 1 ] with
    //          to give some context, lets use a < b < c < d, and originally there is some order where d < b < c < a
    //          the first hop swap is between b and a
    //          then through some sequence of moves, a and d get swapped
    //          then we swap d and b

    // if we only can use adj swaps, then the optimal soution is just to put the elements in place one at a time
    //      that is, get 1 to the front, then 2, etc...
    //  this is because any operation that uses the smallest value should only ever move it left
    //      and all moves preformed before moving 1 can be preformed just as well after (completly) moving 1
    // the key difference is that hop swaps don't preserve the relative order of the rest of the elements
    //      so the operations preformed before a hop swap can not be preformed the same after one

    // instead of doing two adj swaps, we should always do a hop swap and then an adj swap
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
