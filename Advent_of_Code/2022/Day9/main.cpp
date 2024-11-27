#include <bits/stdc++.h>
using namespace std;

using ll = long long;
map<char, pair<int, int>> dirs = { { 'U', {1, 0} }, { 'D', {-1, 0} }, { 'L', {0, -1} }, { 'R', {0, 1} } };

set<pair<int, int>> seen;

void solve() {
    /* string line; */
    /* int hr=0, hc=0, tr=0, tc=0; */
    /* seen.insert({ tr, tc }); */

    /* while (true) { */
    /*     getline(std::cin, line); */
    /*     if (line.empty()) break; */

    /*     char dir = line[0]; */
    /*     int a = stoi(line.substr(2)); */

    /*     auto [dr, dc] = dirs[dir]; */
    /*     for(int i=0; i<a; i++) { */
    /*         hr += dr, hc += dc; */
    /*         if (abs(hr - tr) > 1 || abs(hc - tc) > 1) { */
    /*             tr = hr - dr, tc = hc - dc; */
    /*         } */

    /*         cout << hr << ' ' << hc << "  -  " << tr << ' ' << tc << '\n'; */
    /*         seen.insert({ tr, tc }); */
    /*     } */
    /* } */

    /* cout << seen.size() << '\n'; */

    string line;
    vector<pair<int, int>> pos(10, {0, 0});
    seen.insert({0, 0});

    while (true) {
        getline(std::cin, line);
        if (line.empty()) break;

        char dir = line[0];
        int a = stoi(line.substr(2));

        for(int i=0; i<a; i++) {
            auto [dr, dc] = dirs[dir]; // where to move head
            pos[0].first += dr, pos[0].second += dc;

            for(int j=1;j<pos.size();j++) {
                auto [ hr, hc ] = pos[j-1];
                auto [ cr, cc ] = pos[j];
                int dx = hr - cr, dy = hc -  cc;

                bool move = abs(dx) > 1 || abs(dy) > 1;
                if (move) {
                    pos[j].first += ((dx > 0) - (dx < 0)), pos[j].second += ((dy > 0) - (dy < 0));
                    if (j == 9) seen.insert(pos[9]);
                }
            }

        }
    }

    for (int r=-25; r<25; r++) {
        for (int c=-25; c<25; c++) {
            if (r == 0 && c == 0) cout << 'S';
            else if (seen.count({r, c}) ) cout << '#';
            else cout << '.';
        }
        cout << '\n';
    }

    cout << seen.size() << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
