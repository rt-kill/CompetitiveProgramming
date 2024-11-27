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

int n, m;

vii edges;
vvi graph;
vi d;

void init() {
    cin >> n >> m;

    graph.rsz(n), d.rsz(n);
    rep(m) {
        int a, b; cin >> a >> b;
        a--, b--;
        edges.pb({b, 1});
        graph[a].pb(edges.size()-1);
        edges.pb({a, 0});
        graph[b].pb(edges.size()-1);
    }
}

bool bfs() {
    fill(all(d), n);
    d[0] = 0;
    queue<int> q({0});

    while(q.size()) {
        int u = q.front(); q.pop();
        for(int i : graph[u]) {
            auto [ v, cap ] = edges[i];

            if (d[v] > d[u] + 1 && cap > 0) {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }

    return (d[n-1] != n);
}

bool dfs(int u=0, int flow=1) {
    if (u == n-1 || flow == 0) return flow;
    for (int i : graph[u]) {
        auto &[ v, cap ] = edges[i];
        auto &[ _, ocap ] = edges[i^1];

        if (d[v] == d[u] + 1) {
            int f = dfs(v, min(cap, flow));
            if ( f > 0 ) {
                cap -= f;
                ocap += f;
                return f;
            }
        }
    }

    return 0;
}

vi head;
bool bfs2() {
    fill(all(head), n), fill(all(d), n);
    head[0] = 0;
    d[0] = 0;

    queue<int> q({0});
    while(q.size()) {
        int u = q.front(); q.pop();

        for(int i : graph[u]) {
            if (i & 1) continue;
            auto [ v, cap ] = edges[i];

            if (d[v] > d[u] + 1 && cap == 0) {
                d[v] = d[u] + 1;
                head[v] = i;
                q.push(v);
            }
        }
    }

    return (d[n-1] != n);
}

vvi res;
void build_res() {
    while(bfs()) while(dfs());

    head.rsz(n);
    while(bfs2()) {
        res.pb(vector<int>());

        int cur = n-1;
        res.back().pb(cur+1);

        while(cur != 0) {
            auto &[u, ocap] = edges[ head[cur] ^ 1 ];
            auto &[_, cap] = edges[ head[cur] ];

            ++cap, --ocap;

            res.back().pb(u+1);
            cur = u;
        }
    }
}

void solve() {
    init();
    build_res();
    cout << res.sz << '\n';
    each(p, res) {
        cout << p.sz << '\n';
        reach(it, p) cout << *it << ' ';
        cout << '\n';
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
