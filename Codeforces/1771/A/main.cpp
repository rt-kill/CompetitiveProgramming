#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll n;
vector<ll> a;
void solve() {
    a.clear();

    cin >> n;
    ll tmp;
    for (ll i = 0; i < n; i++) {
        cin >> tmp;
        a.push_back(tmp);
    }

    ll Ma = * max_element(a.begin(), a.end());
    ll ma = * min_element(a.begin(), a.end());

    if (Ma == ma) {
        cout << n * (n-1) << '\n';
        return;
    }

    ll Mac = transform_reduce(a.cbegin(), a.cend(), 0l, plus{}, [Ma](ll v){ return (v == Ma); });
    ll mac = transform_reduce(a.cbegin(), a.cend(), 0l, plus{}, [ma](ll v){ return (v == ma); });

    cout << 2l * Mac * mac << '\n';
}

int main() {
    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
