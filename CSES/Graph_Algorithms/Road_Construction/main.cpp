#include <bits/stdc++.h>
using namespace std;

/* Macros {{{ */
using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using vi = vector<int>;
using vii = vector<ii>;
using vvi = vector<vi>;

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

int mc = 1, cmp;
vi uf, siz;

int gp(int a) {
    if (a != uf[a])
        uf[a] = gp(uf[a]);
    return uf[a];
}

void merge(int a, int b) {
    int l = gp(a), r = gp(b);
    if (l == r) return;
    if (siz[l] < siz[r]) {
        uf[l] = r;
        siz[r] += siz[l];
    } else {
        uf[r] = l;
        siz[l] += siz[r];
    }
    mc = max(mc, max(siz[l], siz[r]));
    --cmp;
}

int n, m;
void solve() {
    cin >> n >> m;
    cmp = n;

    uf.rsz(n+1);
    iota(uf.begin(), uf.end(), 0);
    siz = vi(n+1, 1);

    rep(m) {
        int a, b;
        cin >> a >> b;
        merge(a, b);
        cout << cmp << ' ' << mc << '\n';
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
