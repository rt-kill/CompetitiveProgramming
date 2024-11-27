#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ar array

int n;
char c;
string s;

int memory[int(2e5)+9];
int dp(int i) {
    if (i >= n) return dp(0);
    if (s[i] == 'g') return 0;

    if (memory[i] == -1) memory[i] = 1 + dp(i+1);
    return memory[i];
}

void solve() {
    cin >> n >> c;
    cin >> s;

    fill(memory, memory + n + 2, -1);

    int res = 0;
    for (int i=0; i<n;i++)
        if (s[i] == c)
            res = max(res, dp(i));

    cout << res << '\n';
}

int main() {
    int t; cin >> t;
    for (int i = 0; i < t; i++)
        solve();

    return 0;
}
