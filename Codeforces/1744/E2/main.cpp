#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int t;
int a,b,c,d;
int p[60], L;

void factor(int n, int i = 0) {
    while (!(n & 1)) {
        p[i++] = 2;
        n = n / 2;
    }

    for (int f = 3; f <= (sqrt(n) + 1); f += 2) {
        while (!(n - f*(n/f))) {
            p[i++] = f;
            n = n / f;
        }
    }

    if (n > 1) p[i++] = n;

    L = i;
}

set<tuple<int, int, int>> seen;
pair<int, int> dfs(int i, int mx, int my) {
    if (seen.count(make_tuple(i, mx, my)))
        return make_pair(-1, -1);
    seen.insert(make_tuple(i, mx, my));

    if (i == L) {
        int x = (a/mx + 1)*mx;
        int y = (b/my + 1)*my;
        if (x <= c && y <= d)
            return make_pair(x, y);
        return make_pair(-1, -1);
    } else {
        pair<int, int> sub;
        if (mx <= c/p[i]) {
            sub = dfs(i+1, mx*p[i], my);
            if (sub.first != -1)
                return sub;
        }

        if (my <= d/p[i])
            return dfs(i+1, mx, my*p[i]);
    }

    return make_pair(-1, -1);
}

void solve() {
    cin >> a >> b >> c >> d;

    factor(a);
    factor(b, L);
    sort(p, p + L, greater<int>());

    /* cout << '\n'; */
    /* cout << a << ' ' << b << '\n'; */
    /* for (int i = 0; i < L; i++) { */
    /*     cout << p[i] << '\n'; */
    /* } */
    /* cout << '\n'; */

    seen.clear();
    pair<int, int> res = dfs(0, 1, 1);
    cout << res.first << ' ' << res.second << '\n';

    // cout << "DONE" << '\n';

    // We know 1 <= a < c <= 1e9, 1 <= b < d <= 1e9
    // Find any pair x,y for which
    //      a < x <= c, b < y <= d
    //      a*b | x*y
    //      x and y may not exist

    // Wlog a <= b. If a == b, c <= d

    // a*b | (2a)(2b)
    // The nubmers ab divide in order:
    //  [ 0, ab, 2(ab), 3(ab), 4(ab), ... ]

    // When can we use 2(ab)? Only if we can set x = b, y = 2a

    // What if we factorize a, b?
    //  a = prod(p, p + i) -- p is sorted
    //  b = prod(q, q + j) -- q is sorted
    //  F := sorted(p + q)
    //  P := sorted(set(p + q))

    // If a solution exists, then one exists for which x <= y
    //  Suppose we let (b < y <= d), be maximal with respect to product of its prime factors shared with ab
    //  Let a < x be the minimal number that uses the rest of the prime factors

    // If c < x does no solution exist?
    //  Not nessesarily:
    //      Suppose x = 2*rest, 3|y, and 2 \in rest
    //      x = 3*rest/2, y = 2*y/3 could be a solution

    // |p| <= log2(a) <= log2(1e9) < 30
    // |q| <= log2(b) <= log2(1e9) < 30
    // We will have less than 60 factors

    // What about dp? For each prime, it either contributes to y, or it doesn't
    //
    // if j contributes to y, the new problem is
    //  a < x <= c, b < j*y <= d, s.t. a and y use primes [j+1:]
    // else, the new problem is
    //  a < j*x <= c, b < y <= d, s.t. a and y use primes [j+1:]

    // dp(i, mx, my) =>
    //  dp(i+1, mx*p[i], my)
    //  dp(i+1, mx, my*p[i])

    // i will take less than 60 values
    // the pair (mx, my) will take less than (60 choose 2) values
    // this is fast enough!
    // this feels more like a dfs than dp
}

int main() {
    cin >> t;
    for (int i = 0; i < t; i++)
        solve();

    return 0;
}
