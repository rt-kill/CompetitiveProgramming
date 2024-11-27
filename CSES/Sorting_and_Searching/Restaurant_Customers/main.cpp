#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n;
vector<pair<int, int>> t;

void solve() {
    cin >> n;
    t.resize(2*n);
    for(int i=0; i<2*n; i+=2) {
        cin >> t[i].first; t[i].second = 1;
        cin >> t[i+1].first; t[i+1].second = -1;
    }
    sort(t.begin(), t.end());

    int cur = 0, res = 0;
    for(auto [ a, b ] : t)
        cur += b, res = max(res, cur);
    cout << res << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
