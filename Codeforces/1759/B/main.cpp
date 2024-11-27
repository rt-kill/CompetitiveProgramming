#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int m, s, b[100];

void solve() {
    cin >> m >> s;
    for (int i=0;i<m;i++)
        cin >> b[i];

    int bsum=0;
    int mb=0;
    for (int i=0;i<m;i++) {
        bsum+=b[i];
        mb = max(b[i], mb);
    }

    int tmp = mb*(mb+1)/2;
    s -= (tmp - bsum);
    bsum = tmp;

    while (s > 0) {
        mb += 1;
        s -= mb;
    }

    if (s < 0) {
        cout << "NO" << '\n';
        return;
    }

    cout << "YES" << '\n';
    return;
}

int main() {
    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
