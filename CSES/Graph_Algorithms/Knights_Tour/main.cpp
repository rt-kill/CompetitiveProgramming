#include <bits/stdc++.h>
using namespace std;

/* Macros {{{ */
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ii = pair<int,int>;
using vi = vector<int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvii = vector<vii>;

#define arr array
#define ve vector
#define pb push_back
#define rsz(a) resize(a)
#define mp make_pair
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define sz size()

#define For(i, a, b) for(int i=a; i<b; ++i)
#define Rof(i, a, b) for(int i = (b)-1; i >= (a); --i)
#define rep(a) For(_, 0, a)
#define each(a, x) for (auto &a : x)
#define reach(a, x) for (auto a = x.rbegin(); a != x.rend(); ++a)
/* }}} */

int r, c;
vii diffs = { {1, 2}, {2, 1}, {1, -2}, {2, -1}, {-1, 2}, {-2, 1}, {-1, -2}, {-2, -1} };

int board[8][8] = {};
void print_board() {
    For(r, 0, 8) {
        For(c, 0, 8)
            cout << board[r][c] << ' ';
        cout << '\n';
    }
}

int opps[8][8] = {};
void pop_opps() {
    For(r, 0, 8) For(c, 0, 8) {
        for(auto [dr, dc] : diffs) {
            int nr = r + dr, nc = c + dc;
            if (nr < 0 || 8 <= nr || nc < 0 || 8 <= nc) continue;
            if (board[nr][nc] > 0) continue;
            ++opps[r][c];
        }
    }
}

bool dfs(int u=r, int v=c, int count=2) {
    if (count == 65) return 1;

    ve<pair<int, ii>> candidates;
    for(auto [dr, dc] : diffs) {
        int nr = u + dr, nc = v + dc;
        if (nr < 0 || 8 <= nr || nc < 0 || 8 <= nc) continue;
        if (board[nr][nc] > 0) continue;

        --opps[nr][nc]; // we have just set (r, c) to a value
        candidates.pb({opps[nr][nc], {nr, nc}});
    }

    // This is the hueristic we are using
    // always prefer moves that have less options
    sort(all(candidates));
    for(auto [ _, loc ] : candidates) {
        auto [nr, nc] = loc;

        board[nr][nc] = count;

        bool tmp = dfs(nr, nc, count + 1);
        if (tmp) return 1;

        board[nr][nc] = 0;
    }

    for(auto [ _, loc ] : candidates) {
        auto [nr, nc] = loc;
        ++opps[nr][nc];
    }

    return 0;
}

void solve() {
    cin >> c >> r;
    r--, c--;

    board[r][c] = 1;
    pop_opps();
    dfs();
    print_board();
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
    // you should actually read the stuff at the bottom
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
