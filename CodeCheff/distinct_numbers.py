#!/usr/bin/python3
T = int(input())
for _ in range(T):
    N, K = map(int, input().split(' '))
    A = list(map(int, input().split(' ')))

    def solve():
        max_a = reduce(max, A)
        elms = set(A)

        ap1 = 0 # add largest element to A
        ap2 = 0 # dont add largest element to A

        moves = 0
        idx = 0
        while moves < k:
            if idx in elms: continue
            if k - moves > 1:
                ap1 += 2*N - idx
            ap2 += max_a - idx
            moves += 1

        return max(ap1, ap2)
    print(solve())
