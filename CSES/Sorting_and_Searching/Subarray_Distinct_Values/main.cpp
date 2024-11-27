#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, k, x[200000];
void solve() {
    cin >> n >> k;
    for (int i=0;i<n;i++) cin >> x[i];

    map<int, int> counts;

    ll res = 0;
    int s=0, v=0, l=0, r=0;
    while(l < n) {
        while((v < k || counts[x[r]]) && r < n) {
            v += !counts[x[r]];
            counts[x[r]] += 1;
            r++;
        }

        res += r - l;

        counts[x[l]] -= 1;
        v -= !counts[x[l++]];
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
