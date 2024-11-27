#include <bits/stdc++.h>
using namespace std;

/* Macros {{{ */
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ii = pair<int,int>;
using vi = vector<int>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvii = vector<vii>;

#define arr array
#define ve vector
#define pb push_back
#define rsz(a) resize(a)
#define mp make_pair
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define sz size()

#define For(i, a, b) for(int i=a; i<b; ++i)
#define Rof(i, a, b) for(int i = (b)-1; i >= (a); --i)
#define rep(a) For(_, 0, a)
#define each(a, x) for (auto &a : x)
#define reach(a, x) for (auto a = x.rbegin(); a != x.rend(); ++a)
/* }}} */

int n;
vvi tree;

vi res; // maximal matching in subtree
void dfs(int u=0, int p=0) {
    int r1 = 0; // dont include an edge adjacent to u
    int r2 = 0; // include some edge adjacent to u
    for(auto c : tree[u]) {
        if (c == p) continue;

        dfs(c, u);
        r1 += res[c];
    }
    for(auto c : tree[u]) {
        if (c == p) continue;

        int tmp = 1 + r1 - res[c];
        for(auto c2 : tree[c]) {
            tmp += res[c2];
        }

        r2 = max(r2, tmp);
    }

    res[u] = max(r1, r2);
}

void solve() {
    cin >> n;
    tree.resize(n);
    res.resize(n);

    rep(n-1) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        tree[a].pb(b);
        tree[b].pb(a);
    }

    // we can arbitrarily root the tree at node 0
    dfs();
    cout << res[0] << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
    // you should actually read the stuff at the bottom
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
