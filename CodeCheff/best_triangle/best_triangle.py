from math import sqrt, invtan

N, K = map(int, input().split(' '))
points_set = set(tuple(map(int, input().split(' '))) for i in range(N))
sorted_points = sorted(list(points_set))

def diff(p1, p2):
    nx, ny = p1[0] - p2[0], p1[1] - p2[1]
    return (nx, ny)

def dot(p1, p2):
    return p1[0]*p2[0] + p1[1]*p2[1]

def norm(p):
    return sqrt(dot(p, p))

res = -1
def area(p1, p2, p3):
    v12 = diff(p2, p1)
    v13 = diff(p3, p1)

    b = norm(v13)
    h = norm(diff(v12, dot(v12, v13)*v13))
    2a = h*b

    if 2a <= K: res = max(res, 2a)

    return a

def theta(p):
    toa = p[1]/p[0]
    return invtan(toa)

# Find largest triangle between points and origin larger than res
def area_using_origin(points):
    # Option: Sort points based on theta, divide and concure again
    points = sorted(points, key=theta)
    def dnc_theta(l, r):

        return -1

    return -1

def dnc(l, r):
    if r - l < 3: return 0

    m = l + (r - l)//2
    dnc(l, m), dnc(m+1, r)

    i = m
    while i >= l:
        # Points in question moving sorted_points[i] to the origin
        piq = [diff(sorted_points[j], sorted_points[i]) for j in range(i + 1, r + 1)]
        area_using_origin(points)
        i -= 1

# Idea: Draw giant shape around all points,
#   Slowly shrink shape
#   Convex Hull

# Idea: For every pair of points, binary search on h
#   Problem, we would need to first sort with respect to two points

# Idea: For each point, consider it as the origin
#   How would we solve this problem if we knew one of the points had to be the origin in O(nlog(n))
#   Sort points by distance from origin
#

# Idea: Given two points, how would I find the largest triangle they can make fast?
#   I would need the points to already be sorted by h


print(res)
