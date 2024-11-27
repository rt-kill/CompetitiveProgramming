#include <bits/stdc++.h>
using namespace std;

using ll = long long;

string dna;
void solve() {
    cin >> dna;

    char prev = ' ';
    int count=0, res=0;

    for_each(dna.begin(), dna.end(), [&prev, &res, &count](auto v){
        if (prev == v) count += 1;
        else prev = v, count = 1;
        res = max(res, count);
    });

    cout << res << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
