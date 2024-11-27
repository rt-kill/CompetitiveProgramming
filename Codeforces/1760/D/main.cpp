#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, a[int(2e5) + 9];

void solve() {
    cin >> n;
    for(int i=0;i<n;i++)
        cin >> a[i];

    // A valey is an array that either is only monotonic increasing
    //  Or starts decreasing, and switches to monotonic increasing

    int li = 0;
    int vcount = 0;

    while (li < n) {
        int ili = li;
        while (li + 1 < n && a[li] == a[li + 1]) {
            li += 1;
        }

        if ((ili == 0 || a[ili-1] > a[li]) && (li == n-1 || a[li+1] > a[li]))
            vcount += 1;

        li += 1;
    }

    if (vcount == 1)
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
