#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, m, k;
vector<int> a, b;

void solve() {
    cin >> n >> m >> k;
    a.resize(n), b.resize(m);
    for(int i=0; i<n; ++i) cin >> a[i];
    for(int i=0; i<m; ++i) cin >> b[i];

    sort(a.begin(), a.end()), sort(b.begin(), b.end());

    int i=0, j=0, res=0;
    while(i < n && j < m) {
        if (abs(a[i] - b[j]) <= k)
            ++res, ++i, ++j;
        else if (a[i] < b[j]) ++i;
        else ++j;
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
