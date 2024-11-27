#include <bits/stdc++.h>
using namespace std;

/* Macros {{{ */
using ll = long long;
using ull = unsigned long long;
using ii = pair<int,int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvii = vector<vii>;

#define arr array
#define ve vector
#define pb push_back
#define re(a) resize(a)
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

int n, m;
vvii g;
ll const M = 1e9 + 7;

vll mr;
vll counts;
vll msm, mmm;

priority_queue<arr<ll, 4>, vector<arr<ll, 4>>, greater<arr<ll, 4>>> pq;

void solve() {
    cin >> n >> m;
    g.re(n+1);
    rep(m) {
        int a, b ,c;
        cin >> a >> b >> c;
        g[a].pb({b, c});
    }

    mr = vll(n+1, -1);
    counts.re(n+1), counts[0] = 1;
    msm = vll(n+1, INT_MAX), mmm = vll(n+1, -1);
    msm[0] = -1; mmm[0] = -1;
    pq.push({ 0, 1, 0, 0 });

    while(pq.size()) {
        if (pq.top()[1] == n) break;
        auto [ c, u, f, from ] = pq.top(); pq.pop();

        if (mr[u] == c){
            counts[u] = (counts[u] + counts[from])%M;
            msm[u] = min(msm[u], msm[from] + 1);
            mmm[u] = max(mmm[u], mmm[from] + 1);
        }

        if (mr[u] >= 0) continue;

        mr[u] = c;

        counts[u] = (counts[u] + counts[from])%M;
        msm[u] = min(msm[u], msm[from] + 1);
        mmm[u] = max(mmm[u], mmm[from] + 1);


        for(auto [ v, w ] : g[u]) {
            pq.push({ c + w, v, f + 1, u });
        }
    }

    ll p=pq.top()[0];
    while(pq.size() && pq.top()[1] == n && pq.top()[0] == p) {
        auto [ c, u, f, from ] = pq.top(); pq.pop();
        msm[n] = min(msm[n], msm[from] + 1);
        mmm[n] = max(mmm[n], mmm[from] + 1);
        counts[n] = (counts[n] + counts[from])%M;
    }

    cout << p << ' ' << counts[n] << ' ' << msm[n] << ' ' << mmm[n] << '\n';
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
