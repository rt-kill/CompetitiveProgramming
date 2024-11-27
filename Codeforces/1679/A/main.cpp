#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll n;

void solve() {
    cin >> n;
    // what is max (i+j) such that 4*i + 6*j = n
    // what is min (i+j) such that 4*i + 6*j = n

    // we can always replace 3i with 2j and vice versa
    //  if solution exists, one exists for which i < 3 and one exists for which j < 2

    ll m = -1;
    ll M = -1;

    if (n % 6 == 0)
        m = n/6;
    else if ((n-4) % 6 == 0)
        m = (n-4)/6 + 1;
    else if ((n-8) % 6 == 0)
        m = (n-8)/6 + 2;
    else {
        cout << -1 << '\n';
        return;
    }

    if ((n % 4) == 0)
        M = n/4;
    else if ((n-6) % 4 == 0)
        M = (n-6)/4 + 1;
    else {
        cout << -1 << '\n';
        return;
    }

    cout << m << ' ' << M << '\n';
}

int main() {
    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
