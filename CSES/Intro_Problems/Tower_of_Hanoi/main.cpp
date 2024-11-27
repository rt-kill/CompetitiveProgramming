#include <bits/stdc++.h>
using namespace std;

using ll = long long;
/* pair<int, int> diffs[3] = { {0, 1}, {0, 2}, {1, 2} }; */

vector<pair<int, int>> res;
void rec(int a, int f, int t) {
    if (a == 0) return;
    int o = 6-f-t;

    rec(a - 1, f, o);
    res.push_back( { f, t } );
    rec(a - 1, o, t);
}

void solve() {
    int n; cin >> n;
    rec(n, 1, 3);
    cout << res.size() << '\n';
    for (auto [ v1, v2 ] : res)
        cout << v1 << ' ' << v2 << '\n';

    // dp(n, 2) = 2*dp(n-1, 1) + 1

    /* int max_mask = (1<<n) - 1; */
    /* queue<pair<array<int, 3>, int>> q( { { { max_mask, 0, 0 }, 0 } } ); */

    /* set<ll> seen; */
    /* while (!q.empty()) { */
    /*     auto [ stacks, depth ] = q.front(); q.pop(); */
    /*     ll id = (ll(stacks[0]) << 2*n) + (ll(stacks[1] << n)) + (stacks[2]); */

    /*     if (seen.count(id)) continue; */
    /*     seen.insert(id); */

    /*     if (stacks[2] == max_mask) { */
    /*         res = depth; */
    /*         break; */
    /*     } */

    /*     int m1, m2, tmp, mb; */
    /*     for (auto [ s1, s2 ] : diffs) { */
    /*         m1 = stacks[s1],    m2 = stacks[s2]; */

    /*         tmp = ( m1&(-m1) ) | ( m2&(-m2) ); */
    /*         mb = tmp&(-tmp); */

    /*         array<int, 3> child = { stacks }; */
    /*         child[s1] = m1^mb, child[s2] = m2^mb; */

    /*         q.push( { { child }, depth + 1 } ); */
    /*     } */
    /* } */

    /* cout << res << '\n'; */
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
