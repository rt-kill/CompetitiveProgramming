#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n;
void solve() {
    cin >> n;
    if (n == 1) cout << 1;
    else if (n < 4) cout << "NO SOLUTION";
    else {
        deque<int> myperm = {2, 4, 1, 3};
        for(int v=5; v<=n; ++v) {
            if (myperm.front() < v-1) myperm.push_front(v);
            else if (myperm.back() < v-1) myperm.push_back(v);
        }
        for(auto v : myperm) cout << v << ' ';
    }
    cout << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
