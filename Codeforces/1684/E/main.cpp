#include <bits/stdc++.h>
using namespace std;

const int MAXN=1e5, MAXK=1e5, MAXA=1e9;

int t, n, k, a[MAXN];
unordered_map<int, int> counter;

void solve() {
    cin >> n >> k;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    // Note: Cost of array is always positive
    // We would like to maximize MEX and minimize DIFF

    // Notice that DIFF(a) - MEX(a) = DIFF(a > MEX(a))
    //  This can be seen since for all i, DIFF(a) = DIFF(a > i) + DIFF(a <= i)
    //  By definition of MEX(a), we know that {a <= MEX(a)} = {0, 1, ..., MEX(a) - 1}
    //  This statement directly follows

    // The order of moves that we make does not matter
    // We may also assume that if the last move does not strictly decrease our cost, we don't make it
    //

    // Claim: There exists an optimal sequence of moves that never changes the value of a term less than MEX(a) -- at that instant in time
    //  Suppose we change i for which a[i] < MEX(a) to some value >= MEX(a)
    //      If at the end of our move sequence, COST(a') > 0, this move was useless
    //          We could have instead given j for which a'[j] > MEX(a') this value (NOTE WE ASSUME WE ONLY CHANGE EACH VALUE ONCE -- VALID)
    //      Otherwise, (since we dont re-change i) we eventually fill in the gaps, and could have instead moved some index which has max in a' to this value
    //  It makes even less sense to change i for which a[i] < MEX(a) to some value < MEX(a)
    // So this claim should be valid.

    // If at the end of our transformations we have matrix a', we should have never changed a value to be greater than MEX(a')
    // Such a value could have instead have been changed to be MEX(a'), worst case giving us the same cost.

    // So, there must exist an optimal sequence of moves such that any move
    //  Moves a value greater than MEX(a) to value MEX(a) -- with respect to a at that instant in time
    // We may assume we always use all k moves (unless we hit a of cost 0)

    // We may note that the order of elements touched does not matter
    // Any sequence of moves can be represented as a set of indices

    // IDEA: let a' denote our final array
    //  MEX(a') = MEX(a) + k + garbage -- The important part is we can know exactly what our final MEX(a') should be -- this is not too hard to code

    //  We take all nodes of value > MEX(a') (note no node will have value = MEX(a')) and order them by their counts in a
    //      We take nodes to be in our "solution" combination in this order (We already explained why a solution is in a way a combination of indexes)
    //  If there are not enough nodes, the answer must be 0

    //  Our we select nodes via the following priority
    //      NODE has weight > MEX(a') (note no node will have weight = MEX(a') by how we find it)
    //          NODE is repeated the least number of times
    //      Otherwise the answer is 0

    sort(a, a + n);

    unordered_map<int, int> counter;
    int nxt = 0; int nk = k;
    for (int i = 0; i < n; i++) {
        while (a[i] > nxt && nk > 0) {
            nk -= 1;
            nxt += 1;
        }

        if (a[i] > nxt) {
            counter.emplace(a[i], 0);
            counter[a[i]] += 1;
        }

        if (a[i] == nxt)
            nxt += 1;
    }

    vector<pair<int, int>> sp;
    for (const auto& my_pair : counter) {
        sp.push_back(make_pair(my_pair.second, my_pair.first));
    }
    sort(sp.begin(), sp.end());

    int i = 0;
    while(i < sp.size() && k >= sp[i].first) {
        k -= sp[i].first;
        i += 1;
    }

    int res = sp.size() - i;
    cout << res << '\n';
}

int main() {
    cin >> t;
    for (int i = 0; i < t; i++)
        solve();
    return 0;
}
