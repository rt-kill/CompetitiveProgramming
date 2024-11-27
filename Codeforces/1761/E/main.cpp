#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n;
string adj[4000];

vector<int> reps;
vector<int> ncliq;
set<int> seen;
set<int> comp_vers;
void dfs(int i) {
    if (seen.count(i)) return;
    comp_vers.insert(i);
    seen.insert(i);

    for(int j=0;j<n;j++)
        if(adj[i][j] == '1')
            dfs(j);
}

int isClique() {
    if(comp_vers.size() == 1)
        for(int i : comp_vers)
            return i;

    int res = -1; int rdeg = (comp_vers.size() - 1);
    for(int i : comp_vers) {
        int deg = 0;
        for(int j : comp_vers) {
            if (i == j) continue;
            if (adj[i][j] == '1') deg += 1;
        }

        if (deg < rdeg)
            res = i, rdeg = deg;
    }

    return res;
}

void solve() {
    cin >> n;
    for (int i=0;i<n;i++)
        cin >> adj[i];

    // Suppose we have x components
    //  if any of these components are not cliques,
    //  we can take any vertex in some component that is not adjacent to every vertex in its component and solve in 1 move

    //  So suppose that every component is a clique (of order 2+)

    //  If we have 3+ components, one operation on any node will give us a new component that is not a clique, allowing us to solve the problem in 1 more move
    //  3+ components -> solvable in 2 moves
    //  components are cliques -> not solvable in 1 move

    //  Finally suppose we only have 2 components
    //  If some component is an x clique, we can solve the problem by running the operation on every node in the clique (the last node will have nothing adjacent to it)
    //  This is optimal, and so we operate on every node in the smaller clique

    // We count the number of components/cliques

    reps = vector<int>();
    ncliq = vector<int>();
    seen.clear();

    int mcliq = n; int mcliq_rep;

    int comps = 0;
    for(int i=0;i<n;i++) {
        if (seen.count(i)) continue;

        comps += 1;
        reps.push_back(i);

        comp_vers.clear();
        dfs(i);

        if (comp_vers.size() < mcliq) {
            mcliq = comp_vers.size();
            mcliq_rep = i;
        }

        int tmp = isClique();
        if (tmp != -1) ncliq.push_back(tmp);
    }

    if (comps == 1) {
        cout << 0 << '\n';
        return;
    }

    if (ncliq.size() >= 1) {
        cout << 1 << '\n';
        cout << ncliq[0] + 1 << '\n';
        return;
    }

    if(comps >= 3) {
        cout << 2 << '\n';
        cout << reps[0] + 1 << ' ' << reps[1] + 1 << '\n';
        return;
    }

    if(comps == 2) {
        comp_vers.clear();
        seen.clear();
        dfs(mcliq_rep);
        cout << comp_vers.size() << '\n';
        for(int i : comp_vers)
            cout << i + 1 << ' ';
        cout << '\n';
    }

    // We have 2 comps that are both cliques, we find the smaller one and print all its values
}

int main() {
    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
