from collections import defaultdict
from functools import cache

MOD = 10**9 + 7
def prime_factors(n):
    i = 2
    factors = defaultdict(lambda: 0)
    while i * i <= n:
        if n % i:
            i += 1
        else:
            n //= i
            factors[i] += 1
    if n > 1:
        factors[n] += 1

    return factors


def solve():
    N = int(input()) # 10^5
    A = list(map(int, input().split(' '))) # A[i] <= 10^6

    # factors = defaultdict(lambda: SortedList(key=lambda x: -1*x))
    factors = defaultdict(list)
    for num in A:
        tmp = prime_factors(num)
        for p in tmp:
            if tmp[p] > 0:
                factors[p].append((p**tmp[p]) % MOD)

    for p in factors:
        factors[p] = sorted(factors[p])[::-1]

    res = 0
    for i in range(N):
        tmp = 1
        for p in list(factors.keys()):
            if i < len(factors[p]):
                tmp = (tmp*factors[p][i]) % MOD
            else: del factors[p]

        res = (res + tmp ) % MOD

    print(res)

T = int(input())
for _ in range(T):
    solve()
