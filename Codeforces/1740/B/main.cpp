#include <bits/stdc++.h>
using namespace std;

int t, n;
long long a, b;

void solve() {
    cin >> n;

    long long res = 0;
    long long mh = 0;
    for (int i = 0; i < n; i++) {
        cin >> a >> b;
        res += 2 * min(a, b);
        mh = max(mh, max(a, b));
    }
    res += 2 * mh;

    cout << res << '\n';
}

int main() {
    cin >> t;
    for (int i = 0; i < t; i++)
        solve();

    return 0;
}
