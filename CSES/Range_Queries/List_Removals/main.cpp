#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n;
vector<int> x;

vector<int> bit;
vector<bool> removed;

void init_bit() {
    bit = vector<int>(n+1, 0);
    removed = vector<bool>(n+1, 0);
}

void update_query(int i) {
    if (removed[i]) return;

    removed[i] = 1;
    for(int j=i; j<=n; j+=(j & -j))
        bit[j] += 1;
}

int sum_query(int i) {
    int res = 0;
    for(int j=i-1; j>0; j-=(j&-j))
        res += bit[j];
    return res;
}

void print_bit() {
    for(auto v : bit) cout << v << ' ';
    cout << '\n';
}

void solve() {
    cin >> n;

    x.resize(n+1); x[0] = 0;
    for(int i=1; i<=n; i++)
        cin >> x[i];

    init_bit();

    int p;
    for(int i=1; i<=n; i++) {
        cin >> p;

        int l=1, r=n, m;
        while(l <= r) {
            m = (l + r)/2;
            if (m - sum_query(m) < p) l = m+1;
            else if (m - sum_query(m) > p) r = m-1;
            else if (removed[m]) l = m+1;
            else break;
        }

        cout << x[m] << '\n';

        update_query(m);
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
