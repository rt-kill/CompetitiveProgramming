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

#define INF     INFINITY
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

#define lb lower_bound
#define ub upper_bound

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

#define rev(a, x)   x.rsz(a); each(b, x) _re_(b);
#define rewv(a, x)  _re_(a); rev(a, x);

#define _rdi_(a)    int a; _re_(a)
#define rdi(...)    FOR_EACH(_rdi_, __VA_ARGS__)

#define _rdll_(a)   ll a; _re_(a)
#define rdll(...)   FOR_EACH(_rdll_, __VA_ARGS__)

#define _pr_(a)     cout << a << ' ';
#define pr(...)     FOR_EACH(_pr_, __VA_ARGS__)

#define _ln_(...)       cout << '\n';
#define ln()            cout << '\n';

#define pln(...)        pr(__VA_ARGS__); cout << '\n';

#define _peln_aux_(a)    cout << a << '\n';
#define _peln_(...)      FOR_EACH(_peln_aux_, __VA_ARGS__)
#define peln(...)        _pln_(__VA_ARGS__)

/* IO - Helpers {{{*/
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

int n, m;

vi ntm, mtn; // node to mask, mask to node
vvi adj, madj;
vi adjm;

int igc(int mask) {
    int nm = mask ^ ((1<<n) - 1);

    int res = 1;
    for(int cc=nm; res && cc>0; cc-=(cc&-cc)) {
        int cm = cc&-cc, c = mtn[cm];
        res &= ( (adjm[c] & mask) > 0 );
    }

    return res;
}

vi parrent;
int mic(int r, int s, int mask) { // current node, start node, mask
    if (mask == 0 && ( adjm[r] & ntm[s] )) {
        parrent[s] = r;
        return 1;
    } else if ( mask == 0 ) return 0;

    for(int cc=(mask & adjm[r]); cc > 0; cc -= (cc&-cc)) {
        int cm = ( cc&-cc );
        if (mic(mtn[cm], s, mask^cm)) {
            parrent[mtn[cm]] = r;
            return 1;
        }
    }

    return 0;
}


void solve() {
    re(n, m);

    ntm.rsz(n);
    mtn.rsz((1 << n));

    For(i, 0, n) {
        ntm[i] = (1<<i);
        mtn[ntm[i]] = i;
    }

    adj.assign(n, vi());
    madj.assign(n, vi());
    adjm.assign(n, 0);

    rep(m) {
        rdi(u, v);
        if (u == v) continue;
        --u, --v;

        adj[u].pb(v);
        adj[v].pb(u);

        madj[u].pb(ntm[v]);
        madj[v].pb(ntm[u]);

        adjm[u] |= ntm[v];
        adjm[v] |= ntm[u];
    }

    parrent.rsz(n);
    For(mask, 1, (1<<n)) {
        if (!igc(mask)) continue;

        if (mask == ( mask&-mask )) {
            pln("Yes");

            int cn = __builtin_ctz(mask);
            For(i, 0, n) { pr((i != cn ? cn+1 : abs(cn-1)+1)); }
            ln();

            return;
        }

        int s = __builtin_ctz(mask&-mask);
        if (mic(s, s, mask-(mask&-mask))) {
            pln("Yes");

            For(i, 0, n) {
                if (ntm[i] & mask) { pr(parrent[i]+1); }
                else {
                    int im = adjm[i] & mask;
                    int pn = mtn[im&-im];
                    pr(pn+1);
                }
            }
            ln();

            return;
        }
    }

    pln("No");
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
