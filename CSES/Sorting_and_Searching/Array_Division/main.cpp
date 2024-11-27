#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, k;
vector<ll> x;

bool check(ll v) {
    int i = 0;
    for(int j=1; j<=k; j++) {
        ll sum = 0;
        while(i < n && sum + x[i] <= v)
            sum += x[i++];
    }

    return (i == n);
}

void solve() {
    cin >> n >> k;

    x.resize(n);
    for(int i=0; i<n; i++) cin >> x[i];

    ll Ms=LLONG_MAX, res=Ms;
    for(ll k=Ms/2; k>0; k>>=1) {
        while(check(res - k)) res -= k;
    }
    cout << res << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
