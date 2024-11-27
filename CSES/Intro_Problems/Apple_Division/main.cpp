#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n;
vector<ll> w;

ll bt(int k, ll p1, ll p2) {
    if (k == n) return abs(p1 - p2);
    return min(bt(k+1, p1+w[k], p2), bt(k+1, p1, p2+w[k]));
}

void solve() {
    cin >> n;

    w.resize(n);
    for(int i=0; i<n; i++)
        cin >> w[i];

    ll res = bt(1, w[0], 0);
    cout << res << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
