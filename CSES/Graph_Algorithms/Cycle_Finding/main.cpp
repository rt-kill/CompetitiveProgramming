#include <bits/stdc++.h>
using namespace std;

/* Macros {{{ */
using ll = long long;
using ii = pair<int,int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
#define pb push_back
/* }}} */

int n, m;
vvi g;

vi t;
vector<ll> mr;
vector<array<ll, 3>> edges;


vi active, res, seen;
int dfs(int r) {
    if (res.size()) return 0;

    if (seen[r]) return 0;

    if (active[r]) {
        res.pb(r);
        return r;
    }
    active[r] = 1;


    for(auto u : g[r]) {
        int v = dfs(u);
        if (v > 0) {
            res.pb(r);
            return (v == r) ? 0 : v;
        }

        /* if (v == -1) return -1; */
    }

    seen[r] = 1;

    active[r] = 0;
    return 0;
}


void solve() {
    cin >> n >> m;
    for(int i=1; i<=n; ++i) {
        edges.pb({ 0, i, 0 });
    }

    for(int i=0; i<m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        edges.pb({a, b, c});
    }


    mr.resize(n+1), t.resize(n+1);
    mr[0] = 0, t[0] = 1;

    for(int i=1; i<=n; ++i) {
        for(auto [ a, b, c ] : edges) {
            if (t[a]) {
                if (!t[b] || (t[b] && mr[b] > mr[a] + c))
                    mr[b] = mr[a] + c;
                t[b] = 1;
            }
        }
    }

    g = vvi(n+1);
    for(int i=1; i<=n; ++i) {
        for(auto [ a, b, c ] : edges) {
            if (t[a]) {
                if (mr[b] > mr[a] + c) {
                    mr[b] = mr[a] + c;
                    g[a].pb(b);
                }
            }
        }
    }

    active.resize(n+1), seen.resize(n+1);
    for(int i=1; i<=n; ++i) {
        dfs(i);
    }

    if (res.size()) {
        cout << "YES" << '\n';
        for_each(res.rbegin(), res.rend(), [](auto v){cout << v << ' ';});
        cout << '\n';
    }
    else {
        cout << "NO" << '\n';
    }

}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
