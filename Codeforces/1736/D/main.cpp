#include <bits/stdc++.h>
using namespace std;

int t, n;
string s;

char sp(char c) {
    if (c == '0') return '1';
    return '0';
}

void solve() {
    cin >> n; cin >> s;

    int n1 = 0;
    for (int i = 0; i < s.size(); i++)
        if (s[i] == '1') n1 += 1;
    if (n1 & 1) {
        cout << -1 << '\n';
        return;
    }

    vector<int> b;
    char last = s[0];

    for (int i = 0; i < s.size();) {
        char cur = s[i];
        int count = 0;

        while (i < s.size() && s[i] == cur) {
            count += 1;
            i += 1;
        }

        if (count & 1) {
            if (cur == last) {
                b.push_back(i);
                i += 1;
            }
            else {
                i -= 1;
                s[i] = sp(cur);
                b.push_back(i);
            }

            last = sp(last);
        }
    }

    cout << b.size() << ' ';
    for (int i : b)
        cout << (i + 1) << ' ';
    cout << '\n';
    for (int i = 0; i < n; i++)
        cout << 2*(i+1) << ' ';
    cout << '\n';

    // p and q must be exactly equal (they have the same size).
    // Given a string s, how can we tell if it can be partitoned into ...

    //  If s has a solution, it must have an even number of 1's and 0's
    //  If there are not an even number of 1's and 0's, there is no solution
    //  If s has even nubmer of 1's and 0's,
    //  no two adjacent indices of b should have the same values (B is going to be swapping values)
    //  We either start with a 1 or with a 0,

    // Note: Solvable is by 0 moves
    // Suppose s = vw, if v and w are solvable, must s be solvable? (YES)
    //      If s is solvable and v is solvable, must w be?
    //          w must have

    // If the first two indices are the same, must they ever always go to the same partition?
    //
}

int main() {
    cin >> t;
    for (int i = 0; i < t; i++)
        solve();
    return 0;
}
