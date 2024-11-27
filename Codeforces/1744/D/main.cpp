#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ar array

int n, a[200000 + 9];

void solve() {
    cin >> n;
    for (int i=1;i<=n;i++)
        cin >> a[i];

    // c*(2 << log(n)) are the best indexes to choose
    // then c*(2 << (log(n)-1))

    int n2s=0;
    for (int i=1;i<=n;i++) {
        int tmp = a[i];
        for (; !(tmp&1); tmp>>=1)
            n2s+=1;
    }

    int bi=1, cnt = 0;  // largest power of 2 less than n
    for(; (bi<<1)<=n; bi<<=1, cnt++);


    int ops = 0; int c = (n/bi);
    while(bi>1 && n2s<n) {
        ops += 1;
        n2s += cnt;

        if (c > 2)
            c-=2;
        else {
            bi>>=1; cnt -= 1;
            c = ((n/bi)&1 ? (n/bi) : (n/bi) - 1);
        }
    }

    if (n2s >= n)
        cout << ops << '\n';
    else
        cout << -1 << '\n';
}

int main() {
    int t; cin >> t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
