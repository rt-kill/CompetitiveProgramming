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

int n, vq;
vi e, p, pi;
vvi t;


vi ml, mm;
void dfs(int r=1) {
    ml.pb(p[r]);
    mm[r] = ml.sz - 1;

    for(int c : t[r]) {
        dfs(c);
        ml.pb(p[r]);
    }
}


vvi sparse;
vi mp2;

void init_sparse() {
    mp2.rsz(ml.sz + 1);
    int p = 0;
    For(i, 0, ml.sz + 1) {
        mp2[i] = p;
        p += (1 << (p+1)) <= i;
    }

    sparse = vvi(ml.sz, vi(p+1));

    For(i, 0, sparse.sz) sparse[i][0] = ml[i];
    For(j, 1, p+1) {
        For(i, 0, sparse.sz) {
            sparse[i][j] = (i + (1<<(j-1)) < sparse.sz) ?
                min(sparse[i][j-1], sparse[i + (1<<(j-1))][j-1]) : 1;
        }
    }
}

int query_sparse(int l, int r) {
    if (l > r) swap(l, r);
    int dist = r - l + 1;
    int j = mp2[dist];
    return min(sparse[l][j], sparse[r-(1<<j)+1][j]);
}


void solve() {
    cin >> n >> vq;
    e.rsz(n+1), t.rsz(n+1);

    e[1] = 0;
    For(i, 2, n+1) {
        cin >> e[i];
        t[e[i]].pb(i);
    }

    p.rsz(n+1), pi.rsz(n+1);
    queue<int> q({1});
    int count = 1;
    while(q.sz) {
        int u = q.front(); q.pop();

        p[u] = count, pi[count] = u;
        count++;

        for(auto c : t[u]) q.push(c);
    }

    mm.rsz(n+1);
    dfs();
    init_sparse();

    rep(vq) {
        int a, b; cin >> a >> b;
        cout << pi[query_sparse(mm[a], mm[b])] << '\n';
    }
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
