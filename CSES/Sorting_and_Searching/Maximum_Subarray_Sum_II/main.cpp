#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll n, a, b, x[200001], pf[200001], maxs[200001];

void solve() {
    cin >> n >> a >> b;
    x[0] = 0, pf[0] = 0;
    for(int i=1;i<=n;i++) cin >> x[i];
    for(int i=1;i<=n;i++) pf[i] = x[i] + pf[i-1];

    // for each i, what is the max element in pf[i+a-1, i+b-1]
    ll l = a, r = b;
    deque<pair<ll, ll>> deck;

    for (int i = l; i < r; i++) {
        while(!deck.empty() && deck.back().first < pf[i]) deck.pop_back();
        deck.push_back({ pf[i], i });
    }

    while(l <= n) {
        if (!deck.empty() && deck.front().second < l) deck.pop_front();
        while(!deck.empty() && deck.back().first < pf[r]) deck.pop_back();
        deck.push_back({ pf[r], r });

        maxs[l - a + 1] = deck.front().first;

        l++, r++;
        r = min(r, n);
    }

    ll res = pf[a];
    for (int i=1; i+a-1 <= n; i++)
        res = max(res, maxs[i] - pf[i-1]);
    cout << res << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
