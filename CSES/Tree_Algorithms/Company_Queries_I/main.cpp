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

int n, q;
vi e;

vvi sp;
void pop_sparse() {
    int p = 0;
    while((1 << p) <= n) ++p;

    sp.assign(n, vi(p));

    For(i, 0, n) sp[i][0] = e[i];
    For(j, 1, p) For(i, 0, n)
        sp[i][j] = (sp[i][j-1] >= 0) ? sp[sp[i][j-1]][j-1] : -2;
}

int query_sparse(int x, int k) {
    /* cout << x << ' ' << k << '\n'; */
    while(k > 0) {
        /* cout << ( k & -k ) << '\n'; */
        x = (x >= 0) ? sp[x][__builtin_ctz( k & -k )] : x;
        k -= (k & -k);
    }

    return x;
}

void solve() {
    cin >> n >> q;

    e.rsz(n);
    e[0] = -2;
    For(i, 1, n) {
        int tmp; cin >> tmp; --tmp;
        e[i] = tmp;
    }

    pop_sparse();
    rep(q) {
        int x, k;
        cin >> x >> k;
        --x;
        cout << query_sparse(x, k) + 1 << '\n';
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
