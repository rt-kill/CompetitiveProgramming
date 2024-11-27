#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    string tmp;
    int res1=0, res2=0;
    while(true) {
        vector<int> vals;
        getline(std::cin, tmp, '-');
        if (tmp.empty()) break;
        vals.push_back(stoi(tmp));
        getline(std::cin, tmp, ',');
        vals.push_back(stoi(tmp));
        getline(std::cin, tmp, '-');
        vals.push_back(stoi(tmp));
        getline(std::cin, tmp);
        vals.push_back(stoi(tmp));

        if ((vals[0] >= vals[2] && vals[3] >= vals[1]) || (vals[0] <= vals[2] && vals[3] <= vals[1]))
            res1++;
        if ((vals[0] >= vals[2] && vals[3] >= vals[0]) || (vals[2] >= vals[0] && vals[1] >= vals[2]))
            res2++;
    }

    cout << res1 << ' ' << res2 << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();
        return 0;
}
