#include <bits/stdc++.h>
using namespace std;

using ll = long long;

map<pair<char, char>, int> outcome = {
    { {'A', 'X' }, 3 },
    { {'A', 'Y' }, 6 },
    { {'A', 'Z' }, 0 },
    { {'B', 'X' }, 0 },
    { {'B', 'Y' }, 3 },
    { {'B', 'Z' }, 6 },
    { {'C', 'X' }, 6 },
    { {'C', 'Y' }, 0 },
    { {'C', 'Z' }, 3 }
};

map<pair<char, char>, char> rev = {
    { {'A', 'X' }, 'Z' },
    { {'A', 'Y' }, 'X' },
    { {'A', 'Z' }, 'Y' },
    { {'B', 'X' }, 'X' },
    { {'B', 'Y' }, 'Y' },
    { {'B', 'Z' }, 'Z' },
    { {'C', 'X' }, 'Y' },
    { {'C', 'Y' }, 'Z' },
    { {'C', 'Z' }, 'X' }
};

map<char, int> extra = {
    { 'X', 1 },
    { 'Y', 2 },
    { 'Z', 3 }
};

void solve() {
    vector<pair<char, char>> code;
    char v1, v2;
    while(cin >> v1 >> v2)
        code.push_back( { v1, v2 } );

    int res1 =
        transform_reduce(code.begin(), code.end(), 0,
            plus{},
            [](auto p) { return outcome[p] + extra[p.second]; }
        );

    int res2 =
        transform_reduce(code.begin(), code.end(), 0,
            plus{},
            [](auto p) { return outcome[{p.first, rev[p]}] + extra[rev[p]]; }
        );

    cout << res1 << ' ' << res2 << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
