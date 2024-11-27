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

    ll ss = accumulate(small.begin(), small.end(), 0l, plus{});
    ll sl = accumulate(large.begin(), large.end(), 0l, plus{});

    ll off = *small.begin()*(k&1);
    sols.push_back(ss - sl - off);

    for (int i=k; i<n; i++) {
        ll rm = x[i-k], add = x[i];
        ll m = *small.begin();

        if (add < m) {
            large.insert(add);
            sl += add;
        }
        else {
            small.insert(add);
            ss += add;
        }

        if (rm < m) {
            large.erase(large.find(rm));
            sl -= rm;
        }
        else {
            small.erase(small.find(rm));
            ss -= rm;
        }

        while(large.size() > small.size()) {
            ll tmp = *large.begin();
            large.erase(large.find(tmp));
            sl -= tmp;
            small.insert(tmp);
            ss += tmp;
        }

        while(large.size() + 1 < small.size()) {
            ll tmp = *small.begin();
            small.erase(small.find(tmp));
            ss -= tmp;
            large.insert(tmp);
            sl += tmp;
        }

        ll off = *small.begin()*(k&1);
        sols.push_back(ss - sl - off);
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
