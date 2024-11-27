#include <bits/stdc++.h>
using namespace std;

const int N = int(2e5) + 9;
int t, n, p[N], q[N];
int ml, Mr;
long long res;

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        q[p[i]] = i;
    }

    // Note:
    //  med(m, m+1, m+2, ..., m+j) = m + j/2
    //  med(p[i], p[i+1], ..., p[j]) >= med(min(...), ... + 1, ..., ... + (j - i)) >= min(p[i:j]) + (j-i)/2

    // mex(p[i], p[i+1], ..., p[(j - i)/2], ..., p[j]) > med(...) IFF:
    //      for all 0 <= k <= (j-i)/2, k is in p[i:(j+1)]
    //          as this implies that (mex > (j-i)/2) and (med = (j-i)/2)
    //          and otherwise (mex <= (j-i)/2) and (med >= (j-i)/2)

    // New Question:
    //  For how many 1 <= l <= r <= n, does p[l:(r+1)] contain { 0, 1, ..., (r - l)/2 }

    // I would like to know, given i, what is (l, r) (for which r - l is minimal) such that p[l:(r+1)] contains { 0, 1, ..., i }

    res = 0;

    int l = q[0]; int r = q[0];
    for (int i = 0; i < n-1; i++) { // maybe don't need to go all the way to n
        while (q[i+1] < l) {
            Mr = min(n-1, i*2 + l + 1);
            res += max(0, (Mr - r) + 1);
            l -= 1;
        }
        while (q[i+1] > r) {
            ml = max(0, r - 2*i - 1);
            res += max(0, (l - ml) + 1);
            r += 1;
        }
    }

    while (0 <= l) {
        Mr = min(n-1, (n-1)*2 + l + 1);
        res += max(0, (Mr - r) + 1);
        l -= 1;
    }

    cout << res << '\n';
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++)
        solve();

    return 0;
}
