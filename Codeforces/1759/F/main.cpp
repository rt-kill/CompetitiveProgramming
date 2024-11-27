#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int N = 105;

int n, p, a[N], cp[N];

void solve() {
    cin >> n >> p;
    for (int i = 0; i<n;i++) {
        cin >> a[i];
        cp[i] = a[i];
    }

    // the least significant bits are very important

    // If the first digit is k, and the number already has all digits up to k in it
    //  it will take exactly (m - k) moves where m is the largest digit not in our number

    // The only digits we should care about are the first digit, and the next digit that is not (p-1)
    //  Proof: If we can get the solution without (p - a[-1]) moves, only the first digit matters
    //      Otherwise the first digit will hit both (p-1) and 0 (the only digits that the numbers between our significant bits will take) and so they can be ignored

    // This is slow
    set<int> my_set(a, a+n);
    int lnd = p-1;
    while (my_set.count(lnd)) lnd--;
    int snd = 0;
    while (my_set.count(snd)) snd++;

    if (lnd == -1) {
        cout << 0 << '\n';
        return;
    }

    int i1 = n-1;
    int d1 = a[i1];
    if (d1 < snd) {
        cout << (lnd - d1) << '\n';
        return;
    }

    int i2 = n-2;
    for (; i2 >= 0 && a[i2] == p-1; i2--);
    if (i2 == -1) {
        if (d1 == 2)
            cout << (p - d1) << '\n';
        else
            cout << (p - 1) << '\n';
        return;
    }

    int d2 = a[i2];

    // We have touched everything geq d1
    // We have touched d2+1
    // We have touched 0
    // Everything else is the same

    // What is the new max that we havent touched

    int res = (p - d1);
    my_set.insert(d2 + 1);
    my_set.insert(0);

    int nmx = d1;
    while (my_set.count(nmx)) nmx -= 1;
    nmx = max(0, nmx);

    res += nmx;
    cout << res << '\n';
}

int main() {
    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
