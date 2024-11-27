#!/usr/bin/python3
import math

def main():
    N, A, B = int(input()), input(), input()

    s = sum(1 if a == b else 0 for a, b in zip(A, B))
    if len(A) - s <= math.ceil(N/2):
        print(len(A) - s)
        for i, x in enumerate(zip(A, B)):
            a, b = x[0], x[1]
            if a != b: print('1 ' + str(i + 1))
    else:
        print(s + 1)
        print('2')
        for i, x in enumerate(zip(A[::-1], B[::-1])):
            a, b = x[0], x[1]
            if a == b: print('1 ' + str(i + 1))

T = int(input())
for _ in range(T):
    main()
