#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int n, m, a[int(2e5) + 9];

void solve() {
    cin >> n >> m;
    for(int i=0;i<n;i++)
        cin >> a[i];

    multiset<int, greater<int>> s;
    for(int i=0;i<n;i++)
        s.insert(a[i]);


    int cs=m, b=0, ;
    while(!s.empty()) {
        auto it = s.lower_bound(cs); // pointer to largest element not greater than cs
        if (it != s.end()) {
            int l = *it;
            cs -= l;

            s.erase(s.find(l));
        } else {

        }
    }

    // Notice that if for any i, a[i] = m, it does not matter when we download/watch this video as nothing can be done in parallel with it
    //  If for some i, a[i] = m-1, we can only parallelize a[i] with elms of value 1
    //  do we want to do this even while we watch a[i]? I believe so -- we will need to watch the video eventually anyways which we can only do one at a time

    // So, we know how to handel m's and (m-1)'s
    //  Is there a more general way

    // If for some i, a[i] = k, we can only parallize a[i] with elms of value <= (m-k)
    //  How do we select which elms to parallize it with? Does the problem reduce to a subproblem with (m-k)?
    //      Not exactly since we have a time cap

    // Ideally, we will have the largest watch_time/total_time ratio

    // If (a[i] + a[j] <= m), we can watch both of these videos in [ max(a[i], a[j]) + (a[i] == a[j]) + 1 ] time

    // If multiple videos are ready to be watched, we always watch the larger one first
    // The largest video will need to eventually be downloaded -- i think we can always start with it
    // While it is downloading

    // Complete Guess:
    //  Always start downloading the largest video while you can
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
