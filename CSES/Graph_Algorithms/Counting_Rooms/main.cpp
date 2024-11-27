#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, m;
vector<vector<char>> graph;

vector<pair<int, int>> diffs = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

void dfs(int r, int c) {
    if (r < 0 || n <= r || c < 0 || m <= c) return;
    if (graph[r][c] == '#') return;

    graph[r][c] = '#';
    for(auto [ dr, dc ] : diffs)
        dfs(r + dr, c + dc);
}

void solve() {
    cin >> n >> m;
    for(int r=0;r<n;++r) {
        graph.push_back(vector<char>(m));
        for(int c=0;c<m;++c)
            cin >> graph[r][c];
    }

    int res = 0;
    for(int r=0;r<n;++r)
        for(int c=0;c<m;++c) {
            res += (graph[r][c] == '.');
            dfs(r, c);
        }

    cout << res << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
