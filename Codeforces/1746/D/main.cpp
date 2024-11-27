#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll n, k, p[200009], s[200009];
vector<int> c[200009];

vector<pair<int, ll>> memory[200009];
ll dfs(int i, ll t) {
    for (auto [tp, ans] : memory[i])
        if (t == tp)
            return ans;

    int cs = c[i].size();
    ll slb = t*s[i];
    if (cs == 0)
        return slb;

    ll lb = t/cs, ub = t/cs + 1;
    if(t%cs == 0)
        for (int j: c[i])
            slb += dfs(j, lb);
    else {
        vector<ll> diffs;

        for (int j : c[i]) {
            ll o1 = dfs(j, lb);
            ll o2 = dfs(j, ub);

            slb += o1;
            diffs.push_back(o2 - o1);
        }

        sort(diffs.begin(), diffs.end(), greater<int>());
        for (int z=0;z<(t-(cs*lb));z++)
            slb+=diffs[z];
    }

    memory[i].push_back({t, slb});
    return slb;
}

void solve() {
    cin >> n >> k;
    for (int i=2;i<=n;i++)
        cin >> p[i];
    for (int i=1;i<=n;i++)
        cin >> s[i];

    fill(c, c+n+1, vector<int>());
    for (int i=2;i<=n;i++)
        c[p[i]].push_back(i);

    fill(memory, memory+n+1, vector<pair<int, ll>>());
    ll res = dfs(1, k);
    cout << res << '\n';
}

int main() {
    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
