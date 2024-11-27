#include <bits/stdc++.h>
using namespace std;

int t, n;
int a[int(2e5)];
int w1, w2, w3;
int res;

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    sort(a, a + n);

    // if there exists w1, w2, w3 in b1, b2, b3 respectively
    // for which w1 < w2 < w3, then we can easily beat this by
    // letting b1 = {a[n-1]}, b2 = {a[0]}, b3 = else
    // the same follows for w1 > w2 > w3

    // so for all w1, w2, w3 in b1, b2, b3,
    // (w1 > w2 or w2 > w3) and (w1 < w2 or w2 < w3)

    // that is either every w2 < w1 or every w3 < w2
    // and either every w2 > w1 or every w2 < w3

    // putting these together, either every w2 < min(w1, w3) or every w2 > max(w1, w3)

    // in the case of the former, w2 will always be max(b2) and w1, w3 will always be min(b1) min(b3)
    //

    res = 0;
    for (int i = 0; i < n - 2; i++) {
        w1 = a[n-1]; w2 = a[i]; w3 = a[i+1];
        res = max(res, abs(w1 - w2) + abs(w2 - w3));

        w1 = a[0]; w2 = a[n - i - 1]; w3 = a[n - i - 2];
        res = max(res, abs(w1 - w2) + abs(w2 - w3));
    }

    cout << res << '\n';
}

int main() {
    cin >> t;
    for (int i = 0; i < t; i++)
        solve();

    return 0;
}
