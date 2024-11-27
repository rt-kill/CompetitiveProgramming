#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n;
string s;

void solve() {
    cin >> n; cin >> s;
    char c = 'a';
    for (char m : s) c = max(c, m);
    cout << c - 'a' + 1 << '\n';
}

int main() {
    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
