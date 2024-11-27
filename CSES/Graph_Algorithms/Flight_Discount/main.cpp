#include <bits/stdc++.h>
using namespace std;

/* Macros {{{ */
using ll = long long;
using ii = pair<int,int>;
using lli = pair<ll,int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vvii = vector<vector<pair<int, int>>>;
#define pb push_back
/* }}} */

int n, m;
vi seen;
vvii g;
priority_queue<lli, vector<lli>, greater<lli>> pq;

void solve() {
    cin >> n >> m;
    g.resize(2*n + 1);

    for(int i=0; i<m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].pb({b, c});
        g[a].pb({b+n, c/2});
        g[a+n].pb({b+n, c});
    }

    pq.push({0, 1});
    seen.resize(2*n+1);

    while(pq.size()) {
        auto [ p, u ] = pq.top(); pq.pop();

        if (seen[u]) continue;
        seen[u] = 1;

        if (u == 2*n) {
            cout << p << '\n';
            return;
        }

        for(auto [v, c] : g[u]) {
            if (seen[v]) continue;
            pq.push({p + ll(c), v});
        }
    }
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
