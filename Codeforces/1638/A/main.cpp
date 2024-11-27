#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, p[501];

void solve() {
    cin >> n;
    for(int i=0;i<n;i++)
        cin >> p[i];

    int c = 1; int i = 0;
    while(i < n && p[i] == c)
        i++, c++;
    for(int k=0;k<i;k++)
        cout << p[k] << ' ';

    int j = i;
    if (i < n) {
        while(p[j] != c)
            j++;

        for(int k=j;k>=i;k--)
            cout << p[k] << ' ';
        for(int k=j+1;k<n;k++)
            cout << p[k] << ' ';
    }
    cout << '\n';
}


int main() {
    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
