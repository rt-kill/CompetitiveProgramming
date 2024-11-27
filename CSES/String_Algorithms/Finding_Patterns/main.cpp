#include <bits/stdc++.h>
using namespace std;

/* Macros {{{ */
/* Basics {{{ */
using ll    = long long;
using ull   = unsigned long long;
using ld    = long double;
using str   = string;

using pi    = pair<int,int>;
using pll   = pair<ll, ll>;
using pld   = pair<ld, ld>;

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

#define arr     array
#define ve      vector
#define pb      push_back
#define rsz(a)  resize(a)
#define mp      make_pair
#define fi      first
#define se      second
#define all(x)  x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define sz      size()

#define For(i, a, b)    for(int i=a; i<b; ++i)
#define Rof(i, a, b)    for(int i = (b)-1; i >= (a); --i)
#define rep(a)          For(_, 0, a)
#define each(a, x)      for(auto &a : x)
#define reach(a, x)     for(auto a = x.rbegin(); a != x.rend(); ++a)

template<typename T, typename U> inline void cmin(T &x, U y) { if(y < x) x = y; }
template<typename T, typename U> inline void cmax(T &x, U y) { if(x < y) x = y; }
/*}}}*/

/* IO {{{ */
// Read
#define _re_(a)     cin >> a;
#define re(...)     FOR_EACH(_re_, __VA_ARGS__)

#define _rdi_(a)    int a; re(a)
#define rdi(...)    FOR_EACH(_rei_, __VA_ARGS__)

#define _rdll_(a)   ll a; re(a)
#define rdll(...)   FOR_EACH(_rell_, __VA_ARGS__)

#define _pr_(a)     cout << a << ' ';
#define pr(...)     FOR_EACH(_pr_, __VA_ARGS__)

#define _pln_(a)    cout << a << '\n';
#define pln(...)    FOR_EACH(_pln_, __VA_ARGS__)

/* IO - Helpers {{{*/
#define TENTH_PARAM(_0,_1,_2,_3,_4,_5,_6,_7,_8,NAME,...) NAME

#define PARENS ()
#define EXPAND(arg)     EXPAND1(EXPAND1(EXPAND1(EXPAND1(arg))))
#define EXPAND1(arg)    EXPAND2(EXPAND2(EXPAND2(EXPAND2(arg))))
#define EXPAND2(arg)    EXPAND3(EXPAND3(EXPAND3(EXPAND3(arg))))
#define EXPAND3(arg)    EXPAND4(EXPAND4(EXPAND4(EXPAND4(arg))))
#define EXPAND4(arg)    arg

#define FOR_EACH(macro, ...)                                    \
  __VA_OPT__(EXPAND(FOR_EACH_HELPER(macro, __VA_ARGS__)))
#define FOR_EACH_HELPER(macro, a1, ...)                         \
  macro(a1)                                                     \
  __VA_OPT__(FOR_EACH_AGAIN PARENS (macro, __VA_ARGS__))
#define FOR_EACH_AGAIN() FOR_EACH_HELPER
/*}}}*//*}}}*//*}}}*/

string s;
int n, k;
ve<str> p;


ve<arr<int, 3>> SA;
void suffix_array() {
    ve<arr<int, 3>> parts(n);
    vi bucket(n);

    For(i, 0, n) {
        parts[i][0] = (s[i] - 'a' + 2);
        parts[i][1] = (i+1 < n) ? (s[i+1] - 'a' + 2) : -1;
        parts[i][2] = i;
    }
    sort(all(parts));


    auto shift = [&parts, &bucket](int am) {
        int r=0;
        int pr=parts[0][0];
        parts[0][0] = r;
        bucket[parts[0][2]] = 0;

        For(i, 1, n) {
            if (parts[i][0] == pr && parts[i][1] == parts[i-1][1]) {
                pr = parts[i][0];
                parts[i][0] = r;
            } else {
                pr = parts[i][0];
                parts[i][0] = ++r;
            }
            bucket[parts[i][2]] = i;
        }

        For(i, 0, n) {
            int cand = parts[i][2] + am;
            parts[i][1] = (cand < n) ? parts[bucket[cand]][0] : -1;
        }

        /* int pb = 0; */
        /* int lb = parts[0][0]; */
        /* int ld = parts[0][1]; */
        /* each(a, parts) { */
        /*     bucket[a[2]] = a[0]; */
        /*     if (a[0] == lb && a[1] == ld) a[0] = pb; */
        /*     else { */
        /*         lb = a[0], ld = a[1]; */
        /*         a[0] = ++pb; */
        /*     } */
        /* } */

        /* each(a, parts) { */
        /*     int cand = a[2] + am; */
        /*     a[1] = (cand < n) ? parts[bucket[cand]][0] : -1; */
        /* } */

        sort(all(parts));
    };

    for(int j=2; j<2*n; j<<=1) {
        shift(j);
        /* each(a, parts) { */
        /*     pr(a[0], a[1], a[2]); */
        /*     pln(); */
        /* } */
        /* pln(); */
    }

    SA.assign(all(parts));
}


void solve() {
    re(s, k);
    s += ('a' - 1);
    n = s.sz;
    p.rsz(k);
    each(a, p) re(a);

    suffix_array();
    /* each(a, SA) { */
    /*     pr(a[2]); */
    /* } */
    /* pln(); */

    auto myComp = [](array<int, 3> &l, str r) {
        str seg = s.substr(l[2], r.sz);
        return seg < r;
    };

    /* For(i, 0, n) { */
    /*     pr(myComp(SA[i], p[0])); */
    /* } */
    /* pln(' '); */

    vi res;
    each(pat, p) {
        auto it = lower_bound(all(SA), pat, myComp);
        str seg = s.substr((*it)[2], pat.sz);
        /* pln(seg); */
        res.pb((seg == pat));
    }

    each(re, res) pln(((re) ? "YES" : "NO"));
}

int main() {
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
