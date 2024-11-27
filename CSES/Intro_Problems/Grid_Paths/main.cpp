#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<pair<int, int>> diffs = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
map<char, vector<pair<int, int>>> diffs_map = { { 'D', { {-1, 0} } }, { 'U', { {1, 0} } }, { 'L', { {0, -1} } }, { 'R', { {0, 1} } }, { '?', diffs } };
vector<vector<pair<int, int>>> dirs;

bool visited[7][7] = {};
string input;

int rec(int r=6, int c=0, int i=0) {
    if (r < 0 || r >= 7 || c < 0 || c >= 7) return 0;
    if (visited[r][c]) return 0;
    if (r == 0 && c == 0) return (i == 48);

    // if we bump into a wall
    if (r-1 >= 0 && r+1 < 7 && !visited[r-1][c] && !visited[r+1][c])
        if ((c-1 < 0 || visited[r][c-1]) && (c+1 >= 7 || visited[r][c+1])) return 0;
    if (c-1 >= 0 && c+1 < 7 && !visited[r][c-1] && !visited[r][c+1])
        if ((r-1 < 0 || visited[r-1][c]) && (r+1 >= 7 || visited[r+1][c])) return 0;

    visited[r][c] = 1;
    int res = 0;
    for (auto [ dr, dc ] : dirs[i])
        res += rec(r + dr, c + dc, i+1);
    visited[r][c] = 0;

    return res;
}

void solve() {
    cin >> input;
    for(int i=0; i < 48; i++)
        dirs.push_back(diffs_map[input[i]]);

    int res = rec();
    cout << res << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
