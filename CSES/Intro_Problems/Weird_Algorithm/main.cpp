#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll n;
void solve() {
    cin >> n;

    cout << n << ' ';
    while(n>1) {
        if(n&1) n=n*3+1;
        else n/=2;
        cout << n << ' ';
    }
    cout << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
