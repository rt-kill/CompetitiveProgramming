#include <bits/stdc++.h>
using namespace std;

/* Macros {{{ */
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ii = pair<int,int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvll = vector<vll>;
using vvii = vector<vii>;

#define arr array
#define ve vector
#define pb push_back
#define rsz(a) resize(a)
#define mp make_pair
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define sz size()

#define For(i, a, b) for(int i=a; i<b; ++i)
#define Rof(i, a, b) for(int i = (b)-1; i >= (a); --i)
#define rep(a) For(_, 0, a)
#define each(a, x) for (auto &a : x)
#define reach(a, x) for (auto a = x.rbegin(); a != x.rend(); ++a)
/* }}} */

int n, q;
vi v;
vvi tmp_t, t;
vi e;

void dfs0(int r=1, int p=0) {
    e[r] = p, t[p].pb(r);
    each(c, tmp_t[r]) if (c != p)
        dfs0(c, r);
}

vi perm, iperm, nex;
void dfs1(int r=1) {
    iperm.pb(r); perm[r] = iperm.sz - 1;
    each(c, t[r]) dfs1(c);
    nex[r] = iperm.sz - 1;
}


vll bit, val;
void update_bit(int u, ll k) {
    ll diff = k - val[u];
    val[u] += diff;
    for(int i=u; i<bit.sz; i += (i&-i))
        bit[i] += diff;
}

ll aux_query(int a) {
    ll res = 0;
    for(int i=a; i>0; i-=(i&-i))
        res += bit[i];
    return res;
}

ll query(int l, int r) {
    return aux_query(r) - aux_query(l-1);
}

void init_bit() {
    bit.rsz(n+1), val.rsz(n+1);
    For(i, 1, n+1) update_bit(perm[i], v[i]);
}


void solve() {
    cin >> n >> q;
    v.rsz(n+1);
    For(i, 1, n+1) cin >> v[i];

    t.rsz(n+1), tmp_t.rsz(n+1), e.rsz(n+1);
    rep(n-1) {
        int a, b; cin >> a >> b;
        tmp_t[a].pb(b);
        tmp_t[b].pb(a);
    }
    dfs0();

    perm.rsz(n+1), nex.rsz(n+1);
    iperm.pb(0), perm[0] = 0;
    dfs1();
    init_bit();

    vll res;
    rep(q) {
        int t, s, x; cin >> t >> s;
        if (t == 1) {
            cin >> x;
            update_bit(perm[s], x);
        } else {
            ll tmp = query(perm[s], nex[s]);
            res.pb(tmp);
        }
    }

    each(re, res) cout << re << '\n';
}

int main() {
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
