#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, x;
vector<int> coins;

void solve() {
    cin >> n;
    while(cin >> x) coins.push_back(x);
    sort(coins.begin(), coins.end());

    ll ub = 1;
    for (auto c : coins)
        ub += c*(c <= ub);

    cout << ub << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
