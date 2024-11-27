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

// nodes: 2^15 < 4e4
// edges: 2^16 < 7e4

int n;
vvi g;

vi res;
void dfs(int u=0) {
    while(g[u].size()) {
        int v = g[u].back(); g[u].pop_back();
        dfs(v);
    }

    res.pb(u);
}

void solve() {
    cin >> n;

    // we build a graph where each node is some combination of (n-1) bits
    // the current node represents the last (n-1) values of the string
    // edges represent either adding a 0 or a 1 to the end of the string
    //  Each arrangement of n bits is uniquely defined by an edge from some node to another node
    //  Similarly each edge represents some aragement of n bits
    // thus any eulierian trail of this graph (if one exists) is clearly an optimal solution
    //  the graph is clearly connected
    //  every node clearly has in and out degree 2
    //  an eulierian trail (cycle) exists

    if (n == 1) {
        cout << 10 << '\n';
        return;
    }

    int masks = (1 << (n-1));
    g.rsz(masks);

    For(mask, 0, masks) {
        int tmp = (mask << 1) & (~masks);
        g[mask].pb(tmp);
        g[mask].pb(tmp + 1);
    }

    dfs();
    rep(n-2) cout << 0;
    reach(it, res) cout << (*it & 1);
    cout << '\n';
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
