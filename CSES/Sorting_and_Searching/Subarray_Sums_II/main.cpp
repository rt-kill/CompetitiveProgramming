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

// #define re(a) cin >> a;
// #define rei(a) int a; re(a);
// #define reii(a) ii a; re(a.fi); re(a.se);
// #define rell(a) ll a; re(a);
// #define revi(a, b) vi a(b); each(c, a) re(c);
// #define revll(a, b) vll a(b); each(c, a) re(c);
// #define revii(a, b) vii a(b); each(c, a) re(c.fi), re(c.se);
/* }}} */

int n, x;
vll a;
void solve() {
    cin >> n >> x;
    a.rsz(n+1);
    For(i, 1, n+1) cin >> a[i];
    partial_sum(all(a), a.begin());

    ll res = 0;
    map<ll, ll> ms;
    Rof(i, 0, n+1) {
        auto it = ms.lower_bound(a[i] + x);
        if (it != ms.end() && (*it).fi == a[i] + x) {
            res += (*it).se;
        }
        ++ms[a[i]];
    }
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
