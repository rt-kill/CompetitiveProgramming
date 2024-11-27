#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int N = 2e5 + 9;

ll n, h, a[N];

void solve() {
    cin >> n >> h;
    for (int i=0;i<n;i++)
        cin >> a[i];

    sort(a, a+n);
    int res = 0;

    int c[3][4] = {{2,2,3,1}, {2,3,2,1}, {3,2,2,1}};

    for (int p = 0; p < 3; p++) {
        ll th = h; int i = 0;

        for (int j = 0; j < 4; j++) {
            while (i < n && th > a[i]) {
                th += ll(a[i]/2);
                i += 1;
            }

            th *= ll(c[p][j]);
        }

        res = max(res, i);
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
