#include <bits/stdc++.h>
using namespace std;

int t, n;
string s1, s2;

void solve() {
    cin >> n; cin >> s1; cin >> s2;

    for (int i = 0; i < n/2; i++) {
        swap(s2[i], s2[n - i - 1]);
        if (min(s1[i], s2[i]) != min(s1[n-i-1], s2[n-i-1]) or max(s1[i], s2[i]) != max(s1[n-i-1], s1[n-i-1])) {
            cout << "NO" << '\n';
            return;
        }
    }

    cout << "YES" << '\n';

    // Question: can the order of characters in s1 change?
    //  NO! Let i < j be arbitrary. Let c = s1[i] and c' = s1[j]
    //  At any point in time, either c and c' are in s1, c is in s2 and c' is in s1, or c c' is in s2 (order is always maintained)

    // Let M(k) represent operation k on s1, s2
    //  If k1 <= k2, M(k2)[ M(k1)[ s1, s2 ]] = M(k2 - k1)[ s1, s2 ]
    // So any sequence of moves can be done in a strictly decreasing order

    // If k1 > k2, M(k2)[ M(k1)[ s1, s2 ]] = [ s1[0:k2] + s2[k2:k1] + s1[k1:], s2[0:n-k1] + ]

    // Idea: We can merge s1 and s2 in a way that preseves their relative ordering
    //  such that the first half of this word equals the second, if and only if yes

    // Proof: For any sequence k[i] of strictly decreasing move values, applying all these moves will give us
    //  F2 = s2[0:(n - k[1])] + s1[0:k[1] - k[2]] + s2[(n - k[2]):(n - k[3])] + ...
    //  F1 = ... + s1[...] + s2[...] + s1[k[1]:]

    // If we reverse s2, this becomes we can swap individual characters

    // Algorithm:
    //  reverse s2,



    // Consider the string s1 + s2. The question becomes can we construct ww
    //
}

int main() {
    cin >> t;
    for (int i = 0; i < t; i++)
        solve();

    return 0;
}
