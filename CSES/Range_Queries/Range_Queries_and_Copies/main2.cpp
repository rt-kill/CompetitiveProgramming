#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, q;
vector<ll> x;

vector<array<ll, 4>> queries;
vector<array<ll, 2>> graph;
vector<ll> res;

// stack stores [ list_index, value_index, previous_value ]
/* stack<array<int, 3>> stak; */
/* void dfs(int k) { */

/* } */

vector<bool> seen;
vector<int> sqi; // sorted query indices

void aux_topo_sort(int r) {
    if (r <= 0) return;
    if (r > q) return;
    if (seen[r]) return;
    seen[r] = true;

    aux_topo_sort(graph[r][0]);
    aux_topo_sort(graph[r][1]);

    sqi.push_back(r);
}

void topo_sort() {
    seen.resize(q+1);
    aux_topo_sort(1);
    reverse(sqi.begin(), sqi.end());
}

vector<ll> bit;

void update(int k, ll u) {
    int diff = u-x[k];

    x[k] += diff;
    for(int i=k; i<=n; i += (i & -i))
        bit[i] += diff;
}

ll aux_query(int a) {
    ll res = 0;
    for(int i=a; i>0; i -= (i & -i))
        res += bit[i];
    return res;
}

ll query(int a, int b) {
    ll res = aux_query(b) - aux_query(a - 1);
    return res;
}

void solve() {
    cin >> n >> q;
    x.resize(n+1);
    bit = vector<ll>(n+1);

    ll tmp;
    for(int i=1; i<=n; ++i) {
        cin >> tmp;
        update(i, tmp);
    }

    // a points to b if b depends on a
    //  a create list query points to all queries afterwards that update it, copy it, or sum_query it
    //      number of such edges would be O(n)
    //  an update list query points to all queries afterwards that copy the list, or sum_query it
    //      possibly O(n^2) edges
    //  a sum_query points to all queries afterwards that update the list in question
    //      possibly O(n^2)

    queries.resize(q+1);
    queries[0] = { }; // Initialization query

    // maps query to next query depending on it
    graph.resize(q+1);
    for(int i=0; i<=q; i++) graph[i] = {-1, -1};

    // stores index of last query involving certian array
    vector<array<int, 2>> prev_query = {{ 0, 0 }, { 0, 0 }};

    for(int i=1; i<=q; ++i) {
        int t, k, a=-1, b=-1;
        cin >> t >> k;
        if (t<=2) cin >> a >> b;

        queries[i] = {t, k, a, b};

        auto [ index, type ] = prev_query[k];
        graph[index][type] = i;

        prev_query[k] = { i, 0 };
        if (t == 3) prev_query.push_back({ i, 1 });
    }


    topo_sort();

    vector<bool> is_last_query;
    is_last_query.resize(q+1);
    vector<bool> smth;
    smth.resize(q+1);
    for(int i=q; i>0; --i) {
        auto [ t, k, a, b ] = queries[i];
        if (!smth[k]) {
            is_last_query[i] = 1;
            smth[k] = 1;
        }
    }

    res.resize(q+1);
    fill(res.begin(), res.end(), -1);


    /* for(int i=1; i<=q; ++i) cout << is_last_query[i] << ' '; */
    /* cout << '\n'; */


    stack<array<ll, 3>> updates;
    stack<ll> cl; cl.push(1);
    int count = 1;

    for (auto i : sqi) {
        auto [ t, k, a, b ] = queries[i];
        cout << t << ' ' << k << ' ' << a << ' ' << b << '\n';

        while (k != cl.top()) {
            while(updates.size() && updates.top()[0] != cl.top()) {
                auto [ g1, pa, pv ] = updates.top();
                update(pa, pv);
                updates.pop();
            }

            cl.pop();
        }

        if (t == 1) {
            updates.push({k, a, x[a]});
            update(a, b);
        }
        if (t == 2) {
            res[i] = query(a, b);
        }
        if (t == 3) {
            cl.push(++count);
        }
    }

    for (int i=1; i<=q; i++)
        if (res[i] >= 0)
            cout << res[i] << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
