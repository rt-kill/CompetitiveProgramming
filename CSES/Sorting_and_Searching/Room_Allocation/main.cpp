#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n;
vector<array<int, 3>> c;
vector<int> res;

void solve() {
    cin >> n;

    c.resize(n);
    for(int i=0; i<n; ++i) {
        cin >> c[i][0] >> c[i][1];
        c[i][2] = i;
    }
    sort(c.begin(), c.end());

    res.resize(n);

    auto comp = [](auto l, auto r){ return (l[0] > r[0] || (l[0] == r[0] && l[1] > r[1])); };
    priority_queue<array<int, 2>, vector<array<int, 2>>, decltype(comp)> pq(comp);

    int r = 0;
    pq.push({ c[0][1], ++r });
    res[c[0][2]] = r;

    for(int i=1; i<n; ++i) {
        auto [ a, b, j ] = c[i];

        if (pq.size() && pq.top()[0] < a) {
            auto [ ld, ro ] = pq.top();
            pq.pop();

            res[j] = ro;
            pq.push({ b, ro });
        }

        else {
            pq.push({ b, ++r });
            res[j] = r;
        }
    }

    cout << r << '\n';
    for(auto v : res) cout << v << ' ';
    cout << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
