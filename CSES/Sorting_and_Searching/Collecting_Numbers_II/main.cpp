#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, m;
vector<int> x;
vector<int> y;

vector<int> is;
/* vector<int> bit; */

/* void update(int k, int u) { */
/* } */

/* int query() { */
/*     return 0; */
/* } */

void solve() {
    cin >> n >> m;
    x.resize(n+2), y.resize(n+2), is.resize(n+2);
    x[0] = 0, y[0] = INT_MAX;
    for(int i=1; i<=n; ++i) {
        cin >> x[i];
        y[x[i]] = i;
    }
    x[n+1] = n+1, y[n+1] = INT_MAX;

    int hc=0;
    for(int i=1; i<=n; ++i) {
        if (y[i] < y[i-1]) {
            is[i] = 1;
            ++hc;
        }
    }

    /* for(auto v : x) cout << v << ' '; */
    /* cout << '\n'; */
    /* for(auto v : y) cout << v << ' '; */
    /* cout << '\n'; */
    /* for(auto v : is) cout << v << ' '; */
    /* cout << '\n'; */
    /* cout << hc << '\n'; */

    int a, b, s, t;
    while(m--) {
        cin >> a >> b;
        s = x[a], t = x[b];

        swap(x[a], x[b]);
        swap(y[s], y[t]);

        if (y[s] < y[s-1]) {
            int diff = (1 - is[s]);
            hc += diff, is[s] += diff;
        } else {
            int diff = (0 - is[s]);
            hc += diff, is[s] += diff;
        }

        if (y[s+1] < y[s]) {
            int diff = (1 - is[s+1]);
            hc += diff, is[s+1] += diff;
        } else {
            int diff = (0 - is[s+1]);
            hc += diff, is[s+1] += diff;
        }

        if (y[t] < y[t-1]) {
            int diff = (1 - is[t]);
            hc += diff, is[t] += diff;
        } else {
            int diff = (0 - is[t]);
            hc += diff, is[t] += diff;
        }

        if (y[t+1] < y[t]) {
            int diff = (1 - is[t+1]);
            hc += diff, is[t+1] += diff;
        } else {
            int diff = (0 - is[t+1]);
            hc += diff, is[t+1] += diff;
        }

        /* for(auto v : x) cout << v << ' '; */
        /* cout << '\n'; */
        /* for(auto v : y) cout << v << ' '; */
        /* cout << '\n'; */
        /* for(auto v : is) cout << v << ' '; */
        /* cout << '\n'; */
        cout << hc << '\n';
    }

    // array A that sends v to its position in x
    // array B that sends v1 to v2 such that
    //  [v2, v1] is increasing in x
    //  [v2-1, v1] is not

    // swaping values at indices [ a, b ] in x is the same as swapping values at indices x[a], x[b] in A
    // In B, every value before min(x[a], x[b]) are the same
    // first assume |x[a] - x[b]| is large
    //  if (A[x[b]] > A[x[a]-1])
    //      B[x[a]] will become B[x[a]-1]
    //      every index i for which B[i] = x[a] will become B[x[a]]
    //  if (A[x[b]] < A[x[a]+1])
    //      every index i for which B[i] = x[a]+1 will become B[x[a]]
    //  if (A[x[a]] > A[x[b]-1])
    //      B[x[b]] will become B[x[b]-1]
    //      every index i for which B[i] = x[b] will become B[x[b]]
    //  if (A[x[a]] < A[x[b]+1])
    //      every index i for which B[i] = x[b]+1 will become B[x[b]]
    //

    // the solution to x is the min partitioning of A into increasing subarrays
    // this is the same as the number of unique values in B
    // we can maintain a bit that has a 1 at loctions for which these intervals start
    //

    //
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
