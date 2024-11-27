#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, m;
vector<vector<int>> adj;
vector<int> rev;
vector<bool> seen;

void solve() {
    cin >> n >> m;
    adj.resize(n+1), rev.resize(n+1);
    for(int i=0; i<m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }


    seen.resize(n+1);

    queue<pair<int, int>> q;
    q.push({1, 0});
    seen[1] = 1;

    while(q.size()) {
        auto [ r, c ] = q.front();
        q.pop();

        for(auto child : adj[r]) {
            if (seen[child]) continue;
            seen[child] = 1;

            rev[child] = r;
            q.push({child, c+1});
        }
    }

    vector<int> res;
    auto iv = n;
    res.push_back(iv);
    while(rev[iv] != 0) {
        iv = rev[iv];
        res.push_back(iv);
    }

    if (1 == res.back()) {
        cout << res.size() << '\n';
        for_each(res.rbegin(), res.rend(), [](auto v) {cout << v << ' ';});
        cout << '\n';
    } else {
        cout << "IMPOSSIBLE" << '\n';
    }
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
