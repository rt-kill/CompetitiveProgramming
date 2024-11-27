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
vvii g;
vii e, eh;

// can I take edge i starting at u
bool can_take(int u, int i) {
    return ( u == e[i].fi ) ? e[i].se <= 0 : e[i].se >= 0;
}

void take(int u, int i) {
    if ( u == e[i].fi ) ++e[i].se;
    else --e[i].se;
}

ii parents[501];
int enqued[501];

bool bp() {
    fill(enqued + 1, enqued + n + 1, 0);
    parents[n] = {-1, -1};

    queue<int> q;
    q.push(1);
    enqued[1] = 1;

    while(q.size()) {
        if (enqued[n]) break;
        int u = q.front(); q.pop();

        for(auto [ v, ei ] : g[u]) {
            if (enqued[v]) continue;
            if (!can_take(u, ei)) continue;

            q.push(v);
            enqued[v] = 1;
            parents[v] = { u, ei };
        }
    }

    return enqued[n];
}

bool augment() {
    int pe = bp();
    if (!pe) return 0;

    int v = n;
    while(v != 1) {
        auto [ u, ei ] = parents[v];
        take(u, ei);
        v = u;
    }

    return 1;
}

set<int> reachable;
vii res;
void pop_res() {
    fill(enqued + 1, enqued + n + 1, 0);

    queue<int> q;
    q.push(1);
    enqued[1] = 1;


    while(q.size()) {
        int u = q.front(); q.pop();
        reachable.insert(u);

        for(auto [ v, ei ] : g[u]) {
            if (enqued[v]) continue;
            if (!can_take(u, ei)) continue;

            q.push(v);
            enqued[v] = 1;
        }
    }

    for(auto [a, b] : eh) {
        bool q1 = reachable.count(a), q2 = reachable.count(b);
        if (q1 ^ q2) res.pb({ a, b });
    }
}

void solve() {
    cin >> n >> m;
    g.rsz(n+1), e.rsz(m), eh.rsz(m);

    For(i, 0, m) {
        int a, b;
        cin >> a >> b;

        eh[i] = {a, b};
        g[a].pb({b, i});
        g[b].pb({a, i});
        e[i] = {a, 0}; // away from a
    }


    while(true) {
        bool tmp = augment();
        if (!tmp) break;
    }


    pop_res();
    cout << res.size() << '\n';
    for(auto [a, b] : res) cout << a << ' ' << b << '\n';

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
