#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n;
vector<int> t;

void solve() {
    cin >> n;
    t.resize(n);
    for(int i=0;i<n;++i)
        cin >> t[i];

    sort(t.begin(), t.end(), greater<int>());
    ll off = t[0], res = t[0];
    for(int i=1; i<n; ++i) res += t[i], off -= t[i];
    res += max(off, 0ll);
    cout << res << '\n';

    // p1 will need to eventually read book 0, and solutions are closed under shifting the books read
    // p1 reads all books starting at 0
    //  this will take sum(books) time
    // p2 reads all books starting at 1
    //  this will take max(0, t[0] - sum[t[1, n-1]]) time;
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
