#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 2e5 + 1;
ll n, a[N];

// Does there exist a partioning (into 2) of pieces [i:] that have a difference between (delta-1 & delta)
// solution is dp(0, 1);

void solve() {
    cin >> n;
    ll sum = 0;
    multiset<ll> s;
    for (int i=0;i<n;i++) {
        cin >> a[i];
        s.insert(a[i]);
        sum += a[i];
    }

    stack<ll> st; st.push(sum);
    while (!st.empty()) {
        ll elm = st.top(); st.pop();

        if (s.count(elm)) {
            s.erase(s.lower_bound(elm));
        }
        else if (elm > 1) {
            st.push(elm/2);
            st.push((elm + 1)/2);
        } else if (elm == 1) {
            break;
        }
    }

    if (s.empty())
        cout << "YES" << '\n';
    else
        cout << "NO" << '\n';
}

int main() {
    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
