#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, q;
vector<int> x;
vector<array<int, 4>> queries;
vector<ll> responses;

vector<ll> bit;
void update(int k, int u) {
    ll diff = u - x[k];
    x[k] += diff;
    for(int i=k; i<=n; i+=(i&-i))
        bit[i] += diff;
}

ll aux_query(int a) {
    ll res = 0;
    for(int i=a; i>0; i-=(i&-i))
        res += bit[i];
    return res;
}

ll query(int a, int b) {
    ll res = aux_query(b) - aux_query(a-1);
    return res;
}

void init() {
    cin >> n >> q;

    x.resize(n+1);
    bit.resize(n+1);

    int tmp;
    for(int i=1; i<=n; ++i) {
        cin >> tmp;
        update(i, tmp);
    }

    queries.resize(q+1);
    responses.resize(q+1);

    int list_num = 1;
    for(int i=1; i<=q; ++i) {
        int t, k, a, b=-1;
        cin >> t >> k;
        if (t <= 2) cin >> a >> b;
        if (t == 3) a = ++list_num;
        queries[i] = {t, k, a, b};
    }
}


vector<vector<int>> graph;
void build_graph() {
    graph.resize(q+1);
    for(int i=1; i<=q; ++i) {
        auto [t, k, a, b] = queries[i];
        graph[k].push_back(i);
    }
}

void traverse_graph(int k=1) {
    stack<array<int, 2>> history;

    for(int i : graph[k]) {
        auto [t, k, a, b] = queries[i];

        if (t == 1) {
            history.push({ a, x[a] });
            update(a, b);
        }

        if (t == 2) {
            ll res = query(a, b);
            responses[i] = res;
        }

        if (t == 3) traverse_graph(a);
    }

    while(history.size()) {
        auto [a, b] = history.top();
        history.pop();
        update(a, b);
    }
}


void print_responses() {
    for(int i=1; i<=q; i++) {
        if (queries[i][0] == 2)
            cout << responses[i] << '\n';
    }
}



void solve() {
    init();
    build_graph();
    traverse_graph();
    print_responses();
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
