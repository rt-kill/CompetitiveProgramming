#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MM = 998244353;
const int N = 2e5 + 1;
ll n, i[N], j[N], x[N], y[N];
vector<tuple<int, map<int, int>, map<int, int>>> c[N];

bool active[N];
map<int, int> val[N];

map<int, int> pf(int q) {
    map<int, int> res;

    for (int p = 2; p*p <= q; p++) {
        if (!(q%p))
            res.emplace(p, 0);
        while (!(q%p))
            res[p] += 1, q/=p;
    }

    if (q > 1)
        res.emplace(q, 1);

    return res;
}

void dfs1(int u) {
    if (active[u]) return; active[u] = 1;

    map<int, int> res;
    int v; map<int, int> px, py;

    for (auto p : c[u]) {
        tie(v, px, py) = p;
        dfs1(v);

        if (active[v]) continue;

        map<int, int> tmp;
        int prime, mult;

        for (auto q : px ) {
            tie(prime, mult) = q;
            tmp.emplace(prime, mult);
        }

        for (auto q : val[v]) {
            tie(prime, mult) = q;
            tmp.emplace(prime, 0);
            tmp[prime] += mult;
        }

        for (auto q : py ) {
            tie(prime, mult) = q;
            tmp.emplace(prime, 0);
            tmp[prime] = max(0, tmp[prime] - mult);
        }

        for (auto q : tmp) {
            tie(prime, mult) = q;
            res.emplace(prime, 0);
            res[prime] = max(res[prime], mult);
        }
    }

    val[u] = res; active[u] = 0;

    // find minimal int res such that for all children v of u
    //  There exists int m such that
    //      res = x[v]/y[v](m*val[v])
    // since we want res to be minimal, we want m to be minimal
    // m will just be the primes in y that are not covered by x or val

    // prime p in res will have multiplicity
    //  max(mult[p](x[v]*val[v]) for child v of u)
    //  = max(mult[p](x[v]) + mult[p](val[v]) for child v of u)
}

void dfs2(int u) {
    if (active[u]) return; active[u] = 1;

    map<int, int> res;
    int v; map<int, int> px, py;

    for (auto p : c[u]) {
        tie(v, px, py) = p;

        if (active[v]) continue;

        map<int, int> cp;
        int prime, mult;

        for (auto q : val[u]) {
            tie(prime, mult) = q;
            cp.emplace(prime, mult);
        }

        for (auto q : py ) {
            tie(prime, mult) = q;
            cp.emplace(prime, 0);
            cp[prime] += mult;
        }

        for (auto q : px ) {
            tie(prime, mult) = q;
            cp.emplace(prime, 0);
            cp[prime] -= mult;
        }

        val[v] = cp;
        dfs2(v);
    }
}

void solve() {
    cin >> n;
    for (int k=1;k<n;k++)
        cin >> i[k] >> j[k] >> x[k] >> y[k];

    fill(c+1, c+n+1, vector<tuple<int, map<int, int>, map<int, int>>>());
    for (int k=1;k<n;k++) {
        c[i[k]].push_back( { j[k], pf(x[k]), pf(y[k]) } ); // i[k] = j[k]x[k]/y[k]
        c[j[k]].push_back( { i[k], pf(y[k]), pf(x[k]) } ); // j[k] = i[k]y[k]/x[k]
    }

    fill(active+1, active+n+1, 0);
    dfs1(1); dfs2(1);

    ll res = 0;
    int prime, mult;
    for (int u=1;u<=n;u++) {
        ll tmp = 1;
        for (auto q : val[u]) {
            tie(prime, mult) = q;
            for (int t=0;t<mult;t++)
                tmp=(tmp*prime)%MM;
        }

        res = (res+tmp)%MM;
    }

    cout << res << '\n';

    /* cout << val[1] << '\n'; */

    // Question: What is the array of min sum z such that for all k, z[i[k]]/z[j[k]] = x[k]/y[k]
    //  z[i]/z[j] = x/y <-> z[i]*y = z[j]*x
    //      -> z[i] >= x, z[j] >= y

    // Suppose there are two disconnected components of the input
    //  it follows that the ingrediants for the two are entirely independent and we can't calculate all ri

    // So now assume that the input is connected:
    //  That is, for all k1 k2, there exists a path from z[k1] to z[k2] (in terms of fractions)
    //  That is we can relate the two.

    // Idea: build a graph with nodes 1-n, and an edge between nodes if they are related
    //  It could be to slow to build the transitive closure of this graph

    // We can find the relation between r1 and the rest by traversing this graph
    //
}

int main() {
    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
