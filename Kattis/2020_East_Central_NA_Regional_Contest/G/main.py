n, m = map(int, input().split())
a = [x for x in range(1,n+1)]
for i in range(m):
    win, lose = input().split()
    win = int(win[1:])
    lose = int(lose[1:])
    wini = a.index(win)
    losei = a.index(lose)
    if wini < losei:
        continue
    else:
        a = a[:losei] + a[losei+1:wini+1] + [lose] + a[wini+1:]
b = ["T" + str(i) for i in a]
print(*b)
