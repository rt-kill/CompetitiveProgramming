#include <bits/stdc++.h>
using namespace std;

int n;
int p[int(1e5) + 9];
vector<int> t[int(1e5) + 9];
int d[int(1e5) + 9];

int pop(int r) {
    d[r] = 1;
    for (int c : t[r])
        d[r] = max(d[r], 1 + pop(c));

    return d[r];
}

int dfs(int r) {
    int tmp = 0;
    for (int c : t[r])
        tmp += dfs(c);

    return max(tmp, d[r]);
}

int main() {
    cin >> n;
    for (int i = 2; i <= n; i++) {
        cin >> p[i];
        t[p[i]].push_back(i);
    }

    pop(1);
    cout << dfs(1) << '\n';
}
