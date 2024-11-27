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

int n;
vvi t;

vi nc;
void dfs1(int r=0, int p=-1) {
    nc[r] = 1;
    for(auto c : t[r]) {
        if (c == p) continue;
        dfs1(c, r);
        nc[r] += nc[c];
    }
}

vll res;
void dfs2(int r=0, int p=-1) {
    res[r] = 0;
    for(auto c : t[r]) {
        if (c == p) continue;
        dfs2(c, r);
        res[r] += res[c] + nc[c];
    }
}

void dfs3(int r=0, int p=-1) {
    if (p >= 0) res[r] = (res[p] - nc[r] + (n - nc[r]));

    for(auto c : t[r]) {
        if (c == p) continue;
        dfs3(c, r);
    }
}


void solve() {
    cin >> n;
    t.rsz(n), nc.rsz(n), res.rsz(n);
    rep(n-1) {
        int a, b;
        cin >> a >> b;
        t[a-1].pb(b-1);
        t[b-1].pb(a-1);
    }

    dfs1(), dfs2(), dfs3();
    for(auto v : res) cout << v << ' ';
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
