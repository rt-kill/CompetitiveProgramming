#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int good_order(string l, string r) {
    if (l[0] != '[' && r[0] == '[')
        l = '[' + l + ']';
    else if (l[0] == '[' && r[0] != '[')
        r = '[' + r + ']';
    else if (l[0] != '[' && r[0] != '[') {
        return 2*(stoi(l) < stoi(r)) + (stoi(l) == stoi(r));
    }

    vector<string> left;
    int i=1, j;

    if (l.size() > 2) {
        while (i < l.size()-1) {
            if (l[i] == '[') {
                j = i+1;
                int tmp = 1;
                while(tmp > 0) {
                    tmp += (l[j] == '[') - (l[j] == ']');
                    j++;
                }
            } else
                j = l.find(',', i);

            if (j < 0) j = l.size() - 1;

            left.push_back(l.substr(i, j - i));
            i=j+1;
        }
    }

    vector<string> right;
    i=1;
    if (r.size() > 2) {
        while (i<r.size()-1) {
            if (r[i] == '[') {
                j = i+1;
                int tmp = 1;
                while(tmp > 0) {
                    tmp += (r[j] == '[') - (r[j] == ']');
                    j++;
                }
            } else
                j = r.find(',', i);

            if (j < 0) j = r.size() - 1;

            right.push_back(r.substr(i, j - i));
            i=j+1;
        }
    }

    i = 0;
    while(i < left.size() && i < right.size()) {
        int tmp = good_order(left[i], right[i]);
        if (tmp == 0) return 0;
        if (tmp == 2) return 2;
        i++;
    }

    return 2*(left.size() < right.size()) + (left.size() == right.size());
}

void solve() {
    vector<array<string, 2>> pac;
    pac.push_back({"", ""});

    string line;
    while (true) {
        getline(std::cin, line);
        if (line.empty()) break;

        string tmp[2];
        tmp[0] = line;
        getline(std::cin, line);
        tmp[1] = line;

        pac.push_back({ tmp[0], tmp[1] });

        getline(std::cin, line);
    }

    int res1=0;
    for(int i=1; i< pac.size(); i++) {
        int tmp = good_order(pac[i][0], pac[i][1]);

        /* cout << "STARTING " << i << '\n'; */
        /* if (tmp == 0) cout << "BAD" << '\n'; */
        /* if (tmp == 1) cout << "IDK" << '\n'; */
        /* if (tmp == 2) cout << "GOOD" << '\n'; */
        /* cout << "ENDING" << '\n'; */

        res1 += i*(tmp == 2);
    }

    cout << res1 << '\n';

    string d1 = "[[2]]";
    int i1 = 1;
    string d2 = "[[6]]";
    int i2 = 2;

    int tmp;
    for(int i=1; i< pac.size(); i++) {
        tmp = good_order(pac[i][0], d1); // does pac[i][0] come before d1
        i1 += (tmp == 2);
        tmp = good_order(pac[i][1], d1); // does pac[i][1] come before d1
        i1 += (tmp == 2);
        tmp = good_order(pac[i][0], d2); // does pac[i][0] come before d2
        i2 += (tmp == 2);
        tmp = good_order(pac[i][1], d2); // does pac[i][1] come before d2
        i2 += (tmp == 2);

        /* cout << "STARTING " << i << '\n'; */
        /* if (tmp == 0) cout << "BAD" << '\n'; */
        /* if (tmp == 1) cout << "IDK" << '\n'; */
        /* if (tmp == 2) cout << "GOOD" << '\n'; */
        /* cout << "ENDING" << '\n'; */
    }

    int res2 = i1 * i2;
    cout << res2 << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
