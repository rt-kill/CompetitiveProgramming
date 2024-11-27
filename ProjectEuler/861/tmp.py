import cmath
val = {}
val[0] = 0
def surreal(n):
    if n in val: return val[n]
    cur = 0
    if n%2 == 1:
        nex = (n-1)//2
        if val[nex] >= 0: cur = 2*val[nex] + 1
    else:
        nex = (n-2)//2
        if val[nex] <= 0: cur = 2*val[nex] - 1
    val[n] = cur
    return cur

N = 300
def term(hi, val, i):
    out = []
    x = 0
    y = 0
    while y <= hi:
        out.append((x, y))
        x += val
        x += 0
        y += i
    return out
terms = sorted([(term(N, surreal(i), i),i) for i in range(1, N+1)], key=lambda x: abs(surreal(x[1])))

lo = 0
hi = 0

dp = [[0] for i in range(N+1)]
dp[0][0] = 1

for t, i in terms:
    print(i)
    now = t[-1][0]
    nlo = min(lo+now, lo)
    nhi = max(hi+now, hi)
    ndp = [[0] * (len(dp[0]) + abs(now)) for j in dp]

    for x, y in t:
        for j in range(y, len(ndp)):
            for k in range(lo, hi+1):
                assert(k+x - nlo >= 0)
                ndp[j][k+x - nlo] += dp[j-y][k-lo]

    lo = nlo
    hi = nhi
    dp = ndp
print(sum(dp[N][:-lo+1]))
