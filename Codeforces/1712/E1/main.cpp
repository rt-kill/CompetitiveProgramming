#include <bits/stdc++.h>
using namespace std;

int t;
int l, r;
int res;

int t[int(2e5) + 1];

void solve() {
    cin >> l >> r;



    // Note, this is never true for (i, i, i). This is true for (i, i, j) if and only if i does not divide j
    //  This could be relevant to counting
    // l and r are relatively small

    // FACT: If (i | A) and (j | A) if and only if (lcm(i, j) | A)

    // lcm(i, j) >= i + j <=> (i does not divide j)

    // lcm(i, j, k) = k if both i and j divide k
    // lcm(i, j, k) = lcm(lcm(i, j), k) = lcm(lcm(i, k), j) = lcm(i, lcm(j, k)) = lcm(lcm(i, j), lcm(i, k), lcm(j, k))
    // lcm(i, j, k) >= i + j + k
    //      <=> lcm(lcm(i, j), k) >= i + j + k
    //      <=> lcm(lcm(i, j), k) >= i + j + k

    // If none of the terms divide each other, then obviously
    //  lcm(i, j, k) >= i + j + k
    // If all terms divide k, then obviously
    //  lcm(i, j, k) = k < i + j + k

    // if [ i | j and j | k ] then [ lcm(i, j, k) = k < i + j + k ]
    //
    // if [ i | k and j \not| k ]
    //  if [ lcm(j, k) = 2 * k ]
    //      if [ j > (i * (k/i - 1)) ]
    //        lcm(i, j, k) = i * (k/i) + k < i + j + k
    //      else lcm(i, j, k) >= i + j + k
    //  else lcm(i, j, k) >= lcm(j, k) >= 3 * k > i + j + k
    //
    // if [ i \not| k ]
    //  lcm(i, j, k) >= lcm(i, k) >= k + k >= j + j + k > i + j + k

    // for any (i, j, k), l <= i < j < k <= r,
    //  lcm(i, j, k) < i + j + k if and only if
    //      [ (i | k) ] and [ [ lcm(j, k) = k ] or [ lcm(j, k) = 2k and j + i > k ] ]



    // How many (i, k) pairs are there for which (i | k)?
    //  ~(r/i)
    //  \sum_{i \in (1, 1e5)} (1e5/i) = 1e5*(sum_{i \in (1, 1e5)} 1/i) < (1e5 + \int_{1}^{1e5} (1/x)) = 1e5 + ln(1e5) < 2e5

    //  We can iterate over all (i, k) pairs!
    //  For each (i, k) pair,

    // for all i in (l, r-2)
    //  we can count the k in (l + 2, r) that i does not divide
    //      we can count the j between them
    //  for each k that i divides, we would like to count the j, i < j < k for which
    //      lcm(j, k)


    res = 0;
    // Count the (i, k) for which (i \not | k)
    for (int i = l; i <= r-2; i++) {
        // j = i + 1 can be used for every r
        // j = i + 2 can be used for every r but r = i + 2 -- r may never equal i + 2 tho

        // j = i + (i-1) can be used (r - ) times

        // i < j < 2*i can be used for all but (j - 1) r
        // j = 2*i can be used the same number of times as (j = 2*i - 1)
        //
        // m*i < j < (m+1)*i

        // sum_{m=1}^{r/m} \sum_{j = im+1}^{im + i} (j)
    }

    // THIS IS SO UGLY!!! There must be a better way! Maybe dp?



    // Arguments are fine, but we would need to solve each rec in O(\sqrt{n})
    // solve(l, r) = solve(l + 1, r) + #(i = l)
    //  We can probably solve solutions for which (i \not | k) in ~O(1)
    //  Can we (i | k) in sqrt{N}?


    // dfs tree for solve(l, r) has too many nodes!
    // solve(l, r) = (solve(l + 1, r) + solve(l, r - 1) - solve(l + 1, r - 1)) + res(i = l, k = r)
    //  res(i = l, k = r) =
    //      ((r - 1) - (l + 1) + 1) IF (i \not | k)
    //      (((r - 1) - (l + 1) + 1) - #{j divide k} - #{j > (k - i) and lcm(j, k) = 2k}) IF (i | k)


    // solve(l, r) = solve(l, r/2) + solve(r/2 + 1, r) + sols for which i in left and r in right
    //  This would be fast enough for E1, but not E2

    // segment tree?
    //  What are the time complexities of a segment tree?
    //      If merging intervals takes O(1), O(n) to build (2n nodes) O(log(n)) to find
    //      If merging intervals of length n/2 takes T(n),
    //          S(n) = 2*s(n/2) + T(n) = 2(T(n/2) + 2*s(n/4)) + T(n)
    //          ...  = T(n) + 2T(n/2) + 4T(n/4) + ... + nT(1)
    //      If mering intervals takes O(n), O(nlog(n)) to build, O(nlog(n)) to find

    // merge(solve(l, m), solve(m+1, r)) -> solve(l, r) fast
    //  We may assume m is a multiple of 2 and min((m - l), (r - (m+1))) > 2
    //  solve(l, r) = solve(l, m) + solve(l, m+1) +
    //      /sum_{i = l}^m (\sum_{k = m+1}^r ((k - i - 2)int(!(i | r))))


}

int main() {
    cin >> t;
    for (int i = 0; i < t; i++)
        solve();
    return 0;
}
