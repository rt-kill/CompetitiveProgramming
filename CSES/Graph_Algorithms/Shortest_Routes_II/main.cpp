#include <bits/stdc++.h>
using namespace std;

/* Macros {{{ */
using ll = long long;
using ii = pair<int,int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
#define pb push_back
/* }}} */

int n, m, q;
vector<vector<ll>> mr;

void solve() {
    cin >> n >> m >> q;

    mr = vector<vector<ll>>(n+1, vector<ll>(n+1, -1));
    for(int i=1; i<=n; ++i) mr[i][i] = 0;

    int a, b, c;
    for(int i=0; i<m; ++i) {
        cin >> a >> b >> c;
        if (mr[a][b] == -1)
            mr[a][b] = c;
        mr[a][b] = min(mr[a][b], (ll) c);
        mr[b][a] = mr[a][b];
    }

    for(int k=1; k<=n; ++k)
        for(int i=1; i<=n; ++i)
            for(int j=1; j<=n; ++j) {
                if (mr[i][k] >= 0 && mr[k][j] >= 0)
                    mr[i][j] = mr[i][j] >= 0 ? min(mr[i][j], mr[i][k] + mr[k][j]) : mr[i][k] + mr[k][j];
                mr[j][i] = mr[i][j];
            }

    while(q--) {
        cin >> a >> b;
        cout << mr[a][b] << '\n';
    }
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
