#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, q;
vector<int> p;
vector<tuple<int, int, int>> queries;

vector<int> vals;
int N;
int ind(int s) {
    int i = lower_bound(vals.begin(), vals.end(), s) - vals.begin();
    return i;
}

vector<int> bit;

void update_bit(int k, int u) {
    for(int i=k; i<=N; i+=(i&-i))
        bit[i] += u;
}

int aux_query(int a) {
    int res = 0;
    for(int i=a; i>0; i-=(i&-i))
        res += bit[i];
    return res;
}

int query_bit(int a, int b) {
    int res = aux_query(b) - aux_query(a - 1);
    return res;
}

void init_bit() {
    bit = vector<int>(N+1, 0);
    for(auto v : p)
        update_bit(ind(v), 1);
}

void solve() {
    cin >> n >> q;

    p.resize(n);
    for(int i=0; i<n; ++i) {
        cin >> p[i];
        vals.push_back(p[i]);
    }

    char a;
    int b, c;
    while(q--) {
        cin >> a >> b >> c;
        queries.push_back({ a, b, c });
        if (a == '!') vals.push_back(c);
    }

    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    N = vals.size();

    init_bit();
    for(auto [a, b, c] : queries) {
        switch(a) {
            case '?': {
                int res = query_bit(ind(b), ind(c));
                cout << res << '\n';
                break;
            }
            case '!': {
                int prev = p[b];
                p[b] = c;
                update_bit(ind(prev), -1);
                update_bit(ind(c), 1);
                break;
            }
        }
    }
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
