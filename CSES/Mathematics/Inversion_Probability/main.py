
n = int(input());
r = list(map(int, input().strip().split(' ')))

fracs = []
for i in range(len(r)):
    for j in range(i+1, len(r)):
        if r[i] <= r[j]: fracs.append(( r[i]-1, 2*r[j] ))
        else: fracs.append((( 2*r[i] - r[j] - 1), 2*r[i] ))

num, den = 0, 1

for _, d in fracs: den *= d
for n, d in fracs: num += n*(den//d)

res = num/den
print("%.6f" % res)
