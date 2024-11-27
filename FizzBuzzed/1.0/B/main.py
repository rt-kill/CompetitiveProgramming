from sys import stdin
from itertools import permutations

for line in stdin:
    n = int(line)

    s = []
    for _ in range(n): s.append(input())

    o = int(input())
    bp = []
    for _ in range(o): bp.append(tuple(input().split(' ')))
    bp = set(bp)

    s = sorted(s)
    p = permutations(s)

    flag = 0
    for cp in p:
        cf = 1
        for i in range(len(cp)-1):
            if (cp[i], cp[i+1]) in bp: cf = 0
            if (cp[i+1], cp[i]) in bp: cf = 0

        if cf:
            flag = 1
            for v in cp: print(v)
            break

    if flag == 0: print("You all need therapy.")
