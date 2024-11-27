#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n;
vector<ll> x;
void solve() {
    cin >> n;
    x.resize(n);
    for(int i=0; i<n; i++) cin >> x[i];

    ll res = 0, cm = 0;

    for_each(x.begin(), x.end(), [&res, &cm](auto v) {
        res += max(0ll, cm - v);
        cm = max(cm, v);
    });

    cout << res << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
