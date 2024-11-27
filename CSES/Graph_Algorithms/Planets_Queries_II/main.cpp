#include <bits/stdc++.h>
using namespace std;

/* Macros {{{ */
using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using vi = vector<int>;
using vii = vector<ii>;
using vvi = vector<vi>;

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

#define FOR(i, a, b) for(int i=a; i<b; ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for(int i = ( b )-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define rep(a) F0R(_, a)
#define each(a, x) for (auto &a : x)
/* }}} */

// how can we tell if a can reach b?
// union find can tell us if they are in the same component
// We can build a new graph on the strongly connected components (aka cycles and vertices that are not in cycles)

// I can build a map form a node to the first node in a cycle it can reach
// If first node in cycle can reach value, go to this node first
// We can binary search on nodes it can reach that are not in cycles

// if a and b point to differnet cycles, return -1
//  log(n)
// find distance from a and b to first node in their cycle
//  from here it is trivial

int const MN = 2e5, MQ = 2e5;

int n, q;

int t[MN+1];

vi ch;
int active[MN+1] = {}, seen[MN+1] = {};
void dfs1(int r) {
    if (active[r]) {
        ch.pb(r);
        return;
    };

    if (seen[r]) return;
    seen[r] = 1;

    active[r] = 1;
    dfs1(t[r]);
    active[r] = 0;
}


int uf[MN+1], siz[MN+1];
int gp(int a) {
    if (a != uf[a])
        uf[a] = gp(uf[a]);
    return uf[a];
}

void uion(int a, int b) {
    int l = gp(a), r=gp(b);
    if (l==r) return;
    if (siz[l] < siz[r]) {
        uf[l] = r;
        siz[r] += siz[l];
    } else {
        uf[r] = l;
        siz[l] += siz[r];
    }
}


int cdist[MN+1];
int dfs2(int r) {
    if(cdist[r] < 0)
        cdist[r] = dfs2(t[r]) + 1;
    return cdist[r];
}


int sparse[MN+1][18];
void sparse_init() {
    FOR(i, 1, n+1) sparse[i][0] = t[i];
    FOR(e, 1, 18) {
        FOR(i, 1, n+1) {
            sparse[i][e] = sparse[sparse[i][e-1]][e-1];
        }
    }
}

int query_sparse(int x, int k) {
    for(int i=1, e=0; i<=k; i<<=1, ++e)
        if (i & k) x = sparse[x][e];
    return x;
}


int res[MQ], cr=0;
void query(int a, int b) {
    int d1 = cdist[a], d2 = cdist[b], d3 = 0;

    // if b is in a cycle, and is not the head
    // the distance from b to the head is cdist[b]
    // the distance from the head to b is
    int rep = gp(b);
    if (cdist[b] != 0 && siz[rep] > 1) {
        d3 = siz[rep] - cdist[b]; // dist from rep to b
    }

    int diff = d1 - d2;
    int c1 = (diff >= 0) ? query_sparse(a, diff) : 0;

    int c2 = query_sparse(a, d1 + d3);

    if (b == c1) res[cr++] = diff;
    else if (b == c2) res[cr++] = d1 + d3;
    else res[cr++] = -1;
}


void solve() {
    cin >> n >> q;
    FOR(i, 1, n+1) cin >> t[i];
    FOR(i, 1, n+1) dfs1(i);

    sparse_init();

    iota(uf+1, uf+n+1, 1);
    fill(siz+1, siz+n+1, 1);

    fill(cdist+1, cdist+n+1, -1);
    each(u, ch) {
        cdist[u] = 0;
        for(int i=t[u]; i != u; i=t[i])
            uion(i, t[i]);
    }
    FOR(i, 1, n+1) dfs2(i);

    rep(q) {
        int a, b;
        cin >> a >> b;
        query(a, b);
    }

    F0R(i, q) cout << res[i] << '\n';
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
