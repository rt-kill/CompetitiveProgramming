#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, x;
vector<int> w;
void solve() {
    cin >> n >> x;
    w.resize(n);
    for(int i=0; i<n; ++i)
        cin >> w[i];

    sort(w.begin(), w.end());
    int l=0, r=n-1, res=0;
    while(l <= r) {
        l += (w[l] + w[r] <= x);
        --r, ++res;
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
