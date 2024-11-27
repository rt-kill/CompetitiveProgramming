#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n;
void solve() {
    cin >> n;

    // n/5 is the number of numbrs <= n that are divisible by 5
    // n/25 is the number of numbers <= n that are divisible by 25
    // ...

    int div2 = 0, div5 = 0;
    for(int i=2; i<=n; i*=2)
        div2 += n/i;
    for(int i=5; i<=n; i*=5)
        div5 += n/i;

    int res = min(div2, div5);
    cout << res << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
