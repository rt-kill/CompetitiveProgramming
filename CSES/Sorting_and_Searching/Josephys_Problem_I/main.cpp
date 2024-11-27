#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, k=1;
void solve() {
    cin >> n;
    int children[n+1], binary_index_tree[n+1];

    children[0] = 0, binary_index_tree[0] = 0;
    for(int i=1;i<=n;i++) {
        children[i] = 1;
        binary_index_tree[i] = (i & (-i));
    }

    int cl = n, to_skip = 0;
    while(cl > 0) {
        // We set up off so that we can always start at 0
        to_skip = ((k + to_skip) % cl);

        // We now binary search for an index i in children such that
        //  children[i] = 1
        //  #children to our left is to_skip

        int l=1, r=n, m;
        while(l <= r) {
            m = (l + r)/2;

            int v = 0, i = m-1;
            while(i > 0) {
                v += binary_index_tree[i];
                i -= (i & (-i));
            }

            if (v > to_skip) r = m-1;
            else if (v < to_skip || children[m] == 0) l = m+1;
            else break;
        }

        /* cout << '\n'; */
        /* cout << l << ' ' << r << ' ' << m << ' ' << '\n'; */
        /* for(int i=1;i<=n;i++) */
        /*     cout << children[i] << ' ' << binary_index_tree[i] << '\n'; */

        cout << m << ' ';

        children[m] = 0;
        int i = m;
        while(i <= n) {
            binary_index_tree[i] -= 1;
            i += (i & (-i));
        }

        cl--;
    }

    /* for(int i=1;i<=n;i++) cout << children[i] << ' ' << binary_index_tree[i] << '\n'; */

    cout << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
