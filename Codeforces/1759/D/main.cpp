#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, m;

void solve() {
    cin >> n >> m;

    int c2s = 0; int tmp = n;
    while (!(tmp&1)) {
        tmp /= 2;
        c2s += 1;
    }

    int c5s = 0; tmp = n;
    while (!(tmp % 5)) {
        tmp /= 5;
        c5s += 1;
    }

    ll k = 1;
    while (true) {
        if (c2s < c5s) {
            if ((k<<1) <= m) { k<<=1; c2s += 1; }
            else break;
        }

        if (c5s < c2s) {
            if (k*5 <= m) { k*=5; c5s += 1; }
            else break;
        }

        if (c2s == c5s) {
            if (k*10 <= m) { k*=10; }
            else break;
        }
    }

    k = (m/k) * k;

    ll res = ll(n)*ll(k);

    cout << res << '\n';
}

int main() {
    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
