#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, d;
vector<set<int>> graph;
set<int> p1, p2;
vector<bool> l1, l2;
vector<int> md, ss;

void setup() {
    graph.clear(), p1.clear(), p2.clear(), md.clear(), l1.clear(), l2.clear();

    cin >> n >> d;
    graph.resize(n+1), md.resize(n+1), ss.resize(n+1), l1.resize(n+1), l2.resize(n+1);

    int u, v;
    for(int i=1; i<n; i++) {
        cin >> u >> v;
        graph[u].insert(v);
        graph[v].insert(u);
    }

    int m1, m2, a, b;

    cin >> m1;
    for(int i=0; i<m1; i++) {
        cin >> a;
        /* p1.insert(a); */
        l1[a] = true;
    }

    cin >> m2;
    for(int i=0; i<m2; i++) {
        cin >> b;
        /* p2.insert(b); */
        l2[b] = 1;
    }
}

pair<bool, bool> simplify(int r=1, int p=0) {
    /* pair<bool, bool> res = { p1.count(r), p2.count(r) }, tmp; */
    pair<bool, bool> res = { l1[r], l2[r] }, tmp;

    vector<int> rem;

    for (auto c : graph[r]) {
        if (c == p) continue;

        tmp = simplify(c, r);
        if (!tmp.first && !tmp.second) rem.push_back(c);

        /* if (tmp.first) p1.insert(r); */
        /* if (tmp.second) p2.insert(r); */

        l1[r] = l1[r] || tmp.first;
        l2[r] = l2[r] || tmp.second;

        res = { res.first || tmp.first, res.second || tmp.second };
    }

    for (auto c : rem) graph[r].erase(c);

    return res;
}

void populate(int r=1, int p=0) {
    md[r] = 0, ss[r] = 1;

    for (auto c : graph[r]) {
        if (c == p) continue;

        populate(c, r);
        md[r] = max(md[r], 1 + md[c]);
        ss[r] += ss[c];
    }
}

int aux_solve(int r=1, int p=0) {
    int res = 0;

    for(auto c : graph[r]) {
        if (c == p) continue;

        /* if ((md[c] + 1 > d) || (p1.count(c) && p2.count(c))) */
        /*     res += aux_solve(c, r) + 4; */
        if ((md[c] + 1 > d) || (l1[c] && l2[c]))
            res += aux_solve(c, r) + 4;
        else
            res += 2*ss[c];
    }

    return res;
}

void solve() {
    setup();

    simplify();
    populate();


    int res = aux_solve();
    cout << res << '\n';


    // compression can be done with a simple dfs


    // If both pieces must touch a node in a subtree induced by some child c of the root, our solution is
    //  (4 + solve(c)) + solve(r - c)

    // If neither piece must touch a node in a subtree induced by some child c of the root, our solution is
    //  solve(r - c)

    // This actually follows for arbitrary nodes
    //  Aka, we can compress our graph so that every leaf must be touched by a chess piece

    // If some node n that some chess piece must touch is over a distance of d from the root,
    //  then the other chess piece must touch the child of the root corresponding to its subtree

    // We may assume that for every child of r, exactly one piece must touch a node in the subtree generated by it
    // In addition, every piece is at most a distance of d from the root
    // From here, the solution comes from a simple dfs
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
