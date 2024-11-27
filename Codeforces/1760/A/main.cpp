#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int a, b, c;

void solve() {
    cin >> a >> b >> c;
    cout << a + b + c - max(a, max(b, c)) - min(a, min(b, c)) << '\n';
}

int main() {
    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
