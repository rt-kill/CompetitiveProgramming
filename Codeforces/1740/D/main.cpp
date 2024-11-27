#include <bits/stdc++.h>
using namespace std;

int t, n, m, k;
int a[int(1e5) + 5];

bool solve() {
    cin >> n >> m >> k;
    for (int i = 0; i < k; i++)
        cin >> a[i];

    int pending = 0;
    set<int> seen;
    int next = k;

    int limit;
    if (min(n, m) == 1) limit = 2;
    else if (n == 2 && m == 2) limit = 3;
    else limit = n*m - 2;

    for (int i = 0; i < k; i++) {
        seen.insert(a[i]); pending += 1;
        if (pending >= limit) return false;

        while (seen.count(next)) {
            next -= 1;
            pending -= 1;
        }
    }

    return true;
}

int main() {
    cin >> t;
    for (int i = 0; i < t; i++) {
        if (solve()) cout << "YA";
        else cout << "TIDAK";
        cout << '\n';
    }
}
