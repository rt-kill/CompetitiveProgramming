#include <bits/stdc++.h>
using namespace std;

int t, n, a[int(1e5) + 9], b[int(1e5) + 9];

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> b[i];

    // we will revolve around values that are 0 and n + 1

    // Suppose that a generates b
    //  if b[i] = n+1, and a[j] = i, for all t < j, a[t] <= k
    //  if b[i] = 0, and a[j] = i, for all t < j a[j] > k

    // No matter what,
    //  b[a[1]] = 0     iff a[1] > k
    //  b[a[1]] = n+1   iff a[1] <= k

    //  b[a[2]] = 0     iff min(a[1], a[2]) > k
    //  b[a[2]] = n+1   iff max(a[1], a[2]) <= k
    //  b[a[2]] = a[1]  else

    //  b[a[i]] = 0     iff min(a[1], ..., a[i]) > k
    //  b[a[i]] = n+1   iff max(a[1], ..., a[i]) <= k
    //  1 <= b[a[i]] <= n else

    //  b[a[n]] = 0     iff k = 0   => b[a[i]] = 0
    //  b[a[n]] = n+1   iff k = n   => b[a[i]] = n+1

    //  b will never have both 0 and n+1
    //  b will always have either 0 or n+1
    //  every i for which b[i] \in {0, n+1} will need to be at the start of a
    //  the order of these terms does not matter except for the last element
    //  the only term of these that will appear in b is the last element
    //  this index will nessesarily need to be after this head



    // This is a disorgonized start to the problem
    // set<int> head;
    // for (int i = 1; i <= n; i++)
    //     if (b[i] == 0 || b[i] == n+1)
    //         head.insert(i);
    // int tmp;
    // for (int i = 1; i <= n; i++)
    //     if (head.count(b[i])) {
    //         tmp = i;
    //         head.erase(b[i]);
    //         break;
    //     }
    // a = [...head, b[tmp], tmp, ...]
    // After this, a will nessesarily need to have all indexes for which b[i] = tmp
    // We repeat the same thing we did for (b[i] == 0) or (b[i] == n+1)

    vector<int> my_list[n+2];
    int my_vals[n+2] = { -1 }; // b[i] -> vals whose indices must come next in a

    for (int i = 1; i <= n; i++)
        my_list[b[i]].push_back(i);

    for (int i = 1; i <= n; i++)
        if (my_list[i].size() > 0)
            my_vals[b[i]] = i;

    int cur_val = (my_list[0].size() > 0) ? 0 : n+1;
    int i = 1;

    while (i <= n) {
        for (int v : my_list[cur_val]) {
            if (v = my_vals[cur_val]) continue;
            a[i++] = cur_val;
        }
        a[i++] = my_vals[cur_val];
        cur_val = my_vals[cur_val];
    }

    for (int i = 1; i <= n; i++) {
        cout << a[i] << ' ';
    }
    cout << '\n';
}

int main() {
    cin >> t;
    for (int i = 0; i < t; i++)
        solve();

    return 0;
}
