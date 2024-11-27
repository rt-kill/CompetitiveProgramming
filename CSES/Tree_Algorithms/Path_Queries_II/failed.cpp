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

vi seg;
void init_seg() {
    seg.rsz(2*(n+1));
    For(i, 1, n+1) seg[perm[i] + n+1] = v[i];
    Rof(i, 1, n+1) seg[i] = max(seg[2*i], seg[2*i+1]);
}

void update_seg(int r, int v) {
    seg[perm[r] + n+1] = v;
    for(int i=(perm[r]>>1); i>0; i>>=1)
        seg[i] = max(seg[2*i], seg[2*i+1]);
}

int query_seg(int l, int r) {
    int res = 0;

    l+=n+1, r+=n+1;

    while(l <= r) {
        if (l&1) res = max(res, seg[l++]);
        if (!(r&1)) res = max(res, seg[r--]);
        l>>=1, r>>=1;
    }

    return res;
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
