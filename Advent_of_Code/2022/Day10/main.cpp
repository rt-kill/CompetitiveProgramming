#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    string line;

    vector<int> vals(2, 1);
    cout << vals.size() << '\n';

    int cycle = 1;
    while (true) {
        getline(std::cin, line);
        if (line.empty()) break;

        string inst = line.substr(0, 4);
        if (inst == "noop") {
            vals.push_back(vals.back());
            cycle++;
            continue;
        }

        int num = stoi(line.substr(5));
        vals.push_back(vals.back());
        vals.push_back(vals.back() + num);
    }

    int res1 = 20*vals[20] + 60*vals[60] + 100*vals[100] + 140*vals[140] + 180*vals[180] + 220*vals[220];
    cout << res1 << '\n';

    for (int r=0; r<6; r++) {
        for (int c=0; c<40; c++) {
            int cycle = 40*r + c + 1;
            if (vals[cycle] - 1 <= c && c <= vals[cycle] + 1)
                cout << '#';
            else
                cout << ' ';
        }
        cout << '\n';
    }
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
