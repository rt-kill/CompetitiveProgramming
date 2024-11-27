#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n;
string b[100];
vector<int> dag[100];


set<int> res[100];
bool seen[100];

void dfs(int u) {
    if (seen[u]) return;
    seen[u] = 1;

    for(int v : dag[u]) {
        dfs(v);
        for(int a : res[v])
            res[u].insert(a);
    }
}

void solve() {
    cin >> n;
    for(int i=0;i<n;i++)
        cin >> b[i];

    fill(dag, dag + n, vector<int>());
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(b[i][j] == '1')
                dag[j].push_back(i); // A[j] strictly contains all its children

    fill(res, res+n, set<int>());
    fill(seen, seen+n, 0);

    int val = 1;
    for(int i=0;i<n;i++)
        res[i].insert(val++);

    for(int u=0;u<n;u++) {
        dfs(u);
        cout << res[u].size() << ' ';
        for(int e : res[u])
            cout << e << ' ';
        cout << '\n';
    }


    // if b[i][j] == 1, then Ai \subset Aj
    // if b[i][j] == 1 -> b[j][i] != 1 (otherwise Ai == Aj)
    //  -> b[i][i] == 0;

    // We can build a relation among the indices of the sets. i < j <-> Ai \subset Aj <-> b[i][j] == 1;
    // Since a solution exists, this is a valid relation

    // First, find all indices for which no index is less than it (b[j][i] == 0 for all j)

    // i < j iff b[i][j] == 1


    // Note, relations are transitive
}

int main() {
    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
