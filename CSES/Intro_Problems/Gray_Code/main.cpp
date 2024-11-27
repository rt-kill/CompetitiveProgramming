#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n;

vector<bool> cur;
void print_cur() {
    for(auto v : cur) cout << v;
    cout << '\n';
}

void solve() {
    cin >> n;
    cur.resize(n);

    print_cur();
    for(int i=1; i<(1<<n); i++) {
        int bit = __builtin_ctz(i&-i);
        cur[bit] = cur[bit] ^ 1;
        print_cur();
    }
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
