#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int n, l, r;

void solve() {
    cin >> n >> l >> r;

    // We always start at node 1 and go to node 2
    // We would like to use all edges with node 1 as soon as possible

    // 1 2 1 3 1 4 1 5 ... 1 n      -- takes every edge with 1 accept for (n, 1)
    //      length: 2*(n-1)
    //      edges: 2*(n-1) - 1
    // 2 3 2 4 2 5 2 6 ... 2 n-1    -- takes every (untaken) edge with 2 accept for (n-1, 2) and (2, n)
    //      length: 2*(n-3)
    //      edges: 2*(n-3)
    // 3 4 3 5 3 6     ... 3 n-2    -- takes every (untaken) edge with 3 accept for (n-2, 3) and (3, n-1)
    //      length: 2*(n-5)
    //      edges: 2*(n-5)

    // ...

    // ODD: n/2+1 n/2+2
    //      length: 2
    //      edges: 2
    //  n/2 n/2+3 n/2-1 ... n-1 2 n 1
    //      length: n-2
    //      edges: n-3
    //  Check: 2*(n-1 + n-3 + n-5 + ... + 1) + n - 4
    //

    // EVEN: n/2 n/2+1
    //      length: 2
    //  n/2 n/2+2 n/2-1 n/2+3 ... n-1 2 n 1
    //      length: n-1


    for (int i=1; i<n; i++) {

    }
}

int main() {
    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
