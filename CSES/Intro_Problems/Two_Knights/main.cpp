#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n;
ll res[10001] = {0, 0, 6, 28, 96, 252, 550, 1056};
void solve() {
    cin >> n;

    // from corner squares, knights have only two moves
    // from squares adj to corners, knights have only 3 moves
    // from any other square on an edge, a knight has 4 moves

    // for the inner k-2 by k-2 board,
    //  over its corner squares, knights have 4 moves
    //  any other square on an edge admits 6 moves

    // every other square admits 8 moves



    for(int k=5; k<=n; ++k) {
        ll ns = 2*k - 1; // new squares added
        ll nsc2 = (ns*(ns-1))/2; // ways of choosing two new squares
        ll bnsgp = nsc2 - 2; // only two of these choices have attacking knights

        ll onsp = (k-1)*(k-1)*(ns); // ways of choosing on square from (k-1, k-1), and one outside of that
        ll onsbp = 2*3 + 3*4 + 4*(ns - 3 - 4) - 4; // number of bad pairs for such choices
        ll onsgp = onsp - onsbp;

        res[k] = res[k-1] + bnsgp + onsgp;
    }

    for(int i=1; i<=n; i++)
        cout << res[i] << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
