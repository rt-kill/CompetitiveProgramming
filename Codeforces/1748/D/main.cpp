#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll t, a, b, d;

void solve() {
    cin >> a >> b >> d;

    int off = 0;
    while ( !(d&1) ) {
        if ((a&1) || (b&1)) {
            cout << -1 << '\n';
            return;
        }

        a>>=1; b>>=1; d>>=1; off += 1;
    }


    ll x=0, tmp=0, op=d;
    for (int bi = 0; bi < 30; bi++) {
        if (!(tmp&1)) {
            tmp += d;
            x += op;
        }

        tmp >>= 1;
        op <<= 1;
    }

    x <<= off;

    cout << x << '\n';
}

int main() {
    cin >> t;
    for (int i = 0; i < t; i++)
        solve();
    return 0;
}
