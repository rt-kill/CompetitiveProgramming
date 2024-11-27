lines = []
while True:
    line = input()
    if not len(line): break
    lines.append(line)

res = 0
for i in range(len(lines)):
    cur = lines[i]

    cur = cur[cur.find(":")+1:]

    cur = cur.split(';')

    res += i

print(res)
