#include <bits/stdc++.h>
using namespace std;

/* Macros {{{ */
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ii = pair<int,int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvll = vector<vll>;
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
vvi tmp_t, t;
vi e;

void dfs0(int r=1, int p=0) {
    e[r] = p, t[p].pb(r);
    each(c, tmp_t[r]) if (c != p)
        dfs0(c, r);
}


void solve() {

    // root the tree
    // relable vertices in bfs order (lowest value vertex has always a leaf)
    // store paths in pq by { node, pid }
    //  TLE: Worst case O(n^2) since graph is not balanced

    cin >> n >> m;
    t.rsz(n+1), tmp_t.rsz(n+1), e.rsz(n+1);
    rep(n-1) {
        int a, b; cin >> a >> b;
        tmp_t[a].pb(b);
        tmp_t[b].pb(a);
    }
    dfs0();

    vi p(n+1), ip(n+1);
    int count = 1;
    queue<int> q({1});
    while(q.size()) {
        int r = q.front(); q.pop();
        p[r] = count, ip[count] = r;
        ++count;
        each(c, t[r]) q.push(c);
    }

    priority_queue<ii> pq;
    For(i, 0, m) {
        int a, b; cin >> a >> b;
        pq.push({ p[a], i });
        pq.push({ p[b], i });
    }

    vi res(n+1), idc(m);
    while(pq.size()) {
        auto l = pq.top().fi;

        stack<int> stak;
        while(pq.size() && l == pq.top().fi) {
            auto id = pq.top().se; pq.pop();
            if (idc[id]++ == 0) stak.push(id);
        }

        while(stak.size()) {
            auto id = stak.top(); stak.pop();
            ++res[ip[l]];
            if (idc[id] == 1) pq.push({ p[e[ip[l]]], id });
            idc[id] = 0;
        }
    }

    For(i, 1, n+1) cout << res[i] << ' ';
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
