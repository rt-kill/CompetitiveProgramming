#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ar array

ll n, q, a[int(1e5)+9];

void solve() {
    cin >> n >> q;
    for (int i=0;i<n;i++)
        cin >> a[i];

    ll ne=0, no=0, s=0;
    for (int i=0;i<n;i++) {
        s += a[i];
        if (a[i]&1) no += 1;
        else ne += 1;
    }

    ll t, x;
    for (int i=0;i<q;i++) {
        cin >> t >> x;
        if (t == 0) {
            s += ne * x;
            if (x&1) { no += ne; ne = 0; }
        } else {
            s += no * x;
            if (x&1) { ne += no; no = 0; }
        }
        cout << s << '\n';
    }

}

int main() {
    int t; cin >> t;
    for (int i=0;i<t;i++)
        solve();
    return 0;
}
