#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, m, a[1001][1001];

vector<pair<int, int>> deltas = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };

bool is_sq(int r, int c) {
    if (r < 0 || r >= n-1 || c < 0 || c >= m-1) return false;

    set<int> tmp = { a[r][c], a[r][c+1], a[r+1][c], a[r+1][c+1] };
    return tmp.count(0) ? tmp.size() == 2 : tmp.size() == 1;
}

int sqco(int r, int c) {
    int res = max(max(a[r][c], a[r][c+1]), max(a[r+1][c], a[r+1][c+1]));
    return res;
}

void zsq(int r, int c) {
    a[r][c] = 0;    a[r][c+1] = 0;
    a[r+1][c] = 0;  a[r+1][c+1] = 0;
}

void solve() {
    cin >> n >> m;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            cin >> a[i][j];

    deque<tuple<int, int, int>> q;
    deque<tuple<int, int, int>> res;
    set<tuple<int, int>> seen;

    for(int i=0;i<n-1;i++)
        for(int j=0;j<m-1;j++)
            if(is_sq(i, j))
                q.push_back( { i, j, a[i][j] } );



    int r, c, co, dr, dc;
    while(!q.empty()) {
        tie(r, c, co) = q.front(); q.pop_front();
        res.push_front( { r, c, co } );
        zsq(r, c);

        for (auto d : deltas) {
            tie(dr, dc) = d;

            if (is_sq(r + dr, c + dc)) {
                if (seen.count( { r + dr, c + dc } )) continue;
                seen.insert( { r + dr, c + dc } );
                q.push_back( { r + dr, c + dc, sqco(r + dr, c + dc) } );
            }
        }
    }

    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if (a[i][j] != 0) {
                cout << -1 << '\n';
                return;
            }

    cout << res.size() << '\n';
    for (auto sq : res ) {
        tie(r, c, co) = sq;
        cout << r+1 << ' ' << c+1 << ' ' << co << '\n';
    }

    // Starting in the top left corner, if there is a different color to our right, we dfs down that path

    // We could do a bfs on the square's
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
