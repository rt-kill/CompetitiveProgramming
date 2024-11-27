#include <bits/stdc++.h>
using namespace std;

using ll = long long;

string line;
void solve() {
    vector<deque<char>> crates(10, deque<char>());

    while(true) {
        getline(cin, line);
        if (line[0] != '[') break;
        for(int i=1; i<line.size();i+=4) {
            if (line[i] != ' ') {
                crates[(i-1)/4 + 1].push_front(line[i]);
            }
        }
    }

    /* for (auto c : crates) { */
    /*     for (auto w : c) */
    /*         cout << w << ' '; */
    /*     cout << '\n'; */
    /* } */

    getline(cin, line);

    string tmp;
    while(true) {
        getline(cin, tmp, ' ');
        cout << tmp << '\n';
        if (tmp.empty()) break;
        getline(cin, tmp, ' ');
        cout << tmp << '\n';
        int a = stoi(tmp);
        getline(cin, tmp, ' ');
        cout << tmp << '\n';
        getline(cin, tmp, ' ');
        cout << tmp << '\n';
        int f = stoi(tmp);
        getline(cin, tmp, ' ');
        cout << tmp << '\n';
        getline(cin, tmp);
        cout << tmp << '\n';
        int t = stoi(tmp);

        int c=0;
        deque<char> tmp;
        while(!crates[f].empty() && c++<a) {
            tmp.push_front(crates[f].back());
            crates[f].pop_back();
        }
        for(auto i : tmp)
            crates[t].push_back(i);
    }

    for(auto t : crates) {
        cout << t.size() << ' ';
        if (t.size() > 0) cout << t.back();
        cout << '\n';
    }
    cout << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
