class Solution:
    def multinomial(self, n):
        return factorial(sum(n))/prod([factorial(i) for i in n])

    def getProbability(self, balls: List[int]) -> float:
        n = sum(balls)//2
        opts = [ range(0, i+1) for i in balls ]
        ch = list(product(*opts))
        och = [ [ i - j for i, j in zip(balls, ch[k]) ] for k in range(len(ch)) ]

        res = 0
        for fh, sh in zip(ch, och):
            if (sum(fh) == n and fh.count(0) == sh.count(0)):
                res += self.multinomial(fh) * self.multinomial(sh)

        return res / self.multinomial(list(balls))
