#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int l, r, x, a, b;

void solve() {
    cin >> l >> r >> x;
    cin >> a >> b;


    int res;
    if (a == b)
        res = 0;
    else if (abs(a - b) >= x)
        res = 1;
    else if (abs(a - l) >= x && abs(b - l) >= x)
        res = 2;
    else if (abs(a - r) >= x && abs(b - r) >= x)
        res = 2;
    else if (abs(a - l) >= x && abs(l - r) >= x && abs(r - b) >= x)
        res = 3;
    else if (abs(a - r) >= x && abs(l - r) >= x && abs(l - b) >= x)
        res = 3;
    else
        res = -1;

    cout << res << '\n';
}

int main() {
    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
