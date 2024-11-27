#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, x, y;
vector<pair<int, int>> intervals;
vector<array<int, 3>> sorted_intervals;
vector<bool> contains, contained, is_open;

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        intervals.push_back({x, y});
        sorted_intervals.push_back({x, y, i});
        sorted_intervals.push_back({y, x, i});
    }
    sort(sorted_intervals.begin(), sorted_intervals.end(),
            [](auto l, auto r) { return (l[0] < r[0]) || (l[0] == r[0] && l[1] > r[1]); } );

    contains.resize(n);
    contained.resize(n);
    is_open.resize(n);

    set<pair<int, int>, greater<pair<int, int>>> open; // all open intervals
    set<pair<int, int>, greater<pair<int, int>>> open_pending; // all open intervals that are yet to contain an interval

    for (auto [ x, y, i ] : sorted_intervals) {
        if (!is_open[i]) {
            is_open[i] = 1;
            open.insert({x, i});
            open_pending.insert({x, i});
        } else {
            swap(x, y); is_open[i] = false;
            open.erase({x, i});
            open_pending.erase({x, i});

            vector<pair<int, int>> tmp;
            auto it = open_pending.lower_bound({x, n});
            while (it != open_pending.end()) {
                tmp.push_back(*it);
                int j = (*it).second;
                contains[j] = 1;
                it++;
            }

            for (auto t : tmp)
                open_pending.erase(t);


            it = open.lower_bound({x, n});
            if (it != open.end())
                contained[i] = 1;
        }
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
