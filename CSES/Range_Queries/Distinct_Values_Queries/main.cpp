#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, q, k;
vector<int> x, res;

vector<pair<int, int>> queries, sorted_queries;

void solve() {
    cin >> n >> q;
    k = sqrt(n);

    x = vector<int>(n);
    map<int, int> compression;
    int val = 0, tmp;
    for(int i=0; i<n; i++) {
        cin >> tmp;
        if (!compression.count(tmp))
            compression[tmp] = val++;
        x[i] = compression[tmp];
    }

    int a, b;
    while(q--) {
        cin >> a >> b;
        queries.push_back({--a, --b});
    }

    sorted_queries = vector<pair<int, int>>(queries.begin(), queries.end());
    sort(sorted_queries.begin(), sorted_queries.end(),
        [](auto f, auto s) {
            auto [a1, b1] = f; auto [a2, b2] = s;
            return ((a1/k) < (a2/k) || ((a1/k == a2/k) && b1 < b2));
        }
    );


    vector<int> cur_counts = vector<int>(val, 0);
    int l=0, r=-1, cur_res = 0;
    for(auto [nl, nr] : sorted_queries) {
        while(r < nr) {
            r++;
            cur_res += (cur_counts[x[r]] == 0);
            cur_counts[x[r]]++;
        }

        while(r > nr) {
            cur_counts[x[r]]--;
            cur_res -= (cur_counts[x[r]] == 0);
            r--;
        }

        while (l < nl) {
            cur_counts[x[l]]--;
            cur_res -= (cur_counts[x[l]] == 0);
            l++;
        }

        while (l > nl) {
            l--;
            cur_res += (cur_counts[x[l]] == 0);
            cur_counts[x[l]]++;
        }

        res.push_back(cur_res);
    }

    map<pair<int, int>, int> res_map;
    for(int i=0; i<sorted_queries.size(); i++)
        res_map[sorted_queries[i]] = res[i];

    for(auto query : queries)
        cout << res_map[query] << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
