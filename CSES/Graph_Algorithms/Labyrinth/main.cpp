#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, m;
vector<vector<char>> graph;
vector<vector<pair<pair<int, int>, char>>> bef;

vector<pair<pair<int, int>, char>> diffs = { {{1, 0}, 'D'}, {{0, 1}, 'R'}, {{-1, 0}, 'U'}, {{0, -1}, 'L'} };
void solve() {
    cin >> n >> m;
    graph.resize(n), bef.resize(n);
    for_each(graph.begin(), graph.end(), [](auto &v){v.resize(m);});
    for_each(bef.begin(), bef.end(), [](auto &v){v.resize(m);});

    int ar, ac;
    for(int i=0;i<n;++i)for(int j=0;j<m;++j) {
        cin >> graph[i][j];
        if (graph[i][j] == 'A')
            ar = i, ac = j;
    }

    queue<pair<int, int>> q;
    q.push({ ar, ac });

    while(q.size()) {
        auto [ r, c ] = q.front();
        q.pop();


        if (graph[r][c] == 'B') {
            cout << "YES" << '\n';
            vector<char> res;
            int cr = r, cc = c;
            while(cr != ar || cc != ac) {
                auto [ diff, rep ] = bef[cr][cc];
                auto [ dr, dc ] = diff;

                res.push_back(rep);
                cr += dr, cc += dc;
            }

            cout << res.size() << '\n';
            for_each(res.rbegin(), res.rend(), [](auto v) { cout << v; });
            cout << '\n';
            return;
        }

        if (graph[r][c] == '#') continue;
        graph[r][c] = '#';

        for(auto [ diff, rep ] : diffs) {
            auto [ dr, dc ] = diff;
            int nr = r + dr, nc = c + dc;

            if (nr < 0 || n <= nr || nc < 0 || m <= nc) continue;
            if (graph[nr][nc] == '#') continue;

            q.push({nr, nc});
            bef[nr][nc] = { { -dr, -dc }, rep };
        }
    }

    cout << "NO" << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
