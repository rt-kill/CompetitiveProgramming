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
/* }}} */

int n, m;
vvii g;

vi deg;/*{{{*/
bool even_degrees() {
    deg.rsz(n);
    int oc = transform_reduce(all(g), 0, plus{}, [](auto &c){ return (c.size() & 1); });
    return (oc == 0);
}/*}}}*/

vi s1;/*{{{*/
void aux_ic(int u=0) {
    if (s1[u]) return;
    s1[u] = 1;

    for(auto [v, _] : g[u])
        aux_ic(v);
}

bool ic() {
    s1.rsz(n);
    aux_ic();
    return transform_reduce(all(g), 1, logical_and{}, [](auto &c){ return ( (c.size() == 0) || s1[c.back().fi] ); });
}/*}}}*/

vi taken;

int go_next(int u) {
    while(g[u].size() > 0) {
        auto [v, i] = g[u].back(); g[u].pop_back();
        if (taken[i]) continue;

        taken[i] = 1;
        return v;
    }

    return -1;
}

void solve() {
    cin >> n >> m;
    g.rsz(n), deg.rsz(n);

    For(i, 0, m) {
        int a, b;
        cin >> a >> b;
        a--, b--;

        g[a].pb({b, i});
        g[b].pb({a, i});
    }

    bool exists = ic() && even_degrees();

    if (!exists) {
        cout << "IMPOSSIBLE" << '\n';
        return;
    }

    taken.rsz(m);

    // If possible, avoid vertices in avoid
    list<int> res = { 0 };
    auto it = res.begin();

    while(it != res.end()) {
        auto tmp = it;

        int start = *it;
        int cur = go_next(start);

        if (cur >= 0) {
            ++it;

            res.emplace(it, cur);
            while(cur != start) {
                cur = go_next(cur);
                res.emplace(it, cur);
            }
        }

        it = ++tmp;
    }

    for (auto u : res) cout << (u+1) << ' ';
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
