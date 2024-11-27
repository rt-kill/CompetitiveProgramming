#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ar array

const int MN = int(2e5);
int n, l[MN], r[MN], c[MN], res[MN];
tuple<int, int> sl[MN], sr[MN], sa[2*MN];
int colors[MN + 1];

void solve() {
    cin >> n;
    for (int i = 0; i<n; i++)
        cin >> l[i] >> r[i] >> c[i];

    fill(res, res+n, INT_MAX);

    for (int i = 0; i<n; i++) {
        sl[i] = make_tuple(l[i], i);
        sr[i] = make_tuple(r[i], i);
    }

    sort(sl, sl + n, less<tuple<int, int>>());
    sort(sr, sr + n, greater<tuple<int, int>>());

    int i1=get<1>(sl[0]), i2=-1;
    for (int t = 0; t < n; t++) {
        int i = get<1>(sl[t]);

        if (c[i] == c[i1])
            i1 = (r[i] > r[i1] ? i : i1);
        else if (i2 == -1)
            i2 = i;
        else if (c[i] == c[i2])
            i2 = (r[i] > r[i2] ? i : i2);
        else if (r[i1] > r[i2] && r[i] > r[i2])
            i2 = i;
        else if (r[i] > r[i1])
            i1 = i;

        if (c[i] != c[i1])
            res[i] = min(res[i], max(0, l[i] - r[i1]));
        if (i2 >= 0 && c[i] != c[i2])
            res[i] = min(res[i], max(0, l[i] - r[i2]));
    }

    i1=get<1>(sr[0]), i2=-1;
    for (int t = 0; t < n; t++) {
        int i = get<1>(sr[t]);

        if (c[i] == c[i1])
            i1 = (l[i] < l[i1] ? i : i1);
        else if (i2 == -1)
            i2 = i;
        else if (c[i] == c[i2])
            i2 = (l[i] < l[i2] ? i : i2);
        else if (l[i1] < l[i2] && l[i] < l[i2])
            i2 = i;
        else if (l[i] < l[i1])
            i1 = i;

        if (c[i] != c[i1]) {
            res[i] = min(res[i], max(0, l[i1] - r[i]));
            res[i1] = min(res[i1], max(0, l[i1] - r[i]));
        }
        if (i2 >= 0 && c[i] != c[i2]) {
            res[i] = min(res[i], max(0, l[i2] - r[i]));
            res[i2] = min(res[i2], max(0, l[i2] - r[i]));
        }
    }

    for (int i = 0; i <n; i++)
        cout << res[i] << " ";
    cout << '\n';

    // Idea: sweep right, then left
    //  For sweep right, order the points by start
    //  Keep adding lines to a stack (while they are the same color)
    //  Once we see a line that is not the same color, we pop every element of the stack, and this is the closest line
    // Then repeat this left


}

int main() {
    int t; cin >> t;
    for (int i = 0; i < t; i++)
        solve();
    return 0;
}
