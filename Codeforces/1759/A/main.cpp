#include <bits/stdc++.h>
using namespace std;

using ll = long long;

string s;

void solve() {
    cin >> s;

    char c = s[0];
    if (c != 'Y' && c != 'e' && c != 's') {
        cout << "NO" << '\n';
        return;
    }

    char n;
    for (int i = 1; i < s.size(); i++) {
        if (c == 'Y') n = 'e';
        if (c == 'e') n = 's';
        if (c == 's') n = 'Y';

        if (s[i] != n) {
            cout << "NO" << '\n';
            return;
        }

        c = s[i];
    }

    cout << "YES" << '\n';
}

int main() {
    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
