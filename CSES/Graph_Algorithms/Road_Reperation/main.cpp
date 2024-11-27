#include <bits/stdc++.h>
using namespace std;

/* Macros {{{ */
using ll = long long;
using ull = unsigned long long;
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

#define FOR(i, a, b) for(int i=a; i<b; ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for(int i = ( b )-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define rep(a) F0R(_, a)
#define each(a, x) for (auto &a : x)
/* }}} */

int n, m;
vvii g;

vi seen;
priority_queue<ii, vector<ii>, greater<ii>> pq;

void solve() {
    cin >> n >> m;
    g.rsz(n+1);
    rep(m) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].pb({b, c});
        g[b].pb({a, c});
    }

    ll res = 0;
    seen.rsz(n+1);
    pq.push({ 0, 1 });

    while(pq.size()) {
        auto [ c, u ] = pq.top(); pq.pop();

        if (seen[u]) continue;
        seen[u] = 1;
        res += c;

        for(auto [ v, p ] : g[u])
            pq.push({ p, v });
    }

    if ( accumulate(seen.begin() + 1, seen.end(), 1, logical_and{}) ) {
        cout << res << '\n';
    } else {
        cout << "IMPOSSIBLE" << '\n';
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
