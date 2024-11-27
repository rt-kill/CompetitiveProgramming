#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n;
vector<int> x, res;
void solve() {
    cin >> n;

    x.resize(n), res.resize(n);
    for(int i=0; i<n; ++i)
        cin >> x[i];

    deque<pair<int, int>> stak;

    for(int i=0; i<n; ++i) {
        int index = lower_bound(stak.begin(), stak.end(), make_pair(x[i], -1)) - stak.begin() - 1;
        if (index >= 0) res[i] = stak[index].second + 1;

        while(stak.size() && stak.back().first >= x[i])
            stak.pop_back();

        stak.push_back({ x[i], i });
    }

    for(auto v : res) cout << v << ' ';
    cout << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
