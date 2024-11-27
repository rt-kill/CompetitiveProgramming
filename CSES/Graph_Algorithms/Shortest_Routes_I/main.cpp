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
vector<vector<pair<ll, ll>>> g;

vi seen;
vector<ll> res;
priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;

void solve() {
    cin >> n >> m;
    g.resize(n+1);
    int a, b, c;
    for(int i=0; i<m; ++i) {
        cin >> a >> b >> c;
        g[a].pb({b, c});
    }

    res.resize(n+1), seen.resize(n+1);
    pq.push({0, 1});

    while(pq.size()) {
        auto [ t, u ] = pq.top(); pq.pop();
        if (seen[u]) continue;
        res[u] = t;
        seen[u] = 1;

        for(auto [ v, dt ] : g[u]) {
            pq.push({ t + dt, v });
        }
    }

    for_each(res.begin() + 1, res.end(), [](auto t){cout << t << ' ';});
    cout << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
