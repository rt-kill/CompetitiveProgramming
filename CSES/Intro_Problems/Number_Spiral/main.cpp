#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll r, c;
void solve() {
    cin >> r >> c;

    ll res;
    if (r >= c) {
        bool sal = (r & 1);
        if (sal) res = (r-1)*(r-1) + c;
        else res = (r * r) - c + 1;
    }

    else {
        bool sat = !(c & 1);
        if (sat) res = (c-1)*(c-1) + r;
        else res = (c * c) - r + 1;
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
