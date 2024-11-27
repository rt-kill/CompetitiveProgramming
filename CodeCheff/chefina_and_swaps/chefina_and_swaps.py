# Help from https://www.codechef.com/viewsolution/68190572
def solve():
    N, A = int(input()), list(map(lambda x: list(map(int, format(int(x), '020b'))), input().split(' ')))
    res = float('inf')

    for x in range(20):
        for y in range(20):
            nb, nx, ny = 0, 0, 0
            for i in range(N):
                if A[i][x] == A[i][y] == 1: nb += 1 # c3
                elif A[i][x] == 1: nx += 1 # c1
                elif A[i][y] == 1: ny += 1 # c2

            if nb >= 2 or (nb == 0 and (nx == 0 or ny == 0)): continue

            if nb == 0:
                Nb, Nx, Ny = 0, 0, 0; cur = 0
                for i in range(N):
                    if A[i][x] == A[i][y] == y: Nb += 1
                    elif A[i][x] == 1: Nx += 1
                    elif A[i][y] == 1: Ny += 1

                    if (Nb + Nx + Ny <= nx): cur += Ny
                    else: cur += nx - Nx

                res = min(res, cur)

            else:
                Nb, Nx, Ny = 0, 0, 0; cur = 0
                for i in range(N):
                    if A[i][x] == A[i][y] == 1:
                        Nb += 1
                        if (Nb + Nx + Ny <= nx): cur += Ny
                        else: cur += nx - Nx
                    elif A[i][x] == 1: Nx += 1
                    elif A[i][y] == 1: Ny += 1

                    if (Nb + Nx + Ny <= nx): cur += Ny + Nb
                    else: cur += nx - Nx + nb - Nb

                res = min(res, cur)

    if res == float('inf'): print(-1)
    else: print(res)


T = int(input())
for _ in range(T):
    solve()
