#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, a[int(1e5) + 9];

void solve() {
    cin >> n;
    for(int i=0;i<n;i++)
        cin >> a[i];

    // We can never get an even number above another even number
    // Same with odds
    // If even numbers are already sorted and odd numbers are already sorted, then yes

    bool eis = 1; int pe = 0;
    bool ois = 1; int po = 1;

    for(int i=0;i<n;i++) {
        if (a[i]&1)
            ois = ois&&(po <= a[i]), po = a[i];
        else
            eis = eis&&(pe <= a[i]), pe = a[i];
    }

    if(eis&&ois)
        cout << "YES" << '\n';
    else
        cout << "NO" << '\n';
}

int main() {
    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
