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

int n, m;
vvi g;
vi in, out;

vi seen;
bool can_reach(int u=1) {
    if (seen[u]) return 0;
    seen[u] = 1;

    if (u == n) return 1;

    bool r = 0;
    for(auto v : g[u])
        r = r || can_reach(v);

    return r;
}

vi res;
void dfs(int u=1) {
    while(g[u].size()) {
        int v = g[u].back(); g[u].pop_back();
        dfs(v);
    }

    res.pb(u);
}

void solve() {
    cin >> n >> m;
    g.rsz(n+1), in.rsz(n+1), out.rsz(n+1);

    rep(m) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
        ++in[b], ++out[a];
    }

    g[n].pb(1);
    ++in[1], ++out[n];

    int oc = transform_reduce(all(in), out.begin(), 1, logical_and{}, [](int l, int r){return l == r;});
    seen.rsz(n+1);
    int cr = can_reach();

    if (!oc || !cr) {
        cout << "IMPOSSIBLE" << '\n';
        return;
    }

    dfs();

    if (res.sz < m+1) {
        cout << "IMPOSSIBLE" << '\n';
        return;
    }
    reverse(all(res));

    For(i, 0, m+1) {
        int j = (i+1)%(m+1);
        if (res[i] == n && res[j] == 1) {
            For(d, 0, m+1) {
                int u = (j + d) % (m+1);
                cout << res[u] << ' ';
            }
            cout << '\n';
            break;
        }
    }
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
