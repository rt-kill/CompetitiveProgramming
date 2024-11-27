#include <bits/stdc++.h>
using namespace std;

using ll = long long;
vector<pair<int, int>> diffs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

void solve() {
    string line;
    vector<string> grid;

    while (true) {
        getline(std::cin, line);
        if (line.empty()) break;
        grid.push_back(line);
    }

    int sr, sc, er, ec;
    for(int r=0; r<grid.size(); r++)
        for(int c=0; c<grid[r].size(); c++) {
            if (grid[r][c] == 'S') {
                sr = r, sc = c;
                grid[r][c] = 'a';
            }
            if (grid[r][c] == 'E') {
                er = r, ec = c;
                grid[r][c] = 'z';
            }
        }


    map<pair<int, int>, int> seen;
    seen[{ sr, sc }] = 0;

    queue<pair<int, int>> q;
    q.push({sr, sc});

    while(!q.empty()) {
        auto [ r, c ] = q.front(); q.pop();
        int d = seen[{r, c}];
        char h = grid[r][c];

        for(auto [dr, dc] : diffs) {
            int nr = r + dr, nc = c + dc;

            if (nr < 0 || nr >= grid.size() || nc < 0 || nc >= grid[0].size()) continue;
            char nh = grid[nr][nc];
            if (nh - h > 1) continue;

            if (seen.count({nr, nc})) continue;
            seen[{nr, nc}] = d+1;

            q.push({nr, nc});
        }
    }

    int res1 = seen[{er, ec}];
    cout << res1 << '\n';



    map<pair<int, int>, int> seen2;
    seen2[{ er, ec }] = 0;

    queue<pair<int, int>> q2;
    q2.push({er, ec});

    while(!q2.empty()) {
        auto [ r, c ] = q2.front(); q2.pop();
        int d = seen2[{r, c}];
        char h = grid[r][c];

        for(auto [dr, dc] : diffs) {
            int nr = r + dr, nc = c + dc;

            if (nr < 0 || nr >= grid.size() || nc < 0 || nc >= grid[0].size()) continue;
            char nh = grid[nr][nc];
            if (h - nh > 1) continue;

            if (seen2.count({nr, nc})) continue;
            seen2[{nr, nc}] = d+1;

            q2.push({nr, nc});
        }
    }

    int res2 = res1;
    for(int r=0; r<grid.size(); r++)
        for(int c=0; c<grid[r].size(); c++) {
            if (grid[r][c] == 'a' && seen2[{r, c}] != 0)
                res2 = min(res2, seen2[{r, c}]);
        }

    cout << res2 << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
