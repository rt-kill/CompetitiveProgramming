#include <bits/stdc++.h>

#define st string
#define pb push_back
#define no cout << "NO" << endl;
#define yes cout << "YES" << endl;
#define vec vector
#define len length()
#define all(a) a.begin(), a.end()
#define ff first
#define ss second
#define ll long long

using namespace std;
using vl = vec<int>;
using vi = vec<int>;
using vvi = vec<vi>;
using pi = pair<int, int>;
using vpi = vec<pi>;
using vvvi = vec<vvi>;
using vvpi = vec<vec<pi>>;
using vvvpi = vec<vvpi>;
using vvvvi = vec<vvvi>;
using vppi = vec<pair<pair<int, int>, pair<int, int>>>;

struct Node {
    ll mn = 0;
    ll add = 0;
};

vec<Node> tree;

void push(int v, int tl, int tr) {
    if (tr - tl == 1 || !tree[v].add) {
        return;
    }
    ll x = tree[v].add;
    tree[2 * v + 1].mn += x;
    tree[2 * v + 2].mn += x;
    tree[2 * v + 1].add += x;
    tree[2 * v + 2].add += x;
    tree[v].add = 0;
}

void update(int v, int tl, int tr, int l, int r, ll add) {
//    cout << tl << " " << tr << " " << (tl + tr) / 2 << endl;
    push(v, tl, tr);
    if (tl >= r || tr <= l) {
//        cout << "dora" << endl;
//        cout << 111 << " " << tl << " " << tr << " " << v << " " << tree[v].sum << " " << tree[v].mn << " " << l << " " << r << endl;
        return;
    }
    if (tl >= l && tr <= r) {
        tree[v].mn += add;
        tree[v].add += add;
//        cout << "dora" << endl;
//        cout << tl << " " << tr << " " << v << " " << tree[v].sum << " " << tree[v].mn << " " << l << " " << r << endl;
        return;
    }
    int m = (tl + tr) / 2;
    update(2 * v + 1, tl, m, l, r, add);
    update(2 * v + 2, m, tr, l, r, add);
    tree[v].mn = min(tree[2 * v + 1].mn, tree[2 * v + 2].mn);
}

ll get(int v, int tl, int tr, int l, int r) {
    push(v, tl, tr);
    if (tl >= r || tr <= l) {
        return (ll) 1e15;
    }
    if (tl >= l && tr <= r) {
        return tree[v].mn;
    }
    int m = (tl + tr) / 2;
    ll ans1 = get(2 * v + 1, tl, m, l, r);
    ll ans2 = get(2 * v + 2, m, tr, l, r);
    return min(ans1, ans2);
}

void solve() {
    int n, k; cin >> n >> k;

    int kk = 1;
    while (kk < k) {
        kk *= 2;
    }
    tree.resize(2 * kk - 1);

    vi a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }
    vi cold(k);
    for (int i = 0; i < k; i++) cin >> cold[i];
    vi hot(k);
    for (int i = 0; i < k; i++) cin >> hot[i];
    vi used(k, 0);
    update(0, 0, k, 0, k + 1, cold[a[0]]);
    used[a[0]] = 1;

    for (int i = 1; i < n; i++) {
        int last = a[i - 1];
        if (last == a[i]) {
            update(0, 0, k, 0, k + 1, hot[a[i]]);
        }
        else {
            ll dpj = get(0, 0, k, a[i], a[i] + 1);
            update(0, 0, k, 0, k, cold[a[i]]);
            if (used[a[i]]) {
                update(0, 0, k, a[i], a[i] + 1, (hot[a[i]] - cold[a[i]]));
            }
            ll now = get(0, 0, k, last, last + 1);
            ll c = now;
            now = min(now, get(0, 0, k, 0, k));
            if (used[a[i]]) {
                now = min(now, dpj + hot[a[i]]);
            }
            update(0, 0, k, last, last + 1, now - c);
        }

        used[a[i]] = 1;
    }

    cout << get(0, 0, k, 0, k) << endl;
    tree = {};
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    //freopen("input.csv", "r", stdin);
    //freopen("output.txt", "w", stdout);
    int tt = 1;
    cin >> tt;
    while (tt--) {
        solve();
    }
}
