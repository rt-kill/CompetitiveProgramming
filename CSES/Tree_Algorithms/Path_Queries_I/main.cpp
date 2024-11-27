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

vi depth;
void init_depth() {
    depth.rsz(n+1);
    queue<ii> q({{1, 1}});
    while(q.size()) {
        auto [r, d] = q.front(); q.pop();
        depth[r] = d;
        each(c, t[r]) q.push({c, d+1});
    }
}

vvi sparse_parrent;
void init_sp() {
    int p = 0;
    while(1 << p <= n+1) ++p;
    sparse_parrent.assign(n+1, vi(p));
    For(i, 1, n+1) sparse_parrent[i][0] = e[i];
    For(j, 1, p) For(i, 1, n+1)
        sparse_parrent[i][j] = sparse_parrent[sparse_parrent[i][j-1]][j-1];
}


// sends a node r at depth d to its descendants of depth d + (d&-d)
vvi spd;
void init_spd() {
    spd.rsz(n+1);
    For(i, 1, n+1) {
        int d = depth[i];
        for(int j = 0; j < __builtin_ctz(d&-d); ++j) {
            spd[sparse_parrent[i][j]].pb(i);
        }
    }
}


vll tbit, val;
void aux_update_tbit(int r, ll diff) {
    tbit[r] += diff;
    each(sc, spd[r])
        aux_update_tbit(sc, diff);
}

void update_tbit(int r, ll nv) {
    ll diff = nv - val[r];
    val[r] += diff;
    aux_update_tbit(r, diff);
}

void init_tbit() {
    init_spd();
    tbit.rsz(n+1), val.rsz(n+1);
    For(i, 1, n+1) update_tbit(i, v[i]);
}

ll query_tbit(int a) {
    int d = depth[a];
    ll res = 0;
    while(d > 0) {
        res += tbit[a];
        a = sparse_parrent[a][__builtin_ctz(d&-d)];
        d -= d&-d;
    }

    return res;
}


void solve() {
    // We create a data structure
    // nodes at depth d store the sum of all ancestors within 2^i gens
    //  where 2^i is the largest pow of 2 that divides d

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

    init_depth();
    init_sp();
    init_tbit();

    vll res;
    rep(q) {
        int t, s, x; cin >> t >> s;

        if (t == 1) {
            cin >> x;
            update_tbit(s, x);
        } else {
            ll re = query_tbit(s);
            res.pb(re);
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
