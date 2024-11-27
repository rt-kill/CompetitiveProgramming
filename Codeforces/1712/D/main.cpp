#include <bits/stdc++.h>
using namespace std;

#define NA int(1e9)

int t;
int n, k;
int a[int(1e5) + 9];

int res;

void solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    // No matter what array a we are given, the min path between i and j will be of the form (i-j) or (i-m-j) for some (m < i) or (m > j)

    //  In the case of the former, the weight will be min(a[i], ..., a[j])

    //  In the case of the latter, the weight will be
    //      min(a[m], ..., a[i]) + min(a[m], ..., a[j])     if m < i    -- IFF exists m < i s.t. a[m] < min(a[i], ..., a[j])/2
    //          -- IFF min(a[1], a[i-1]) < min(a[i], ..., a[j])/2
    //      min(a[i], ..., a[m]) + min(a[j], ..., a[m])     if m > j    -- IFF exists m > j s.t. a[m] < min(a[i], ..., a[j])/2
    //          -- IFF min(a[j+1], a[n]) < min(a[i], ..., a[j])/2
    //  -- IFF min(a[1], a[n]) < min(a[i], ..., a[j])/2

    // For all i and j,
    //  d(i, j) = min(  min(a[i], ..., a[j]),  2*min(a[1], ..., a[n])  )
    //      => if (j - i) > 1, d(i, j) = d(m, m+1) for some i <= m <= j

    // max(d(i, j)) = max(d(i, i+1))  = max( min( min(a[i], a[i+1]), 2*C ) ) = min( max( min(a[i], a[i+1]) ), 2*C )


    // Given some a, the diamater is either
    //  D = 2*C
    //      Eventually, in order to increase D, we must increase all of the smallest elements of a

    //  D = max( min(a[i], a[i + 1]) ) < 2*C
    //      We either make a move that increases
    //          max( ... ) the most, and terminate
    //          Or if we have two moves left, we can make max( ... ) 10^9, and then terminate
    //      (if we don't do this, it is nessesarily because we will eventually increase C)
    //  OR  We increase all of the smallest elements of a



    // if k > 1:    we can try to max C in k-1 moves and return min(1e9, 2*C)
    //      OR      we can try to max C in k moves and return min( max( ... ), 2*C )
    // if k == 1:   we can easy brute force
    // -----------------------------------
    map<int, int> counter;
    for (int i = 1; i <= n; i++) {
        counter.emplace(a[i], 0);
        counter[a[i]] += 1;
    }
    // I want this to be a min queue
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq(counter.begin(), counter.end());

    // if k == 1:
    //  if pq.top().second == 1:
    //      res = max(
    //          min( max(max( ... ), a[m-1], a[m+1]), 2 * pq.second_top().first) // we replace po.top with 1e9
    //          min( max(a), 2*pq.top().first )
    //      )
    //  else:
    //      res = min( max(a), 2*pq.top().first )
    //

    if (k == 1) {
        res = min( *max_element(a+1, a+1+n), 2*pq.top().first );
    } else {
        while (!pq.empty() && (pq.top()).second < k) {
            k -= pq.top().second; pq.pop();
        }

        res = pq.empty() ? int(1e9) : min(int(1e9), 2*pq.top().first);
    }

    if (k == pq.top().second) {
        int myMax = 1;
        int neck = pq.top().first; pq.pop();

        for (int i = 1; i < n; i++) {
            int v1 = a[i] <= neck ? int(1e9) : a[i];
            int v2 = a[i+1] <= neck ? int(1e9) : a[i+1];
            myMax = max(myMax, min(v1, v2));
        }

        int tmp = pq.empty() ? int(1e9) : pq.top().first;
        res = max( res, min( myMax, 2*tmp ) );
    }
    cout << res << '\n';

    // -----------------------------------



    //  Since in the case of the latter, min(a[m], ..., a[i]) + min(a[m], ..., a[j]) <= min(a[i], ..., a[j]), min(a[m], ..., a[i-1]) <= min(a[i], ..., a[j])/2. Wlog, a[m] = min(a[m], ..., a[i])

    // Ordering of a[i] will not change anything (the graphs constructed will be isomorphic)
    // We will only change values of a[i] to 1e9

    // MST's don't always contain sohrtest paths (Unless values are distinct)
    // This graph will have to many edges to build

    // We notice
    //  d(l, r) = min
    //      min_{i != l, r} (d(l, i) + d(i, r))
    //      min(a[l], a[l + 1], \dots, a[r])

    // So, any min path from l to r will not have second or preultimate node (l < m < r)
    //  It follows that the min path will either be (l-r), or (l-m-r) for some (m < l) or (m > r)
    //  The latter part of this claim: Suppose our min path is (l-m1-m2-...-r). It follows that min(a[m1]...a[m2]) < min(a[m1]...a[r]) => m2 > r & min(a[l]...a[m2]) <= min(a[r]...a[m2]) < min(a[m1]...a[r]) <= min(a[m1]...a[l]) => (l-m2-...-r) is a smaller path


    //  I am guessing that the shortest path from l to r is just the edge connecting them.
    //  This is not the case: consider the case then a[1] = 1, then d(l, r) is max 2 for all l and r

    //


    // max_{l, r} d(l, r) = max_{l, r} min_{i} (d(l, i) + d(i, r))
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++)
        solve();

    return 0;
}
