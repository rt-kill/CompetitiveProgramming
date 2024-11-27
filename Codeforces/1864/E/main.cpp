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

ll const Mod = 998244353;

ll modpow(ll a, ll b) {
    ll res = 1;
    for(ll e=1, p=a; e<=b; e<<=1, p=p*p%Mod)
        if (b&e) res = res*p%Mod;
    return res;
}

ll moddiv(ll a, ll b) {
    ll num=a, den=modpow(b, Mod-2), res=num*den%Mod;
    return res;
}


struct node {
    ll subtree_size;
    array<ll, 2> next; // index of children
};

ll const MAXLEN = 5e6;
node tree[MAXLEN];
ll siz;

void tree_init() {
    tree[0].subtree_size = 0;
    tree[0].next = { -1, -1 };
    siz=1;
}

void tree_extend(ll v) {
    ll cur = 0;
    bitset<32> bs(v);

    for(ll i=31; i>=0; --i) {
        ll d = bs[i];

        if (tree[cur].next[d] == -1) {
            tree[siz].subtree_size = 0;
            tree[siz].next = { -1, -1 };
            tree[cur].next[d] = siz;
            ++siz;
        }

        cur = tree[cur].next[d];
    }

    ++tree[cur].subtree_size;
}

ll pop_subtree_siz(ll v=0) {
    if (v < 0) return 0;
    tree[v].subtree_size += pop_subtree_siz(tree[v].next[0]) + pop_subtree_siz(tree[v].next[1]);
    return tree[v].subtree_size;
}

// XXX: we might have problems on leafs
ll get_sum(ll r=0, ll b=0) {
    if (r == -1) return 0;

    if (tree[r].next[0] == -1 && tree[r].next[1] == -1) {
        ll cnt = tree[r].subtree_size;
        return cnt*cnt%Mod;
    }

    ll lc = tree[r].next[0], rc = tree[r].next[1];
    ll lv = lc != -1 ? tree[lc].subtree_size : 0;
    ll rv = rc != -1 ? tree[rc].subtree_size : 0;

    // if I pick two numbers from different subtrees, for half, alice can solve on turn 1, and the other half bob can solve on turn 2
    ll res = ll(3)*lv*rv % Mod;
    // ps(lv, rv, 3*lv*rv, rv*rv, get_sum(rc, 1) + rv*rv);


    // otherwise I pick them from the same set.
    //  if the leading bit is 0, this changes nothing
    res = (res + get_sum(lc, 0)) % Mod;
    //  if the leading bit is 1, we resume from bob and add 1 turn
    res = (res + get_sum(rc, 1) + (rv*rv)%Mod)%Mod;

    return res;
}

ll n;
vi s;

void solve() {
    re(n), rv(n, s);

    tree_init();
    each(v, s) tree_extend(v);
    pop_subtree_siz();

    ll num = get_sum(), den = n*n%Mod, res = moddiv(num, den)%Mod;
    ps(res);

    // we will need to prove that the game always terminates, and know how many turns it takes in different situations
    // let A, B be any two integers


    // if A is 0, the game always takes 1 turn
    // otherwise if B is 0, the game always takes 2 turns
    //  using this, we can count and then remove all zeros

    // So assume no numbers are 0

    // if B has a 2's bit larger than A, the game takes 1 turn
    //      log2(A) < log2(B)
    // so assume this is not the case

    // in any other case, alice will pass:

    // whenever Alice skips, Bob knows that log2(A) ≥ log2(B)
    //  if log2(B) > log2(A), the game takes 2 turns
    //  otherwise, we resume the game starting at bob this time, and both players may ignore their leading bit


    // it follows that we can solve the game for (a,b) in log time, and only consider pairs with the same leading bit



    // remove zeros
    // divide our numbers into equivalence classes where all numbers have the same leading bit
    //  we know the answer for numbers chosen from differnet equivalence classes
    //  then recurse on the solution for those equivalence classes


    // we can solve this with a tree
    //  the leaves of the tree represent our numbers (and the count of them),



    // Let X be the random variable of the number of turns a game takes
    // Ev[X] = n⁻² * ∑ X(i, j)
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    /* cout << fixed << setprecision(6); */
    int t = 1;
    cin >> t;
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
