#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int INF = INT_MAX;

const int MAXN=5e2, MAXM=25e4, MAXW=1e9;

int t, n, m, u, v, w;
int graph[MAXN][MAXN];
ll dists[MAXN];
vector<int> adj[MAXN];

void solve() {
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        adj[i] = vector<int>();
        for (int j = 0; j < n; j++)
            graph[i][j] = -1;
    }

    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        u -= 1; v -= 1;

        if (graph[u][v] == -1) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        if (graph[u][v] == -1 || w < graph[u][v]) {
            graph[u][v] = w;
            graph[v][u] = w;
        }
    }

    for (int i = 1; i < n; i++)
        dists[i] = INF;
    dists[0] = 0;

    // dp(i, t) := the smallest cost to get from node 0 to i with 1 edge after t operations
    // dp(i, 0) := { w[i] if i connected to n, INF otherwise }
    // dp(i, t) := {
    //      dp(i, t-1) OR
    //      dp(j, t-1) + ... (for j adj to i)
    // }


    // BFS:
    // Q = (0, 0, INF)
    // For i adjacent to 0, add (i, 1, w[i]) to q
    //  When a vertex is processed, we know it can be reached by i in x moves with min weight w
    //      update dist[i] with min(dists[i], x*w)

    // We will hit n-1 with an optimal solution befor x hits n

    deque<tuple<int, int, int>> q = { make_tuple(0, 0, INF) };

    int ci, cx, cw;
    while (true) {
        tie(ci, cx, cw) = q.front(); q.pop_front();
        if (cx >= n) break;

        dists[ci] = min(dists[ci], ll(cx)*ll(cw));
        for (int j : adj[ci])
            q.push_back(make_tuple(j, cx + 1, min(cw, graph[ci][j])));
    }

    int res = dists[n-1];
    cout << res << '\n';

    // Idea: Regular min path algoritm, but with the addition that at any point we can use the weight of the last edge traversed.

    // We would create a new graph on pairs of connected nodes (u, v)
    //

    // Any ideal path will touch each node exactly once
    // Suppose p[i] is an ideal path (after we have made all transformations) with MINIMAL nodes
    // We will refer to edge weights as tuples, where edge i will have weight (w, m) where w is its actual weight and m is the cost of positioning it where it is
    //  Notice that for any a-b-c in this path,
    //      Cost of a-b-c                           Avalible rewirings
    //      (w(a,b) + m(a,b)) + (w(b,c) + m(b,c)) < min(  2w(a,b) + m(a,b),  2w(b,c) + m(b,c)  )
    //  But clearly this is not possible!!!
    //  Such a path will always only have one edge.
    //  Such an ideal path will always exist

    // The new problem becomes find a path P such that
    //  min(W(E(P))) * len(P) is minimal

    // We would like to pivot every edge to only connect 1 and n in the minimal moves possible
    //

    // Doubled edges may be important just in that we can still pthe nodes are still connected when pivoting one of their edges.









    // At each step, i can either travel to a node with the original weight, or twice the weight of the last move

    // For any i, we can either get from v[i] to u[i] in w[i] seconds, OR
    //  from u[i] to t[i] in 2w[i] seconds

    // "In a way", for any i, N(v[i]) is strongly connected with weight 2min(\delta(v[i]))

    // Suppose we are at some vertex v[i], and would like to have u[i] be the last vertex adjacent to it that we visit
    //  We could either take the min of edges between v[i] and u[i] (weight w[i])

    // Wires can pivot about nodes they connect

    // At any point, we will either go
    //  a - b - c in w1 + w2 seconds
    //  a - c in 2*w1 seconds

    // We will clearly never want to touch the same node twice (weights are positive)


    // Is it just a simple bfs where we also que the edge used? This new graph will have at most n*2 nodes, we only need the edges provided of minimal weight
}

int main() {
    cin >> t;
    for (int i = 0; i < t; i++)
        solve();

    return 0;
}
