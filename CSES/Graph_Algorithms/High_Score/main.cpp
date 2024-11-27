#include <bits/stdc++.h>
using namespace std;

/* Macros {{{ */
using ll = long long;
using ii = pair<int,int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vll = vector<ll>;
using vvll = vector<vector<ll>>;
#define pb push_back
/* }}} */

int n, m;
vi it;
vll mr;
vector<array<ll, 3>> e;

vvi g;

vi memory;
bool can_reach(int r) {
    if (r == n) return 1;
    if (memory[r] >= 0) return memory[r];
    memory[r] = 0;

    bool res = 0;
    for(auto c : g[r])
        if (can_reach(c)) res = 1;
    memory[r] = res;
    return res;
}

void solve() {
    cin >> n >> m;

    e.resize(m), g.resize(n+1);
    for(int i=0; i<m; ++i) {
        cin >> e[i][0] >> e[i][1] >> e[i][2];
        e[i][2] = -e[i][2];
        g[e[i][0]].pb(e[i][1]);
    }

    mr = vll(n+1), it = vi(n+1);
    mr[1] = 0; it[1] = 1;

    for(int i=1; i<n; ++i) {
        for(auto [a, b, c] : e) {
            if (it[a]) {
                if (!it[b] || (it[b] && (mr[b] > mr[a] + c))) {
                    mr[b] = mr[a] + c;
                    it[b] = 1;
                }
            }
        }
    }

    vector<int> nc;
    for(auto [a, b, c] : e)
        if (it[a])
            if (mr[b] > mr[a] + c)
                nc.push_back(b);

    memory = vi(n+1, -1);
    for(auto v : nc) {
        if (can_reach(v)) {
            cout << -1 << '\n';
            return;
        }
    }

    cout << -mr[n] << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
