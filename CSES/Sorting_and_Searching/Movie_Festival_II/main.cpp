#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int k, n;
vector<pair<int, int>> endings;

void solve() {
    cin >> n >> k;
    pair<int, int> movie;

    for (int i=0; i<n; i++) {
        cin >> movie.second >> movie.first;
        endings.push_back(movie);
    }

    sort(endings.begin(), endings.end(),
        [](auto l, auto r) { return (l.first < r.first) || (l.first == r.first && l.second < r.second); }
    );

    int i=0, res=0;
    multiset<int, greater<int>> watchers;

    while(i < endings.size()) {
        auto [ stop, start ] = endings[i];

        auto it = watchers.lower_bound(start);
        if (it != watchers.end()) {
            watchers.erase(watchers.find(*it));
            watchers.insert(stop);
            res += 1;
        } else if (watchers.size() < k) {
            watchers.insert(stop);
            res += 1;
        }

        i++;
    }

    cout << res << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
