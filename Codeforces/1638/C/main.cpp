#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, p[int(1e5) + 9];

void solve() {
    cin >> n;
    for(int i=0;i<n;i++)
        cin >> p[i];

    set<int, greater<int>> unseen(p, p+n);
    int comps = 0;
    int cm = p[0]; int i = 0;

    while(!unseen.empty()) {
        while( unseen.lower_bound(cm) != unseen.end() ) { // there is something smaller than the current max to our right
            cm = max(cm, p[i]);
            unseen.erase(p[i]);
            i += 1;
        }


        comps += 1;
        cm = (i < n) ? p[i] : -1;
    }

    cout << comps << '\n';
}

int main() {
    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
