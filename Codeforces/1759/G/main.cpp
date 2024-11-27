#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 2e5 + 9;
int n, b[N], p[N];

inline int bin_ser(vector<int>& li, int v) {
    int l=0, r=li.size()-1, m;

    while(l<r) {
        m=(l+r)/2;
        if (li[m+1] < v) l = m+1;
        else r=m;
    }

    if (li[l] < v) return li[l];
    return -1;
}

void solve() {
    cin >> n;
    for (int i=1;i<=n/2;i++) {
        cin>>b[i];
    }

    set<int> sb(b+1, b+1+(n/2));
    if (sb.size() < n/2) {
        cout << -1 << '\n';
        return;
    }

    set<int, greater<int>> sc;

    for (int i=n;i>=1;i--)
        if(!sb.count(i)) {
            sc.insert(i);
        }

    for(int i=n/2;i>=1;i--) {
        auto it = sc.upper_bound(b[i]);
        if (it == sc.end()) {
            cout << -1 << '\n';
            return;
        }

        int lv = *it;
        sc.erase(lv);

        p[2*i] = b[i];
        p[2*i - 1] = lv;
    }

    for (int i = 1; i<= n;i++)
        cout << p[i] << ' ';
    cout << '\n';
}

int main() {
    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
