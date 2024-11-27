#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// Union Find
// Each value is mapped to its parrent
// Parent values are mapped to themselfs
// Operations:
//  Get Parent
//  Same Set
//  Union

vector<int> uf;
vector<int> ss;

int get_rep(int a) {
    if (uf[a] == a) return a;
    uf[a] = get_rep(uf[a]);
    return uf[a];
}

void merge(int a, int b) {
    int l=get_rep(a), r=get_rep(b);
    if (l == r) return;

    if (ss[l] < ss[r])
        uf[l] = r, ss[r] += ss[l];
    else
        uf[r] = l, ss[l] += ss[r];
}

int n, m;
void solve() {
    cin >> n >> m;

    uf.resize(n+1);
    iota(uf.begin(), uf.end(), 0);
    ss = vector<int>(n+1, 1);

    for(int i=0; i<m; ++i) {
        int a, b;
        cin >> a >> b;
        merge(a, b);
    }

    vector<int> reps;
    for(int i=1; i<=n; ++i)
        if (uf[i] == i) reps.push_back(i);

    cout << reps.size() - 1 << '\n';
    adjacent_difference(reps.begin(), reps.end(), reps.begin(), [](auto l, auto r) { cout << l << ' ' << r << '\n'; return l; } );
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
