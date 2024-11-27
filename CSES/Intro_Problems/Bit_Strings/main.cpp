#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int M = 1e9 + 7;

ll modpow(ll v, ll e) {
    ll res = (e&1) ? v : 1;
    if (e > 1) {
        ll sub = modpow(v, e/2);
        res = (((res * sub) % M) * sub) % M;
    }

    return res;
}

int n;
void solve() {
    cin >> n;
    cout << modpow(2, n) << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
