#include <bits/stdc++.h>
using namespace std;

/* Macros {{{ */
using ll = long long;
using ii = pair<int,int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
#define pb push_back
/* }}} */


int n, m;
vector<vector<char>> g;

queue<ii> mp;
vvi mm; // the min number of moves for a monster to reach this square

queue<pair<ii, int>> q;
vvi s;
vector<vector<ii>> from;
vector<vector<char>> dir;

vector<ii> diffs = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

vector<char> res;

char get_dir(int dr, int dc) {
    if (dr == -1) return 'U';
    if (dr == 1) return 'D';
    if (dc == -1) return 'L';
    if (dc == 1) return 'R';
    return '-';
}

void solve() {
    cin >> n >> m;
    g = vector<vector<char>>(n, vector<char>(m));
    from = vector<vector<ii>>(n, vector<ii>(m, {-1, -1}));
    dir = vector<vector<char>>(n, vector<char>(m, '-'));
    mm = vvi(n, vi(m, INT_MAX));
    s = vvi(n, vi(m, 0));
    for(int i=0; i<n; ++i) {
        for(int j=0; j<m; ++j) {
            cin >> g[i][j];
            if ( g[i][j] == 'M' ) {
                mp.push({i, j});
                mm[i][j] = 0;
            }
            if ( g[i][j] == 'A' )
            {
                q.push({{i, j}, 0});
                s[i][j] = 1;

                if (i == 0 || i == n-1 || j == 0 || j == m-1) {
                    cout << "YES" << '\n' << 0 << '\n';
                    return;
                }
            }
        }
    }

    while(mp.size()) {
        auto [ r, c ] = mp.front(); mp.pop();
        for(auto [dr, dc] : diffs) {
            int nr = r + dr, nc = c + dc;
            if (nr < 0 || n <= nr || nc < 0 || m <= nc) continue;
            if (g[nr][nc] == '#') continue;
            if ( mm[nr][nc] > mm[r][c] + 1 ) {
                mm[nr][nc] = mm[r][c] + 1;
                mp.push({nr, nc});
            }
        }
    }

    while(q.size()) {
        auto [ l, v ] = q.front();
        auto [ r, c ] = l;
        q.pop();

        for(auto [ dr, dc ] : diffs) {
            int nr = r + dr, nc = c + dc;
            if (nr < 0 || n <= nr || nc < 0 || m <= nc) continue;
            if (g[nr][nc] == '#') continue;
            if (mm[nr][nc] <= v+1) continue;
            if (s[nr][nc]) continue;
            s[nr][nc] = 1;
            from[nr][nc] = {r, c};
            dir[nr][nc] = get_dir(dr, dc); // direction that goes from r, c to nr, nc
            q.push({{nr, nc}, v+1});
        }
    }

    for(int r : {0, n-1}) {
        for(int c = 0; c<m; ++c) {
            if (g[r][c] == '.' && from[r][c].first != -1) {
                int cr = r, cc = c;
                while(cr != -1 && cc != -1) {
                    res.pb(dir[cr][cc]);
                    auto [ tr, tc ] = from[cr][cc];
                    cr = tr, cc = tc;
                }
                res.pop_back();
                cout << "YES" << '\n';
                cout << res.size() << '\n';
                for_each(res.rbegin(), res.rend(), [](auto v){cout << v;});
                cout << '\n';
                return;
            }
        }
    }

    for(int c : {0, m-1}) {
        for(int r=0; r<n; ++r) {
            if (g[r][c] == '.' && from[r][c].first != -1) {
                int cr = r, cc = c;
                while(cr != -1 && cc != -1) {
                    res.pb(dir[cr][cc]);
                    auto [ tr, tc ] = from[cr][cc];
                    cr = tr, cc = tc;
                }
                res.pop_back();
                cout << "YES" << '\n';
                cout << res.size() << '\n';
                for_each(res.rbegin(), res.rend(), [](auto v){cout << v;});
                cout << '\n';
                return;
            }
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
