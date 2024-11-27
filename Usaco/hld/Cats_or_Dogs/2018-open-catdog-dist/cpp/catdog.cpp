#include "catdog.h"

#include<bits/stdc++.h>
using namespace std;

int x;

// Lets first suppose we have some current assignment of cats and dogs
//      how can we tell the danger level?

// This is basically asking what is the best assignment of cats and dogs to unassigned nodes to minimize the number of walls needed
//  what is the best assignment of cats and dogs to minimize the number of cat,dog pairs that are adjacent
//  nodes with only 1 child can simply be what ever the node below them is
//  leafs will simply be what ever their parrent is


//


vector<vector<int>> adj;

int root;
vector<int> par, depth;
vector<vector<int>> node_by_depth;
void init_par(int u, int p, int d=0) {
    par[u] = p, depth[u] = d;
    node_by_depth[depth[u]].push_back(u);
    for(auto v : adj[u]) {
        if (v == p) continue;
        init_par(v, u, d+1);
    }
}


vector<int> type, tmp_type; // 0 empty, 1 dog, 2 cat (special, 3 both)

int make_query() {
    tmp_type.assign(type.begin(), type.end());

    int res = 0;

    for(int d=depth.size()-1; d>0; --d) {
        for(auto u : node_by_depth[d]) {
            if (tmp_type[u] == 3) {
                res += (adj[u].size() - 2);
                tmp_type[u] = 0;
            }

            tmp_type[par[u]] |= tmp_type[u];
        }
    }

    if(tmp_type[root] == 3) res += (adj[root].size() - 1);

    return res;
}

void initialize(int N, std::vector<int> A, std::vector<int> B) {
    x = A.size();

    adj.assign(N+1, vector<int>());
    for(int i=0; i<x; ++i) {
        adj[A[i]].push_back(B[i]);
        adj[B[i]].push_back(A[i]);
    }

    root = 1;
    par.assign(N+1, -1), depth.assign(N+1, -1);
    node_by_depth.assign(N+1, vector<int>());
    init_par(root, -1);


    type.assign(N+1, 0);

}

int cat(int v) {
  return 1;
}

int dog(int v) {
  return 2;
}

int neighbor(int v) {
  return 3;
}
