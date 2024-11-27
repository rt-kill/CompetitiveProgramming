#include <bits/stdc++.h>
using namespace std;

/* Macros {{{ */
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ii = pair<int,int>;
using vi = vector<int>;
using vii = vector<ii>;
using vvi = vector<vi>;
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

int n, m, k, s, t;

ve<ii> e;
vvi g;

vi dists;

void init_residual_graph() {
    g.rsz(n + m + 2); // start at n+m, end at n+m+1
    dists.rsz(n + m + 2);

    For(i, 0, n) {
        e.pb({i, 1});
        g[s].pb(e.size() - 1);
        e.pb({s, 0}); // even though this edge should never be used
        g[i].pb(e.size() - 1);
    }

    For(i, n, n+m) {
        e.pb({t, 1});
        g[i].pb(e.size() - 1);
        e.pb({i, 0}); // even though this edge should never be used
        g[t].pb(e.size() - 1);
    }

    For(i, 0, k) {
        int a, b;
        cin >> a >> b;
        a--, b--; b += n;

        e.pb({ b, 1 });
        g[a].pb(e.size() - 1);
        e.pb({ a, 0 });
        g[b].pb(e.size() - 1);
    }
}

bool bfs() {
    fill(all(dists), n+m+2);
    dists[s] = 0;

    queue<int> q({s});
    while(q.sz) {
        int u = q.front(); q.pop();

        for(int ei : g[u]) {
            auto [v, cap] = e[ei];

            if (dists[v] > dists[u] + 1 && cap > 0) {
                dists[v] = dists[u] + 1;
                q.push(v);
            }
        }
    }

    return ( dists[t] != n+m+2 );
}

int dfs(int u=s, int flow=1) {
    if (u == t || flow == 0) return flow;

    for(auto ei : g[u]) {
        auto [v, cap] = e[ei];

        if (dists[v] == dists[u] + 1) {
            int f = dfs(v, min(flow, cap));
            if ( f > 0 ) {
                e[ei].se -= f;
                e[ei ^ 1].se += f;
                return f;
            }
        }
    }

    return 0;
}

/* set<int> r; */
void print_res() {
    vii res;

    int c = 0;
    while(bfs()) {
        while(dfs());
        /* cout << c++ << '\n'; */
    }

    /* For(i, 0, n+m+2) if (dists[i] < n+m+2) r.insert(i); */
    for(int ei = 0; ei < e.sz; ei += 2) {
        auto [ u, _ ] = e[ei ^ 1]; // get head of edge
        auto [ v, c1 ] = e[ei]; // tail of edge and current cap

        if (u == s || v == t) continue; // ignore when we start at s or end at t
        if (c1 == 0) res.pb({u+1, v+1-n});
    }

    cout << res.sz << '\n';
    for(auto [a, b] : res) cout << a << ' ' << b << '\n';
}

void solve() {
    cin >> n >> m >> k;
    s=n+m, t=n+m+1;

    init_residual_graph();
    print_res();
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
