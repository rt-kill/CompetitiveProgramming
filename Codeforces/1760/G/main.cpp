#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, a, b;
vector<pair<int, int>> tree[int(1e5) + 9];
int acosts[int(1e5) + 9], bcosts[int(1e5) + 9];
bool seen[int(1e5) + 9];

void solve() {
    cin >> n >> a >> b;

    fill(tree + 1, tree + n + 1, vector<pair<int, int>>());
    int u, v, w;
    for(int i=1; i<n; i++) {
        cin >> u >> v >> w;
        tree[u].push_back( { v, w } );
        tree[v].push_back( { u, w } );
    }

    fill(seen+1, seen+n+1, 0);
    deque<pair<int,int>> q = { { b, 0 } };
    int w1, w2;
    while(!q.empty()) {
        tie(u, w1) = q.front(); q.pop_front();
        if (seen[u]) continue;
        seen[u] = 1;

        bcosts[u] = w1; // needed x to get from u to b

        for(auto p : tree[u]) {
            tie(v, w2) = p;
            if (seen[v]) continue;
            q.push_back( { v, (w1 ^ w2) } );
        }
    }

    set<int> btmp;
    for(int i=1;i<=n;i++) {
        if (i == b) continue;
        btmp.insert(bcosts[i]);
    }

    fill(seen+1, seen+n+1, 0);
    q = { { a, 0 } };
    while(!q.empty()) {
        tie(u, w1) = q.front(); q.pop_front();
        if (u == b) continue;
        if (seen[u]) continue;
        seen[u] = 1;

        acosts[u] = w1; // x after going from a to u

        for(auto p : tree[u]) {
            tie(v, w2) = p;
            if (seen[v]) continue;
            q.push_back( { v, (w1 ^ w2) } );
        }
    }

    bool res = 0;
    for(int i=1;i<=n;i++) {
        if (seen[i]) // can get to i from a
            if (btmp.count(acosts[i])) // go a to i, teleport from i to whatever needs acosts[i] to get to b, go to b
                res = 1;
    }

    if (res) cout << "YES" << '\n';
    else cout << "NO" << '\n';
}

int main() {
    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
