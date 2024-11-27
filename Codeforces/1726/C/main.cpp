#include <bits/stdc++.h>
using namespace std;

int t;
int n;
string s;

// solve s[i:] for sum equal c
int rec(int l, int r, int c) {
    int res = 0;
    int count = 0;
    int l = 0;
}

void solve() {
    cin >> n;
    cin >> s;

    // for all i < j < k, if (i, k) is balanced and (i, j) is balanced, then so is (j+1, k)
    //  There is an edge from 1 to i if and only if there is an edge from i+1 to n

    // Suppose for some i, (1, i) and (i+1, n) are balanced
    //  For all j < i < k, (j+1, k) is balanced if and only if
    //      (1, j), (k+1, n), (j+1, i) and (i+1, k) are balanced

    // So the components in s = comp([1, i]) + comp([i+1, n]) - 1

    // (1, j) is connected if and only if { sum ( delta('(') ) - sum ( delta(')') ) } == 0

    int res = 1;
    int count = 0;
    int l = 0;
    for (int i = 0; i < 2*n; i++) {
        l += 1;
        if (s[i] == '(') count += 1;
        else count -= 1;

        if (count == 0) {
            res += l/2 - 1;
            l = 0;
        }
    }

    cout << res << '\n';
}

int main() {
    cin >> t;
    for (int i = 0; i < t; i++)
        solve();

    return 0;
}
