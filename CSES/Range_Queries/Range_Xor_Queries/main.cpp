#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, q;
vector<int> x;

void solve() {
    cin >> n >> q;

    x.resize(n+1), x[0] = 0;
    for(int i=1; i<=n; i++) {
        cin >> x[i];
        x[i] ^= x[i-1];
    }

    int a, b;
    while(q--) {
        cin >> a >> b;
        cout << (x[b] ^ x[a-1]) << '\n';
    }
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
