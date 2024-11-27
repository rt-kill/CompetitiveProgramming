#include <bits/stdc++.h>
using namespace std;

/* Macros {{{ */
using ll = long long;
using ii = pair<int,int>;
using lli = pair<ll,int>;
using vi = vector<int>;
using vll = vector<ll>;
using vvi = vector<vector<int>>;
using vvii = vector<vector<ii>>;
#define pb push_back
/* }}} */

int n, m, k;
vvii g;
priority_queue<lli, vector<lli>, greater<lli>> pq;
vi counts;
vll res;
void solve() {
    cin >> n >> m >> k;
    g.resize(n+1);
    for(int i=0; i<m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].pb({b, c});
    }

    counts.resize(n+1);
    pq.push({0, 1});

    while(pq.size()) {
        auto [ c, u ] = pq.top(); pq.pop();

        if(counts[u] >= k) continue;
        ++counts[u];

        if(u == n) res.pb(c);

        for(auto [ v, w ] : g[u])
            pq.push({ c + w, v });
    }

    for(auto r : res) cout << r << ' ';
    cout << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
