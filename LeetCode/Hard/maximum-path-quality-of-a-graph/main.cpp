#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    vector<int> vals;

    vector<vector<pair<int, int>>> adj;
    vector<int> min_dist_to_root;

    vector<int> seen;
    int cur;
    int best;

    void rec(int u, int t) {
        if (t < min_dist_to_root[u]) return;

        cur += seen[u]++ == 0 ? vals[u] : 0;
        if (u == 0) best = max(best, cur);

        for(auto [v, w] : adj[u]) {
            if (w > t) continue;
            rec(v, t-w);
        }

        cur -= --seen[u] == 0 ? vals[u] : 0;
    }

public:
    int maximalPathQuality(vector<int>& values, vector<vector<int>>& edges, int maxTime) {
        int n = values.size();
        vals.assign(values.begin(), values.end());

        adj.assign(n, vector<pair<int, int>>());
        for(auto e : edges) {
            int u = e[0], v = e[1], w = e[2];
            adj[u].push_back({ v, w }), adj[v].push_back({ u, w });
        }

        min_dist_to_root.assign(n, -1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({ 0, 0 });

        while(pq.size()) {
            auto [ d, u ] = pq.top(); pq.pop();
            if (min_dist_to_root[u] >= 0) continue;
            min_dist_to_root[u] = d;
            for(auto [v, w] : adj[u]) pq.push({ d+w, v });
        }

        seen.assign(n, 0);

        cur = 0;
        best = 0;
        rec(0, maxTime);

        return best;
    }
};
