#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int t, p;
int val = 0, r;
vector<set<int>> tree;
map<string, int> mymap;
map<array<int, 2>, bool> is_ancestor;
map<array<int, 2>, bool> dists;

// could be optimized with adj matrix
int find_root() {
    for (int i=0; i<val; i++) {
        bool is_root = 1;
        for (int j=0; j<val; j++) {
            if (i == j) continue;
            is_root = is_root && (!tree[j].count(i));
        }

        if (is_root) return i;
    }

    return -1;
}

void ancestor_pop(int v, int a) {
    if (is_ancestor.count({v, a})) return;

    if (tree[v].empty()) {
        is_ancestor[{v, a}] = (v == a);
        dists[{v, a}] = 0;
    }
    else {
        is_ancestor[{v, a}] = 0;
        for (auto c : tree[v]) {
            ancestor_pop(c, a);
            is_ancestor[{v, a}] = is_ancestor[{v, a}] || is_ancestor[{c, a}];

            if (is_ancestor[{c, a}]) {
                dists[{v, a}] = dists[{c, a}] + 1;
            }
        }
    }
}

int cca_aux(int v, int a, int b) {
    for (auto c : tree[v])
        if (is_ancestor[{c, a}] && is_ancestor[{c, b}])
            return cca_aux(c, a, b);

    return v;
}

int closest_common_ancestor(int a, int b) {
    ancestor_pop(r, a);
    ancestor_pop(r, b);
    int res = cca_aux(r, a, b);
    return res;
}

void solve() {
    cin >> t >> p;

    tree = vector<set<int>>(100, set<int>());

    string s0, si;
    int d;
    for (int i=0; i<t; i++) {
        cin >> s0 >> d;
        if (!mymap.count(s0)) mymap[s0] = val++;

        for (int i=0; i<d; i++) {
            cin >> si;
            if (!mymap.count(si)) mymap[s0] = val++;

            tree[mymap[s0]].insert(mymap[si]);
        }
    }

    r = find_root();

    string ta, tb;
    while (p--) {
        cin >> ta >> tb;
        int a = mymap[ta], b = mymap[tb];

        int c = closest_common_ancestor(a, b);
        int d1 = dists[{c, a}], d2 = dists[{c, b}];

        if (d1 == 0 && d2 == 1) {
            cout << tb << " is the child of " << ta << '\n';
        } else if (d1 == 1 && d2 == 0) {
            cout << ta << " is the child of " << tb << '\n';
        } else if (d1 == 0) {

        }

        if (d1 < d2) {
            swap(d1, d2);
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
