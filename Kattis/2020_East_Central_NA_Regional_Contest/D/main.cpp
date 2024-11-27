#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int r, s, n;
vector<int> a, b, c;

map<array<int, 3>, int> memory;

int dp(int i=0, int j=0, int k=0, int v=0) {
    // if we run out of trains, we are done
    if (k == n) return 1;
    // if the train is full, go to the next one
    if (v == c[k]) return dp(i, j, k+1, 0);
    // if we have overfilled the train, we have messed up
    if (v > c[k]) return 0;

    // if we have already solved this subproblem, return it
    if (memory.count({i, j, k}))
        return memory[{i, j, k}];

    bool res = 0;
    // if we can take from cart a, try it
    if (i < r) res = res || dp(i+1, j, k, v+a[i%r]);
    // if we can take from cart b, try it
    if (j < s) res = res || dp(i, j+1, k, v+b[j%s]);

    // store and return our solution
    memory[{i, j, k}] = res;
    return res;
}

void solve() {
    cin >> r >> s >> n;

    a.resize(r), b.resize(s), c.resize(n);
    for (int i=0; i<r; i++) cin >> a[i];
    for (int i=0; i<s; i++) cin >> b[i];
    for (int i=0; i<n; i++) cin >> c[i];

    bool res = dp();

    if (res) cout << "Yes";
    else cout << "No";

    cout << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
