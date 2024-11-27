#include <bits/stdc++.h>
using namespace std;

using ll = long long;
vector<vector<int>> mymap;
vector<vector<bool>> visible;

vector<vector<int>> memory[4];

string line;
void solve() {
    while (true) {
        getline(std::cin, line);
        if(line.empty()) break;
        mymap.push_back(vector<int>());
        visible.push_back(vector<bool>());
        for(char c : line)
            mymap.back().push_back(c - '0');

        visible.back().resize(mymap.back().size());
        fill(visible.back().begin(), visible.back().end(), false);
    }

    for (int r=0; r<visible.size(); r++) {
        int lrg = -1;
        for(int j = 0; j < visible[0].size(); j++) {
            if (mymap[r][j] > lrg) {
                visible[r][j] = true;
                lrg = mymap[r][j];
            }
        }

        lrg = -1;
        for(int j = visible[0].size()-1; j >= 0; j--) {
            if (mymap[r][j] > lrg) {
                visible[r][j] = true;
                lrg = mymap[r][j];
            }
        }
    }

    for (int c=0; c<visible[0].size(); c++) {
        int lrg = -1;
        for(int r = 0; r < visible.size(); r++) {
            if (mymap[r][c] > lrg) {
                visible[r][c] = true;
                lrg = mymap[r][c];
            }
        }

        lrg = -1;
        for(int r = visible.size()-1; r >= 0; r--) {
            if (mymap[r][c] > lrg) {
                visible[r][c] = true;
                lrg = mymap[r][c];
            }
        }
    }

    int res = 0;
    for (auto row : visible) {
        for (auto square : row) {
            res += square;
        }
    }

    cout << res << '\n';


    fill(memory, memory+4, vector<vector<int>>(mymap.size(), vector<int>(mymap[0].size(), 0)));

    int tmp[10];
    for(int r=0; r<mymap.size(); r++) {
        fill(tmp, tmp + 10, 0);
        for(int c=0; c<mymap[r].size(); c++) {
            int last_visible_loc = *max_element(tmp + mymap[r][c], tmp + 10);

            memory[0][r][c] = c - last_visible_loc;
            tmp[mymap[r][c]] = c;
        }

        fill(tmp, tmp + 10, mymap[r].size()-1);
        for(int c=mymap[r].size() - 1; c>=0; c--) {
            int last_visible_loc = *min_element(tmp + mymap[r][c], tmp + 10);

            memory[1][r][c] = last_visible_loc - c;
            tmp[mymap[r][c]] = c;
        }
    }

    for(int c=0; c<mymap[0].size(); c++) {
        fill(tmp, tmp + 10, 0);
        for(int r=0; r<mymap.size(); r++) {
            int last_visible_loc = *max_element(tmp + mymap[r][c], tmp + 10);

            memory[2][r][c] = r - last_visible_loc;
            tmp[mymap[r][c]] = r;
        }

        fill(tmp, tmp + 10, mymap.size()-1);
        for(int r=mymap.size() - 1; r>=0; r--) {
            int last_visible_loc = *min_element(tmp + mymap[r][c], tmp + 10);

            memory[3][r][c] = last_visible_loc - r;
            tmp[mymap[r][c]] = r;
        }
    }

    int res2 = 0;
    for(int r=0; r<mymap.size(); r++)
        for(int c=0; c<mymap[0].size(); c++) {
            res2 = max(res2,  memory[0][r][c] * memory[1][r][c] * memory[2][r][c] * memory[3][r][c]);
        }

    cout << res2 << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
