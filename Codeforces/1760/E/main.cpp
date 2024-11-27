#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll n, a[int(2e5) + 9];
ll l0[int(2e5) + 9], r0[int(2e5) + 9], l1[int(2e5) + 9], r1[int(2e5) + 9];

void solve() {
    cin >> n;
    for(int i=0;i<n;i++)
        cin >> a[i];

    ll c0=0, c1=0;
    for(int i=0;i<n;i++) {
        l0[i] = c0;
        l1[i] = c1;

        c0 -= min(a[i] - 1, ll(0));
        c1 += a[i];
    }

    c0=0, c1=0;
    for(int i=n-1;i>=0;i--) {
        r0[i] = c0;
        r1[i] = c1;

        c0 -= min(a[i] - 1, ll(0));
        c1 += a[i];
    }

    ll dres=0;
    for(int i=n-1;i>=0;i--)
        dres += a[i]*r0[i];
    ll res = dres;

    for(int i=0;i<n;i++) {
        ll tmp;
        if (a[i] == 0) {
            tmp = dres - l1[i] + r0[i];
        } else {
            tmp = dres - r0[i] + l1[i];
        }
        res = max(res, tmp);
    }

    cout << res << '\n';
}

int main() {
    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
