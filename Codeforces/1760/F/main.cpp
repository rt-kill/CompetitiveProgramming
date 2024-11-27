#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll n, c, d, a[int(2e5) + 9];
ll ps[int(2e5) + 9];

void solve() {
    cin >> n >> c >> d;
    for(int i=1;i<=n;i++)
        cin >> a[i];

    sort(a+1, a+n+1, greater<int>());
    if (a[1] * d < c) {
        cout << "Impossible" << '\n';
        return;
    }

    ps[0] = 0;
    for (int i=1;i<=n;i++)
        ps[i] = ps[i-1] + a[i];

    if (ps[min(n, d)] >= c) {
        cout << "Infinity" << '\n';
        return;
    }


    // if k=i, we only every want to do quests from a[1] to a[k]
    //  after d days, we get ps[k]*(d/k) + ps[d%k] coins

    ll k = 1;
    while((ps[min(k, n)]*(d/k) + ps[min(d%k, n)]) >= c)
        k += 1;

    cout << k-2 << '\n';

}

int main() {
    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
