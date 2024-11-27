#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = i+1;
    }
    int win, lose, win_index, lose_index;
    vector<int> b = a;
    for (int i = 0; i < m; i++) {
        cin >> win >> lose;
        win_index = a.find(win);
        lose_index = a.find(lose);
        if (win_index < lose_index) {
            for (int j = 0; j < n; j++) {

            }
        }
    }
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
