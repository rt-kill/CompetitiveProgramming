#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, s[int(2e5) + 9], res[int(2e5) + 9];
pair<int, int> si[int(2e5) + 9];

void solve() {
    cin >> n;
    for(int i = 0; i<n; i++)
        cin >> s[i];

    for(int i = 0; i<n; i++)
        si[i] = { s[i], i };
    sort(si, si+n);

    for (int i=0; i<n-1; i++)
        res[si[i].second] = si[i].first - si[n-1].first;
    res[si[n-1].second] = si[n-1].first - si[n-2].first;

    for (int i=0; i<n; i++)
        cout << res[i] << ' ';
    cout << '\n';
}

int main() {
    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
