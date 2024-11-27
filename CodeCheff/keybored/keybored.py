from functools import cache
from math import ceil
from collections import defaultdict
from random import sample
from sys import stdout

alpha_list = list('abcdefghijklmnopqrstuvwxyz0123456789')
alpha_set = set(alpha_list)

def point_to_loc(p):
    x = p[0] + 2*p[1]
    y = 2*p[0]
    return (x, y)

def norm(p1, p2):
    x1, y1 = point_to_loc(p1)
    x2, y2 = point_to_loc(p2)
    return int(abs(x1 - x2) + abs(y1 - y2))

test = list(map(list, ('qw0ert1yui2op', '3asdfg4hjkl5', 'z6xc7v8bn9m')))
test_inv = {}
for r in range(3):
    for c in range(13 - r):
        test_inv[test[r][c]] = (r, c)

def query1(w):
    res = 0
    for i in range(len(w) - 1):
        p1 = test_inv[w[i]]
        p2 = test_inv[w[i+1]]
        res += norm(p1, p2)

    return res

def query2(c):
    r, c = test_inv[c]
    return (r + 1, c + 1)

# as we move away from the middle col, net_dist strictly increases
# as we move away from the top row, net_dist strictly decreases
def net_dist(r, c):
    res = 0
    for r2 in range(3):
        for c2 in range(13 - r2):
            res += norm((r, c), (r2, c2))
    return res

net_dists = {}
inv_net_dists = defaultdict(set)
for r in range(3):
    for c in range(13 - r):
        nd = net_dist(r, c)
        net_dists[(r, c)] = nd
        inv_net_dists[nd].add((r, c))

def query_net_dist(a):
    w1, w2 = '', ''
    for c in alpha_list:
        if c == a: continue
        if len(w1) < 36: w1 += (a + c)
        if len(w1) == 36: w2 += (c + a)

    print('? ' + w1, flush=True)
    d1 = int(input())
    # d1 = int(query1(w1))

    print('? ' + w2, flush=True)
    d2 = int(input())
    # d2 = int(query1(w2))

    net_dist = (d1 + d2)//2
    return net_dist

def query_char(a):
    print('? ' + a, flush=True)
    r, c = map(int, input().split(' '))
    # r, c = query2(a)

    return (r - 1, c - 1)

def triangulate(p1, p2, p3, d1, d2, d3):
    for r in range(3):
        for c in range(13 - r):
            p = (r, c)
            nd1 = norm(p1, p) + norm(p2, p)
            nd2 = norm(p1, p) + norm(p3, p)
            nd3 = norm(p2, p) + norm(p3, p)
            if d1 == nd1 and d2 == nd2 and d3 == nd3: return p
    return -1

def triangulate_query(p1, c1, p2, c2, p3, c3, c):
    w1 = c + c1 + c + c2 + c
    w2 = c + c1 + c + c3 + c
    w3 = c + c2 + c + c3 + c

    print('? ' + w1, flush=True)
    d1 = int(input())//2

    print('? ' + w2, flush=True)
    d2 = int(input())//2

    print('? ' + w3, flush=True)
    d3 = int(input())//2

    # d1 = query1(w1)//2
    # d2 = query1(w2)//2
    # d3 = query1(w3)//2

    return triangulate(p1, p2, p3, d1, d2, d3)

def solve():
    # res = [13 * [None], 12 * [None], 11 * [None]]
    res = {}
    inv_res = {}
    unsolved = set(alpha_list)

    # If distance between two keys is 2, they must be adjacent
    # If distance between two keys is 3, they must be a knight move apart

    # If the distance between two keys is even, they must lie on non-adjacent rows
    #   Any key in the center row can only be an even distance away from other keys on the center row
    char_dists = {}
    inv_char_dists = defaultdict(set)
    my_sample = iter(sample(alpha_list, len(alpha_list)))

    while len(res) < 2:
        char = next(my_sample)
        net_dist = query_net_dist(char)

        if len(inv_net_dists[net_dist]) == 1:

            r, c = next(iter(inv_net_dists[net_dist]))
            res[char] = (r, c)
            inv_res[(r, c)] = char
            unsolved.remove(char)

        char_dists[char] = net_dist
        inv_char_dists[net_dist].add(char)

    char = next(iter(unsolved))
    r, c = query_char(char)
    res[char] = (r, c)
    inv_res[(r, c)] = char
    unsolved.remove(char)

    c1, c2, c3 = res.keys()
    p1, p2, p3 = res[c1], res[c2], res[c3]

    for char in unsolved:
        p = triangulate_query(p1, c1, p2, c2, p3, c3, char)
        res[char] = p
        inv_res[p] = char

    rows = []
    for row in range(3):
        tmp = ''
        for col in range(13 - row):
            tmp += (inv_res[(row, col)])
        rows.append(tmp)


    print('!')
    for s in rows:
        print(s)

T = int(input())
for _ in range(T):
    solve()
