#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n;
void solve() {
    cin >> n;
    if (!((n-1)/2 & 1)) cout << "NO" << '\n';
    else {
        cout << "YES" << '\n';

        bool odd = n&1; n -= odd;

        cout << n/2 + odd << '\n';
        for(int i=n/2; i>n/4; --i)
            cout << i << ' ' << n-i+1 << ' ';
        cout << '\n';

        cout << n/2 << '\n';
        if (odd) cout << n+1 << ' ';
        for(int i=n/4; i>0; --i)
            cout << i << ' ' << n-i+1 << ' ';
        cout << '\n';
    }
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
