#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, t;
vector<ll> x;
void solve() {
    cin >> n >> t;

    x.resize(n);
    for(int i=0; i<n; ++i)
        cin >> x[i];

    vector<array<ll, 3>> sum_pairs;
    for(int i=0; i<n; ++i)
        for(int j=i+1; j<n; ++j)
            sum_pairs.push_back({x[i] + x[j], i, j});

    sort(sum_pairs.begin(), sum_pairs.end());

    for(int i=0; i<sum_pairs.size(); ++i) {
        auto [ v1, a, b ] = sum_pairs[i];

        array<ll, 3> req = {(t - v1), b+1, -1};
        int index = lower_bound(sum_pairs.begin(), sum_pairs.end(), req) - sum_pairs.begin();

        if (index < sum_pairs.size() && (sum_pairs[index][0] == (t - v1))) {
            auto [ v2, c, d ] = sum_pairs[index];
            cout << a+1 << ' ' << b+1 << ' ' << c+1 << ' ' << d+1 << '\n';
            return;
        }
    }

    cout << "IMPOSSIBLE" << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
