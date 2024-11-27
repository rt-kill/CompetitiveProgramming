from math import lcm
from collections import defaultdict
from typing import DefaultDict


def factor(v):# {{{
    res = []

    p = 2
    while p*p <= v:
        if v//p*p == v:
            res.append(p)
            v //= p
        else: p += 1
    if v > 1: res.append(v)

    return res# }}}


def is_prime(v):# {{{
    flag = 1
    for p in range(2, v):
        if v//p*p == v:
            flag = 0
            break
    return flag# }}}


Mod = int(1e9+7)

# N = 5
# N = 20
N = 800


vals = []
for v in range(1, N+1):
    tmp = factor(v)
    if len(tmp) == 0 or tmp[-1]*tmp[-1] <= N:
        vals.append(v)


# cnts[(i, clcm)] = number of ways to make clcm with (i-len(vals))
#   cnts[(i, clcm)] += cnts[(i+1, clcm)]
#   cnts[(i, lcm(clcm, vals[i]))] += cnts[(i+1, clcm)]


# def bfs(i=0):
#     if i == len(vals): return { 1:1 }
#
#     cur = defaultdict(lambda : 0)
#     nxt = bfs(i+1)
#
#     for k,v in nxt.items():
#         cur[k] = (cur[k] + v) % Mod
#         cur[lcm(vals[i], k)] = (cur[lcm(vals[i], k)] + v) % Mod
#
#     print(i, len(cur))
#     return cur
# cnts = bfs()

valsC = []
for v in range(1, N+1):
    if v not in vals: valsC.append(v)

# lcms, seen = set(), set()
# def dfs(i=0, clcm=1):
#
#     if (i, clcm) in seen: return
#     seen.add((i, clcm))
#
#     if i == len(vals):
#         lcms.add(clcm)
#         return
#
#     dfs(i+1, clcm)
#     dfs(i+1, lcm(clcm, vals[i]))
# dfs()
