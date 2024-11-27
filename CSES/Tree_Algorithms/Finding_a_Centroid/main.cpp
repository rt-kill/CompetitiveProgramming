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

vi des;
void dfs0(int r=0, int p=-1) {
    des[r] = 1;
    each(c, t[r]) {
        if (c == p) continue;
        dfs0(c, r);
        des[r] += des[c];
    }
}


int dfs1(int r=0) {
    int mc = -1, md = 0;
    each(c, t[r]) if (des[c] > md)
        mc = c, md = des[c];
    if (md <= n/2) return r;

    des[r] -= des[mc];
    des[mc] += des[r];
    return dfs1(mc);
}



void solve() {
    cin >> n;
    t.rsz(n);
    rep(n-1) {
        int a, b; cin >> a >> b; --a, --b;
        t[a].pb(b); t[b].pb(a);
    }

    des.rsz(n); dfs0();
    int res = dfs1() + 1;
    cout << res << '\n';
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
