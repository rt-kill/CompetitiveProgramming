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
vi p, s, res;

int dfs(int r, int p=0) {
    if (s[r]) {
        res.pb(r);
        return r;
    }
    s[r] = 1;

    for(auto c : g[r]) {
        if (c == p) continue;

        int t = dfs(c, r);
        if (t == -1) return t;

        if (t > 0) {
            res.pb(r);
            return (r == t) ? -1 : t;
        }
    }

    return 0;
}

void solve() {
    cin >> n >> m;
    g.resize(n+1), s.resize(n+1);
    int a, b;
    for(int i=0; i<m; ++i) {
        cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }

    for (int i=1; i<=n; ++i) {
        if (!s[i]) {
            dfs(i);
        }
        if (res.size()) {
            cout << res.size() << '\n';
            for_each(res.begin(), res.end(), [](auto v){ cout << v << ' '; });
            cout << '\n';
            return;
        }
    };
    cout << "IMPOSSIBLE" << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
