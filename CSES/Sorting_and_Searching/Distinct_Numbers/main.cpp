#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n;
vector<int> x;
void solve() {
    cin >> n;
    x.resize(n);
    for(int i=0;i<n;++i) cin >> x[i];

    sort(x.begin(), x.end());
    x.erase( unique(x.begin(), x.end()), x.end());
    cout << x.size() << "\n";
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
