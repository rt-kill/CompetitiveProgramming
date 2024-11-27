#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, a, b;

void solve() {
    cin >> n >> a >> b;

    // if a == b == n, then it is true
    // if (a + b) >= n, then it is true if and only if a == b == n;
    // otherwise (a + b) < n;
    //  obviously if (a + b) <= n - 2, it is true
    //  otherwise it can not be true

    bool res;
    if ((a + b) >= n)
        res = ((a == b) && (b == n));
    else
        res = ((a + b) <= n-2);

    if (res)
        cout << "Yes" << '\n';
    else
        cout << "No" << '\n';
}

int main() {
    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
