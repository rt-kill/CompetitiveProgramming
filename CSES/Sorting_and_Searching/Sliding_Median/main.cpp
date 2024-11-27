#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll n, k, x[200000];
void solve() {
    // find the median value for each window
    //  can be done with a min and max heap

    vector<ll> sols;

    cin >> n >> k;
    for(int i=0; i<n; i++) cin >> x[i];

    multiset<ll, greater<int>> large;
    multiset<ll, less<int>> small;

    for (int i=0; i<k; i++) small.insert(x[i]);
    while(large.size() + 1 < small.size()) {
        ll tmp = *small.begin();
        small.erase(small.find(tmp));
        large.insert(tmp);
    }

    ll smaller = *large.begin();
    ll larger = *small.begin();
    sols.push_back(larger*(k&1) + min(smaller, larger)*((k + 1)&1));

    for (int i=0; i<n-k; i++) {
        ll rm = x[i], add = x[i+k];
        ll m = *small.begin();

        if (rm < m) large.erase(large.find(rm));
        else small.erase(small.find(rm));

        if (add < m) large.insert(add);
        else small.insert(add);

        while(large.size() > small.size()) {
            ll tmp = *large.begin();
            large.erase(large.find(tmp));
            small.insert(tmp);
        }

        while(large.size() + 1 < small.size()) {
            ll tmp = *small.begin();
            small.erase(small.find(tmp));
            large.insert(tmp);
        }

        smaller = *large.begin();
        larger = *small.begin();
        sols.push_back(larger*(k&1) + min(smaller, larger)*((k + 1)&1));
    }

    for (auto res : sols) cout << res << ' ';
    cout << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
