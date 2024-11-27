#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, a[10001];

void solve() {
    cin >> n;
    for(int i=1;i<=n;i++)
        cin>>a[i];

    vector<int> mt = {a[1], a[2]};
    sort(mt.begin(), mt.end());

    for (int i=3; i<=n;i++) {
        mt[0] = max(mt[0], a[i]);
        sort(mt.begin(), mt.end());
    }

    cout << mt[0] + mt[1] << '\n';
}

int main() {
    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
