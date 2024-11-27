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

vi res, active, seen;
int dfs(int r) {
    if (res.size()) return 0;
    if (seen[r]) return 0;
    if ( active[r] ) {
        res.pb(r);
        return r;
    }
    active[r] = 1;

    for(auto c : g[r]) {
        int t = dfs(c);

        if (t > 0) {
            res.pb(r);
            return (t == r) ? 0 : t;
        }
    }

    active[r] = 0;
    seen[r] = 1;
    return 0;
}

void solve() {
    cin >> n >> m;
    g.resize(n+1);
    for(int i=0; i<m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
    }

    active.resize(n+1), seen.resize(n+1);
    for(int i=1; i<=n; ++i) {
        if (res.empty())
            dfs(i);
    }

    if (res.empty()) cout << "IMPOSSIBLE" << '\n';
    else {
        cout << res.size() << '\n';
        for_each(res.rbegin(), res.rend(), [](auto v){cout << v << ' ';});
        cout << '\n';
    }
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
