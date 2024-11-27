#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#include <ext/pb_ds/detail/standard_policies.hpp>

using namespace std;

typedef __gnu_pbds::tree<
pair<int, int>,
__gnu_pbds::null_type,
greater<pair<int, int>>,
__gnu_pbds::rb_tree_tag,
__gnu_pbds::tree_order_statistics_node_update>
ordered_set;

using ll = long long;

void solve() {
    int n;
    cin >> n;

    int x, y;
    vector<array<int, 4>> vals;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        vals.push_back({x, 1, y, i}); // 1 is open
        vals.push_back({y, 0, x, i}); // 0 is close
    }
    sort(vals.begin(), vals.end(),
            [](auto l, auto r) { return (l[0] < r[0]) || (l[0] == r[0] && l[1] < r[1]) || (l[0] == r[0] && l[1] == r[1] && l[2] > r[2]); } );

    vector<pair<int, int>> intervals(n, {0, 0});
    for (int k=0; k<vals.size(); k++) {
        auto [ x, t, y, i ] = vals[k];

        if (t) intervals[i].first = k+1;
        else intervals[i].second = k+1;
    }

    int mv = vals.size() + 2;
    vector<array<int, 3>> sorted_intervals;
    for (int i = 0; i <intervals.size(); i++) {
        auto [x, y] = intervals[i];
        sorted_intervals.push_back({ x, y, i });
        sorted_intervals.push_back({ y, x, i });
    }
    sort(sorted_intervals.begin(), sorted_intervals.end(),
            [](auto l, auto r) { return (l[0] < r[0]) || (l[0] == r[0] && l[1] > r[1]); } );


    vector<int> contained(n, 0);
    vector<bool> is_open(n, 0);
    ordered_set open; // all open intervals
    for (auto [ x, y, i ] : sorted_intervals) {
        if (!is_open[i]) {
            is_open[i] = 1;
            open.insert({x, i});
        } else {
            swap(x, y); is_open[i] = false;
            open.erase({x, i});

            int loc = open.order_of_key({x, n});
            contained[i] = open.size() - loc;
        }
    }


    vector<int> pfs(mv+1, 0), pfe(mv+1, 0);
    for (auto [x, y] : intervals)
        pfs[x] += 1, pfe[y] += 1;
    for (int i=1; i <= mv; i++)
        pfs[i] += pfs[i-1], pfe[i] += pfe[i-1];

    vector<int> contains;
    for (int i=0; i<intervals.size(); i++) {
        auto [ x, y ] = intervals[i];

        int startl = pfs[x-1];
        int endr = pfe[mv] - pfe[y];

        int res = (n - 1) - startl - endr + contained[i];
        contains.push_back(res);
    }


    for (auto v : contains) cout << v << ' ';
    cout << '\n';
    for (auto v : contained) cout << v << ' ';
    cout << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
