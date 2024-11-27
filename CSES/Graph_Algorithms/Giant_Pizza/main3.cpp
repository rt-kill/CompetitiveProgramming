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
vvi g;
vi res;

void solve() {
    cin >> n >> m;
    g.rsz(2*m);
    For(i, 0, m) g[i].pb(i+m), g[i+m].pb(i);

    rep(n) {
        char s1, s2; int t1, t2;
        cin >> s1 >> t1 >> s2 >> t2;
        t1--, t2--;

        t1 += m * (s1 == '+');
        t2 += m * (s2 == '+');

        g[t1].pb(t2);
        g[t2].pb(t1);
    }

    For(i, 0, 2*m) {
        cout << "GRAPH: "<< i << '\n';
        each(u, g[i]) cout << u << ' ';
        cout << '\n';
    }

    res = vi(2*m, -1);
    For(i, 0, m) {
        if (res[i] < 0) {
            queue<ii> q; q.push({ i, 0 });
            while(q.size()) {
                auto [ u, b ] = q.front(); q.pop();
                if (res[u] >= 0) {
                    if ((res[u] + b) & 1) {
                        cout << "IMPOSSIBLE" << '\n';
                        return;
                    }
                    continue;
                }

                res[u] = b;
                for(auto v : g[u])
                    q.push({ v, b^1 });
            }
        }
    }

    For(i, 0, m) cout << ( (res[i]) ? '+' : '-' ) << ' ';
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
