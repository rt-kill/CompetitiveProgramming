#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ii = pair<int,int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
#define pb push_back

int n, m;
vvi graph;
vi seen, team;
bool pos = 1;

void solve() {
    cin >> n >> m;
    graph.resize(n+1), seen.resize(n+1), team.resize(n+1);

    int a, b;
    for(int i=0; i<m; ++i) {
        cin >> a >> b;
        graph[a].pb(b);
        graph[b].pb(a);
    }

    for(int i=1; i<=n; ++i) {
        if (seen[i]) continue;

        queue<ii> q;
        q.push({ i, 0 });

        while(q.size()) {
            auto [ c, d ] = q.front(); q.pop();

            if (seen[c]) {
                pos = pos && ((d&1)+1 == team[c]);
                continue;
            }

            seen[c] = 1;
            team[c] = (d&1)+1;

            for(int f : graph[c])
                q.push({ f, d+1 });
        }
    }

    if(pos) for(auto v : vi(team.begin() + 1, team.end()))
            cout << v << ' ';
    else cout << "IMPOSSIBLE";
    cout << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
