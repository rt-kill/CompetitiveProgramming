#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    ll n, tmp, sum=0, res;

    cin >> n;
    for(int i=1;i<n;i++)
        cin >> tmp, sum += tmp;

    res = n*(n+1)/2 - sum;
    cout << res << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
