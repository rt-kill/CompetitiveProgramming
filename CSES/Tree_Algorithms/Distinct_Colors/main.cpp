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

int const N = 2e5 + 5;
int n;
vi c;
vvi t;
vi res;

vi parr, siz;
ve<set<int>> colors;
void init_ds() {
    parr.rsz(n+1), siz.assign(n+1, 1);
    iota(all(parr), 0);

    colors.rsz(n+1);
    For(i, 1, n+1) colors[i].insert(c[i]);
}

int get_rep(int r) {
    while(parr[parr[r]] != parr[r])
        parr[r] = get_rep(parr[r]);
    return parr[r];
}

void merge(int a, int b) {
    int r1 = get_rep(a), r2 = get_rep(b);
    if (r1 == r2) return;
    if (siz[r1] < siz[r2]) swap(r1, r2);
    if (colors[r1].sz < colors[r2].sz) swap(colors[r1], colors[r2]);

    parr[r2] = r1;
    for(auto col : colors[r2])
        colors[r1].insert(col);
}

void dfs(int r=1, int p=-1) {
    for(auto c : t[r]) {
        if (c == p) continue;
        dfs(c, r);
        merge(c, r);
    }

    res[r] = colors[get_rep(r)].sz;
}

void solve() {
    cin >> n;
    c.rsz(n+1);
    For(i, 1, n+1) cin >> c[i];

    t.rsz(n+1);
    rep(n-1) {
        int a, b;
        cin >> a >> b;
        t[a].pb(b);
        t[b].pb(a);
    }
    res.rsz(n+1);

    init_ds();
    dfs();
    For(i, 1, n+1) cout << res[i] << ' ';
    cout << '\n';

    // Maintain disjoint set
    //  DFS: Run rec on all children
    //  Put all children into the same set
    //  Union their colors

    // Worst case is when every node has a unique color
    //  I will do a total of (n-1) unions
    //  Worst case is whenever I do a union, the size of the sets are roughly the same
    //      Consider some arbitrary color
    //      Whenever it is moved to a new set, the size of the set it is in doubles
    //      This color will be moved at most log(n) times
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
