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

#define _rdi_(a)    int a; _re_(a)
#define rdi(...)    FOR_EACH(_rdi_, __VA_ARGS__)

#define _rdll_(a)   ll a; _re_(a)
#define rdll(...)   FOR_EACH(_rdll_, __VA_ARGS__)

#define _pr_(a)     cout << a << ' ';
#define pr(...)     FOR_EACH(_pr_, __VA_ARGS__)

#define _ln_(...)       cout << '\n';
#define ln()            cout << '\n';
#define _pln_aux_(a)    cout << a << '\n';
#define _pln_(...)      FOR_EACH(_pln_aux_, __VA_ARGS__)
/* #define _pln_fork_(...) TENTH_PARAM(__VA_ARGS__,_pln_,_pln_,_pln_,_pln_,_pln_,_pln_,_pln_,_pln_,_ln_)(__VA_ARGS__) */
#define pln(...)        _pln_(__VA_ARGS__)

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

int const N = 3e5;
int n, s, t;
vi a, ia, e, sep, ses, parrent;
void solve() {
    re(n);
    a.rsz(n);
    ia.assign(N+1, 0);
    e.assign(N+1, 0);
    sep.assign(N+1, 0);
    ses.assign(N+1, 0);
    parrent.assign(N+1, 0);

    each(x, a) {
        re(x);
        e[x] = 1;
    }

    For(i, 0, n) {
        ia[a[i]] = i+1;
    }

    re(s, t);
    if (s == t) {
        pln(1, s);
        return;
    }

    int sv = a[s-1], tv = a[t-1];
    if (sv == 1 || tv == 1) {
        pln(-1);
        return;
    }

    if (sv == tv) {
        pln(2);
        pr(s, t);
        ln();
        return;
    }

    ia[sv] = s, ia[tv] = t;

    // a bfs would do the trick if we can transition quickly enough
    //  transitions could be done by
    //      find all prime divisors sqrt(n)
    //          there will be less than 7 prime divisors
    //      for each prime divisor, iterate over its multiples
    //          (3e5/p) iterations
    //      at most 6e5 total iterations
    //          by remembering the primes we have used, throughout the entier bfs, we will have at most
    //              N/2 + N/3 + N/5 + ... total iterations
    //              this is less than N*(harm(N)) ~ Nlog(N)

    // So we will have N*sqrt(N) + N*log(N), which should be good enough

    int pe = 0;

    queue<int> q({sv});
    ses[sv] = 1;

    while(q.sz) {
        int cur = q.front(); q.pop();
        if (cur == tv) {
            pe = 1;
            break;
        }
        int ov = cur;

        vi pd;
        for(int i=2; i*i <= cur; ++i) {
            if (cur/i*i == cur) pd.pb(i);
            while(cur/i*i == cur) cur/=i;
        }
        if (cur > 1) pd.pb(cur);

        each(p, pd) {
            if (sep[p]) continue;
            sep[p] = 1;

            For(m, 1, (N/p) + 1) {
                if (!e[p*m]) continue;
                if (ses[p*m]) continue;
                ses[p*m] = 1;

                parrent[p*m] = ov;
                q.push(p*m);
            }
        }
    }

    if (pe) {
        vi res = {tv};

        int cur = tv;
        while(cur != sv) {
            cur = parrent[cur];
            res.pb(cur);
        }

        reverse(all(res));
        pln(res.sz);
        each(re, res) pr(ia[re]);
        ln();
    } else {
        pln(-1);
    }
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
