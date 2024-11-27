#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define ar array

int a, b, c, d;
vector<int> factors;

void factorize(int x) {
    for (int f = 2; f*f <= x; f++) {
        while (x%f == 0) {
            factors.push_back(f);
            x /= f;
        }
    }

    if (x != 1)
        factors.push_back(x);
}

set<pair<int, int>> seen;
pair<int, int> dfs(int i, ll mx, ll my) {
    if (mx > c || my > d)
        return make_pair(-1, -1);
    if (seen.count(make_pair(mx, my)))
        return make_pair(-1, -1);
    seen.insert(make_pair(mx, my));

    if (i == factors.size()) {
        ll x = ll(a/mx + 1)*ll(mx);
        ll y = ll(b/my + 1)*ll(my);
        if (x <= c && y <= d)
            return make_pair(x, y);
        return make_pair(-1, -1);
    }

    pair<int, int> l = dfs(i+1, ll(mx)*ll(factors[i]), my);
    pair<int, int> r = dfs(i+1, mx, ll(my)*ll(factors[i]));

    if (l.first == -1) return r;
    return l;
}

void solve() {
    cin >> a >> b >> c >> d;
    factors = vector<int>();
    factorize(a); factorize(b);
    sort(factors.begin(), factors.end(), greater<int>());

    seen.clear();
    int x, y;
    tie(x, y) = dfs(0, 1, 1);
    cout << x << ' ' << y << '\n';
}

int main() {
    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
