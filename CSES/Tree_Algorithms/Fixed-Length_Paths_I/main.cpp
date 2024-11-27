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

#define re(a) cin >> a;
#define rei(a) int a; re(a);
#define re2i(a, b) int a, b; re(a); re(b);
#define reii(a) ii a; re(a.fi); re(a.se);
#define rell(a) ll a; re(a);
#define revi(a, b) vi a(b); each(c, a) re(c);
#define revll(a, b) vll a(b); each(c, a) re(c);
#define revii(a, b) vii a(b); each(c, a) re(c.fi), re(c.se);
/* }}} */

int n, k;
vvi t;
vi used;

vi des;
void dfs0(int r=0, int p=-1) {
    des[r] = 1;
    each(c, t[r]) {
        if (c == p) continue;
        dfs0(c, r);
        des[r] += des[c];
    }
}

int find_centroid(int r, int N) {
    int mc = -1, md = 0;
    each(c, t[r]) {
        if (used[c]) continue;
        if (md < des[c]) {
            md = des[c];
            mc = c;
        }
    }

    if (md <= N/2) return r;

    des[r] -= md;
    des[mc] += des[r];
    return find_centroid(mc, N);
}

vvi levels;
vi lp;
void build_levels(int r, int p) {
    levels[r].clear();

    queue<ii> q({{r, 0}});
    lp[r] = p;

    while(q.sz) {
        auto [ c, d ] = q.front(); q.pop();
        if (d >= k) break;

        if (levels[r].sz <= d) levels[r].pb(0);
        ++levels[r][d];

        each(nc, t[c]) {
            if (used[nc] || lp[nc] == p) continue;
            lp[nc] = p;
            q.push({nc, d+1});
        }
    }
}

ll rec(int r=0) {
    int cent = find_centroid(r, des[r]);
    r = cent;

    used[r] = 1;

    vi lsums;
    each(c, t[r]) {
        if (used[c]) continue;
        build_levels(c, r);
        For(i, 0, levels[c].sz) {
            if (lsums.sz <= i) lsums.pb(0);
            lsums[i] += levels[c][i];
        }
    }

    ll res = 0;
    each(c, t[r]) {
        if (used[c]) continue;
        For(i, 0, levels[c].sz) {
            ll heads = levels[c][i];

            int od = k - 2 - i;
            ll tails;

            if (od < -1) tails = 0;
            else if (od == -1) tails = 2; // Since we divide by 2 at the end
            else if (od >= 0) tails = ((od < lsums.sz) ? lsums[od] : 0) - ((od < levels[c].sz) ? levels[c][od] : 0);

            res += heads*tails;
        }
    }
    res /= 2; // we count each (head, tail) pair twice

    each(c, t[r]) {
        if (used[c]) continue;
        res += rec(c);
    }

    return res;
}



void solve() {
    cin >> n >> k;
    t.rsz(n), used.rsz(n), levels.rsz(n), lp.assign(n, -1);
    For(i, 0, n-1) {
        re2i(a, b); --a, --b;
        t[a].pb(b);
        t[b].pb(a);
    }

    des.rsz(n); dfs0();

    ll res = rec();
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
