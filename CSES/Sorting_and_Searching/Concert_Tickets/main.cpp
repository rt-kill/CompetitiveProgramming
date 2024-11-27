#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, m;
vector<int> h, t;
set<int, greater<int>> p;
map<int, int> counts; // because multisets are slow af for repeated values

vector<bool> bought, lbnb;

void solve() {
    cin >> n >> m;

    h.resize(n), t.resize(m);
    for(int i=0; i<n; ++i) {
        cin >> h[i];
        p.insert(h[i]);
        ++counts[h[i]];
    }
    for(int i=0; i<m; ++i) cin >> t[i];


    for(auto u : t) {
        auto it = p.lower_bound(u);

        if (it == p.end()) cout << -1 << '\n';
        else {
            int v = *it;
            cout << v << '\n';

            --counts[v];
            if (counts[v] == 0) p.erase(v);
        }
    }
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
