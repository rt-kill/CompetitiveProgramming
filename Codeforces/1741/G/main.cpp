#include <bits/stdc++.h>
using namespace std;

int t, n, m, f, h[int(1e4) + 9], k, p[10];
vector<int> adj[int(1e4) + 9];
bool masks[int(1e4) + 9][70];
int memory[int(1e4) + 9][70];

void setup() {
    cin >> n >> m;
    fill(adj, adj + n + 1, vector<int>());

    int u, v;
    for (int i = 1; i <= m; i++) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    cin >> f;
    for (int i = 1; i <= f; i++)
        cin >> h[i];

    cin >> k;
    for (int i = 1; i <= k; i++)
        cin >> p[i];

    for (int i = 1; i <= n; i++)
        for (int perm = 0; perm < (1<<k); perm++)
            masks[i][perm] = false;

    for (int i = 1; i <= f; i++)
        for (int perm = 0; perm < (1<<k); perm++)
            memory[i][perm] = -1;
}

void bfs() {
    deque<pair<int, int>> q = { make_pair(1, 0) };
    set<int> seen;

    int cur, mask;
    while (!q.empty()) {
        tie(cur, mask) = q.front(); q.pop_front();

        for (int i = 1; i <= k; i++)
            if (cur == h[p[i]])
                mask += (1<<(i-1));

        masks[cur][mask] = true;

        if (seen.count(cur)) continue;
        seen.insert(cur);

        for (int neighbor : adj[cur])
            q.push_back(make_pair(neighbor, mask));
    }
}

bool dp(int i, int perm) {
    if (perm == 0) return true;
    if (i > f) return false;

    if (memory[i][perm] == -1) {
        for (int j = 1; j <= k; j++)
            if (p[j] == i) {
                memory[i][perm] = dp(i+1, perm);
                return memory[i][perm];
            }

        memory[i][perm] = 0;
        for (int tperm = 0; tperm < (1<<k); tperm++) {
            if (masks[h[i]][tperm]) {
                int subperm = tperm & perm;
                if (dp(i+1, perm - subperm)) {
                    memory[i][perm] = true;
                }
            }

        }
    }

    return memory[i][perm];
}


void solve() {
    setup();
    bfs();

    for (int i = 1; i <= n; i++) {
        cout << "IIIIII " << i << '\n';
        for (int perm = 0; perm < (1<<k); perm++) {
            if (masks[i][perm]) {
                cout << bitset<8>(perm) << '\n';
            }
        }
        cout << "------" << '\n';
    }

    int res = 0;
    for (int perm = 1; perm < (1<<k); perm++) {
        int count = 0;
        for (int i = 1; i <= k; i++)
            if (perm & (1<<(i-1)))
                count += 1;

        if (count > res && dp(1, perm))
            res = count;
    }

    cout << res << '\n';
}

int main() {
    cin >> t;
    for (int i = 0; i < t; i++)
        solve();
    return 0;
}
