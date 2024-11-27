#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, m;

vector<vector<int>> vals;
vector<int> counts;

void solve() {
    counts.clear(), vals.clear();
    cin >> n >> m;

    int tmp;
    for(int i=0; i<n; i++) {
        vals.push_back(vector<int>());
        counts.push_back(0);

        for(int j=0; j<m; j++) {
            cin >> tmp;
            vals.back().push_back(tmp);
            counts.back() += tmp;
        }
    }

    int tot = accumulate(counts.begin(), counts.end(), 0, plus{});
    if (tot % n != 0) {
        cout << -1 << '\n';
        return;
    }
    int des = tot / n;

    set<int> large, small;
    for(int i=0; i<n; i++) {
        if (counts[i] > des) large.insert(i);
        if (counts[i] < des) small.insert(i);
    }

    vector<tuple<int, int, int>> res;
    for(int i=0; i<m; i++) {
        auto lp = large.begin(), sp = small.begin();
        vector<int> lrem, srem;

        while (lp != large.end() && sp != small.end()) {
            int lv = *lp, sv = *sp;
            if (vals[lv][i] == 0) lp = next(lp);
            if (vals[sv][i] == 1) sp = next(sp);
            if (vals[lv][i] == 1 && vals[sv][i] == 0) {
                res.push_back({ lv+1, sv+1, i+1 });
                counts[lv]--, counts[sv]++;
                lp = next(lp), sp = next(sp);

                if (counts[lv] == des) lrem.push_back(lv);
                if (counts[sv] == des) srem.push_back(sv);
            }
        }

        for(auto v : lrem) large.erase(v);
        for(auto v : srem) small.erase(v);
    }

    if (!large.size() && !small.size()) {
        cout << res.size() << '\n';
        for (auto [ x, y, z ] : res)
            cout << x << ' ' << y << ' ' << z << '\n';
    }

    else cout << -1 << '\n';
}

int main() {
    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
