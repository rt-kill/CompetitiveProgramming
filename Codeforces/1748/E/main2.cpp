#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int Ma = int(1e9) + 7;

int t, n, m, a[int(2e5) + 9];

int tree[int(4e5) + 9];
void build_tree(int no, int l, int r) {
    if (l > r) return;
    if (l == r) {
        tr[no] = l;
        return;
    }

    int ms = (l + r)/2;
    build_tree(2*no, l, m);
    build_tree(2*no + 1, m+1, r);

    if (a[tr[2*no]] >= a[tr[2*no + 1]])
        tr[no] = tr[2*no];
    else
        tr[no] = tr[2*no + 1];
}

int query(int l, int r, int no, int ls, int rs) {
    if (l <= ls && rs <= r)
        return tr[no];

    int ms = (ls + rs)/2;

    if (ms >= r)
        return query(l, r, no*2, ls, ms);
    if (ms < l)
        return query(l, r, no*2 + 1, ms+1, rs);

    int left = query(l, ms, no*2, ls, ms);
    int right = query(l, ms+1, no*2 + 1, ms + 1, rs);

    if (a[left] >= a[right])
        return left;
    return right;
}

// although (l, r) can technically have (n choose 2) values, since our divide points are non-dynamic, really its ~2n (nodes on our rec tree)
//  This being said, we are still using divide and concure, so this should run around
map<tuple<int, int, int>, int> memory;
int dp(int l, int r, int M) {
    if (r < l) return 1;
    if (l == r) return M;
    if (M <= 0) return 0;

    tuple<int, int, int> rep = make_tuple(l, r, M);

    if (memory.count(rep) == 0) {
        int cent = query(l, r, 1, 1, n);

        int res = dp(l, r, M - 1);
        res = (res + ((ll(dp(l, cent - 1, M-1)) * ll(dp(cent + 1, r, M))) % Ma)) % Ma;

        memory[rep] = res;

        cout << l << ' ' << r << ' ' << M << " -- " << res << ' ' << cent << '\n';
    }

    return memory[rep];
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    memory.clear();

    build_tree(1, 1, n);
    int res = dp(1, n, m);
    cout << res << '\n';
}

int main() {
    cin >> t;
    for (int i = 0; i < t; i++)
        solve();

    return 0;
}
