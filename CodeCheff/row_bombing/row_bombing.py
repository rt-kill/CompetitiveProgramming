#!/usr/bin/python3
from itertools import product

class DisJointSets():
    def __init__(self,N):
        # Initially, all elements are single element subsets
        self._parents = [node for node in range(N)]
        self._ranks = [1 for _ in range(N)]

    def find(self, u):
        while u != self._parents[u]:
            # path compression technique
            self._parents[u] = self._parents[self._parents[u]]
            u = self._parents[u]
        return u

    def connected(self, u, v):
        return self.find(u) == self.find(v)

    def union(self, u, v):
        # Union by rank optimization
        root_u, root_v = self.find(u), self.find(v)
        if root_u == root_v:
            return True
        if self._ranks[root_u] > self._ranks[root_v]:
            self._parents[root_v] = root_u
        elif self._ranks[root_v] > self._ranks[root_u]:
            self._parents[root_u] = root_v
        else:
            self._parents[root_u] = root_v
            self._ranks[root_v] += 1
        return False

def solve():
    N, M = map(int, input().split(' '))
    wall = [list(map(lambda x: x == '#', input())) for _ in range(N)]
    striked = set()
    dirs = [(0, 1), (1, 0), (0, -1), (-1, 0)]

    def biject(r, c):
        pos = (M*r) + c
        if not (0 <= pos < N*M): raise ValueError(r, c, pos, N, M)
        return pos

    ds = DisJointSets(N*M)
    def update_ds(r, c):
        if not (0 <= r < N and 0 <= c < M): return
        if r not in striked and wall[r][c]: return

        p1 = biject(r, c)
        for dr, dc in dirs:
            nr, nc = r + dr, c + dc
            if not (0 <= nr < N and 0 <= nc < M): continue
            if nr not in striked and wall[nr][nc]: continue

            p2 = biject(nr, nc)
            ds.union(p1, p2)

    for r, c in product(range(N), range(M)):
        update_ds(r, c)

    for r in range(N):
        if any(map(lambda c: ds.connected(biject(0, 0), biject(r, c)), range(M))):
            continue

        striked.add(r)
        for c in range(M): update_ds(r, c)

    print(len(striked) if ds.connected(biject(0, 0), biject(N-1, M-1)) else len(striked) + 1)

T = int(input())
for _ in range(T):
    solve()
