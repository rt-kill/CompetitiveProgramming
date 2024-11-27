#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ar array

int n, a[60];
char d[60];
string s;

void solve(){
    cin >> n;
    for (int i=0;i<n;i++)
        cin >> a[i];
    cin >> s;

    fill(d, d+55, '.');
    for (int i=0;i<n;i++) {
        if (d[a[i]] == '.') {
            d[a[i]] = s[i];
        } else if (d[a[i]] != s[i]) {
            cout << "NO" << '\n';
            return;
        }
    }
    cout << "YES" << '\n';
}

int main() {
    int t; cin >> t;
    for (int i =0; i<t;i++)
        solve();
    return 0;
}
