#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n;
map<string, int> mymap;
vector<int> graph;

int aux(int i) {
    set<int> seen = {-1};
    int cur = i, count=0;

    while (!seen.count(cur)) {
        seen.insert(cur);
        cur = graph[cur];
        count++;
    }

    if (cur == i) return count;
    return 0;
}

void solve() {
    cin >> n;

    graph = vector<int>(2*n, -1);
    int val = 0;

    string a, b, c;
    for (int i=0; i<n; ++i) {
        cin >> a >> b >> c;
        if (!mymap.count(b))
            mymap[b] = val++;
        if (!mymap.count(c))
            mymap[c] = val++;

        graph[mymap[b]] = mymap[c];
    }

    int res = 0;
    for (int i = 0; i < 2*n; i++)
        res = max(res, aux(i));

    if (res > 0) cout << res;
    else cout << "No trades possible";
    cout << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
