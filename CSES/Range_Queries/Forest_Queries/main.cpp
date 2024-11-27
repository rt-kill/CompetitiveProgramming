#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, q;
vector<vector<int>> forest;

void solve() {
    cin >> n >> q;

    forest.push_back(vector<int>(n+1, 0));

    char tmp;
    for(int i=1; i<=n; ++i) {
        forest.push_back(vector<int>(n+1, 0));
        for(int j=1; j<=n; ++j) {
            cin >> tmp;
            forest[i][j] = forest[i-1][j] + forest[i][j-1] - forest[i-1][j-1] + (tmp == '*');
        }
    }

    int r1, c1, r2, c2;
    while(q--) {
        cin >> r1 >> c1 >> r2 >> c2;
        int res = forest[max(r1, r2)][max(c1, c2)]
                - forest[min(r1, r2) - 1][max(c1, c2)]
                - forest[max(r1, r2)][min(c1, c2) - 1]
                + forest[min(r1, r2) - 1][min(c1, c2) - 1];
        cout << res << '\n';
    }
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
