#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, tmp;
ll x;
vector<int> w;

vector<pair<int, ll>> memory;
pair<int, ll> dp(int mask) {
    if (memory[mask].first == -1) {
        pair<int, ll> res = {n, 0};

        int i = 0, e = 1;
        while (i < n) {
            if (e & mask) {
                auto tmp = dp(e ^ mask);

                tmp.first += (tmp.second + w[i] > x);
                tmp.second = (tmp.second + w[i] <= x) ? tmp.second + w[i] : w[i];

                res = min(res, tmp);
            }

            i++, e <<= 1;
        }

        memory[mask] = res;
    }

    return memory[mask];
}

void solve() {
    cin >> n >> x;
    while (cin >> tmp) w.push_back(tmp);

    memory = vector<pair<int, ll>>(1<<n, {-1, -1});
    memory[0] = {0, x};

    auto res = dp((1<<n) - 1);
    cout << res.first << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
