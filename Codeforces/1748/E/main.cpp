#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int Ma = int(1e9) + 7;

int t, n, m, a[int(2e5) + 9];

// Child of i is 2*i and 2*i + 1
int tr[int(4e5) + 9]; // t[n] corresponds a[1]
void build_tree(int no, int l, int r) {
    if (l > r) return;
    if (l == r) {
        tr[no] = l;
        return;
    }

    int ms = (l + r)/2;
    build_tree(2*no, l, ms);
    build_tree(2*no + 1, ms+1, r);

    if (a[tr[2*no]] >= a[tr[2*no + 1]])
        tr[no] = tr[2*no];
    else
        tr[no] = tr[2*no + 1];
}

int query(int l, int r, int no, int ls, int rs) {
    if (l <= ls && rs <= r)
        return tr[no];

    int ms = (ls + rs)/2;

    if (ms >= r)
        return query(l, r, no*2, ls, ms);
    if (ms < l)
        return query(l, r, no*2 + 1, ms+1, rs);

    int left = query(l, ms, no*2, ls, ms);
    int right = query(l, ms+1, no*2 + 1, ms + 1, rs);

    if (a[left] >= a[right])
        return left;
    return right;
}

// although (l, r) can technically have (n choose 2) values, since our divide points are non-dynamic, really its ~2n (nodes on our rec tree)
//  This being said, we are still using divide and concure, so this should run around
map<tuple<int, int, int>, int> memory;
int dp(int l, int r, int M) {
    if (r < l) return 1;
    if (l == r) return M;
    if (M <= 0) return 0;

    tuple<int, int, int> rep = make_tuple(l, r, M);

    if (memory.count(rep) == 0) {
        int cent = query(l, r, 1, 1, n);

        int res = dp(l, r, M - 1);
        res = (res + ((ll(dp(l, cent - 1, M-1)) * ll(dp(cent + 1, r, M))) % Ma)) % Ma;

        memory[rep] = res;

        // cout << l << ' ' << r << ' ' << M << " -- " << res << ' ' << cent << '\n';
    }

    return memory[rep];
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    memory.clear();

    build_tree(1, 1, n);
    int res = dp(1, n, m);
    cout << res << '\n';

    // We will now try divide and concure
    // Let solve(l, r, M) be the solution to the subarray a[l:r] (inclusive) with m = M
    // We would like to find solve(1, n, m)
    //  letting i be lm(1, n), we have

    //      solve(1, n, m) = sum(solve(1, i-1, k-1) * solve(i+1, n, k) for k in range(1, m))


    // break it into parts
    // ways(i, j) := num ways to color part i where first number is j

    // assuming "ways" is fast enough, this will work
    // dp(i, m) = ways(i, m)*dp(i + 1, m + 1) + dp(i, m + 1)

    // ways will be the same problem! but we will need to optimize
    //  For example, we can probably build the parts for ways at the same time as building the original parts

    // We change our dp:
    //  dp(s, i, m) = dp(...)*dp(s, i+1, m+1) + dp(s, i, m+1)
    // Problem: we need a max field as well (the max value is dynamic)

    // dp(d, i, m, M) =
    //  dp(d, i, m+1, M) +
    //  dp(d+1, i, 1, m)*dp(d, i+1, m+1, M)

    // PROBLEMS: (m, M) can take (2e5 choose 2) ~1e10 values

    // s is kindof a "depth"





    // Problem breakdown:
    //  Our array will have some "Pillars", the "most important" values of a
    //      This piliars are the strictly increasing subarray of a, starting at index 1

    // Any desirable array b must have the same "Pillars"
    // The solution to this problem is the sum over pillar assignments of b times the assignments of values inbetween pillars

    // Notice that for any pillar assignment, finding the assignment of innerpillar values is simply the same problem in question

    // solve(l, r, M) =
    //  sum(sum(solve(l', r', M') for adjacent pilar pair) for pillar assignment)







    // Notice that this property is translation invariant
    // Any operation that preserves the ordering of a list will preserve this proerty
    //  Example: Addition, Subtraction, Positive Multiplication

    // Idea: we partition a into continuous subsequences such that
    //  the leftmost maximum of any partition is the left most index in that partition
    //  the leftmost maximum of continuous merged partitions is the left most maximum of the last partition

    // Such a partitioning is not hard to find (O(n))
    // I claim that such a partitioning is unique
    //  This is pretty easy to see!

    // An array b will satisfy the desired constraints if and only if it has the same unique partitioning

    // Let P represent this partitioning, where P[i] is a pair of indices (l, r)
    // How many strictly increasing lists of order |P| are there
    //  For each of these lists,

    // We will do dp over (i, m) where i is the partition, and m is the max value
    //  dp(i, m) =
    //      sum(f(i, j)*dp(i+1, m - j) for j in range(1, m - (|p| - i)))
    //
    // How do we stop over counting? Actually not that bad...

    // Suppose for an array b, b[2:] satisfies the conditions for a[2:]
    //  Let i be the last index for which 1 is the position of the leftmost maximum on the segment [1,i]
    //  Note that nessesariliy, 1 is the position of the left most maximum on the segment [1,j] for all j < i

    // b satisfies the conditions for a if and only if b.max(2, i) < b[1] < b.max(i+1,n)
    //  if i = 1, b.max(2, i) = 0
    //  That is the number of arrays c with c[2:] = b[2:] that satisfy the condition is
    //  (b.max(i+1, n) - b.max(2, i) - 1)

    // Suppose for an array b, b[:n-1] satisfies the conditions for a[:n-1]
}

int main() {
    cin >> t;
    for (int i = 0; i < t; i++)
        solve();

    return 0;
}
