from itertools import product
from functools import cache


@cache
def solve(grid):
    if all( all(grid[r][c] for c in range(len(grid[0]))) for r in range(len(grid)) ):
        return 1


    if all( all(grid[r][c]==0 for c in range(len(grid[0]))) for r in range(len(grid)) ):
        return solve( tuple([ tuple([ (1 if r == 0 and c == 0 else 0)
                                    for c in range(len(grid[0])) ])
                                    for r in range(len(grid)) ])
                     ) / len(grid) / len(grid[0])


    takeable = set()
    for r,c in product(range(len(grid)), range(len(grid[0]))):
        if grid[r][c]: continue
        for dr,dc in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
            if not (0 <= r+dr < len(grid) and 0 <= c+dc < len(grid[0])): continue
            if grid[r+dr][c+dc] == 1: takeable.add((r, c))

    # tmp = [ tuple([ tuple([ (1 if nr==r and nc==c else grid[r][c])
    #                                 for c in range(len(grid[0])) ])
    #                                 for r in range(len(grid)) ])
    #                                 for nr,nc in takeable ]

    subs = [ solve( tuple([ tuple([ (1 if nr==r and nc==c else grid[r][c])
                                    for c in range(len(grid[0])) ])
                                    for r in range(len(grid)) ]) )
                                    for nr,nc in takeable ]

    return sum(subs) / (len(grid)*len(grid[0]) - sum( sum(row) for row in grid ))

rows, cols = 1, 3
# rows, cols = 2, 2
# rows, cols = 2, 3
# rows, cols = 5, 8

print( solve( tuple([ tuple([ 0 for _ in range(cols) ]) for _ in range(rows) ])) )
