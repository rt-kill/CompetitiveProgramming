#include <bits/stdc++.h>
using namespace std;

int t, n, m;
int t1, t2;

pair<int, int> edges[int(2e5) + 9];
vector<int> graph[int(2e5) + 9];

set<pair<int, int>> seen_back_nodes;
vector<pair<int, int>> back_nodes;
bool seen[int(2e5) + 9];

void dfs(int u, int p = -1) {
    seen[u] = true;
    for (int v : graph[u]) {
        if (v == p)
            continue;
        else if (seen[v]) {
            if (0 == seen_back_nodes.count(make_pair(min(u, v), max(u, v)))) {
                back_nodes.push_back(make_pair(min(u, v), max(u, v)));
                seen_back_nodes.insert(make_pair(min(u, v), max(u, v)));
            }
        }
        else
            dfs(v, u);
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) graph[i] = vector<int>();

    for (int i = 0; i < m; i++) {
        cin >> t1 >> t2; --t1; --t2;
        edges[i] = make_pair(t1, t2);

        graph[t1].push_back(t2);
        graph[t2].push_back(t1);
    }

    seen_back_nodes.clear();
    back_nodes = vector<pair<int, int>>();
    fill(seen, seen + n, false);
    dfs(0);

    if (back_nodes.size() == 3) {
        set<int> count;
        for (auto& p : back_nodes) {
            count.insert(p.first);
            count.insert(p.second);
        }

        if (count.size() == 3) {
            for (int i = 0; i < back_nodes.size(); i++) {
                pair<int, int> p = back_nodes[i];

                if (graph[p.first].size() > 2) {
                    int u = p.first;
                    for (int v : graph[u]) {
                        if (0 == count.count(v)) {
                            back_nodes[i] = make_pair(min(u, v), max(u, v));
                            break;
                        }
                    }
                    break;
                }

                else if (graph[p.second].size() > 2) {
                    int u = p.second;
                    for (int v : graph[u]) {
                        if (0 == count.count(v)) {
                            back_nodes[i] = make_pair(min(u, v), max(u, v));
                            break;
                        }
                    }
                    break;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        bool col = false;
        for (auto& p : back_nodes) {
            if (min(edges[i].first, edges[i].second) == p.first && max(edges[i].first, edges[i].second) == p.second)
                col = true;
        }
        cout << int(col);
    }
    cout << '\n';
}

int main() {
    cin >> t;
    for (int i = 0; i < t; i++)
        solve();

    return 0;
}
