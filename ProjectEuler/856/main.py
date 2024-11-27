import random

deck = [ i for i in range(13) for _ in range(4) ]

cnts = [ 0 for _ in range(52) ]

def simulate():
    random.shuffle(deck)

    v = 51
    for i in range(51):
        if deck[i] == deck[i+1]:
            v = i
            break
    cnts[v] += 1

simP = int(1e7)
for i in range(simP): simulate()

res = 0
for i in range(51): res += (i+2)*cnts[i]/(simP-cnts[51])
print(res)
