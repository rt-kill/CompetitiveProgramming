#include <bits/stdc++.h>
using namespace std;

using ll = long long;

string input;
void solve() {
    cin >> input;
    deque<char> lastFour; int i=0;
    while(true) {
        set<char> tmp(lastFour.begin(), lastFour.end());
        if (tmp.size() == 14)
            break;
        lastFour.push_back(input[i++]);
        while(lastFour.size() > 14)
            lastFour.pop_front();
    }

    cout << i << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
