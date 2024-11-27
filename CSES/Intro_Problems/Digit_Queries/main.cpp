#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll len(ll x) {
    ll l, l10=0, p10=1, sub=1;
    while(x>10*p10) l10++, p10*=10, sub += p10;
    l = 1 + (l10+1)*x - sub;
    return l;
}

ll ok(ll x, ll k) { return (len(x) <= k); }

void solve() {
    ll q, k;
    cin >> q;
    while(q--) {
        cin >> k;
        // let pos 0 be 0
        // ints of length 1 appear from [1,9]
        // ints of length 2 appear from [10, 2*99 + 1] = [10, 198]
        // ints of length 3 appear from [200, 3*999 + 2] = [200, 2998]
        // if we assume ints of length n appear from [(n-1)*10^{n-1}, n*10^n - 1]
        //  then ints of length n+1 would appear from [n*10^n, (n+1)*(10^{n+1} - 10^{n}) + n*10^n]
        //      = [n*10^n, (n+1)*(10^{n+1}) - 10^n]

        // For the firs 10 numbers, our string increases in length by 1 every time
        // For the next 90 numbers, our string increases in length by 2 every time
        // For the next 900 numbers, our string increases in length by 3 every time
        // For the next 9000 numbers, our string increases in length by 4 every time

        // Our string after x additions will have length
        //  1 + (x-1) + (x-10) + (x-100) + ... + (x - (10^floor(log(x)))
        //      = 1 + (floor(log(x)) + 1) * x - 111...11
        //      >= 1 + (floor(log(x)) + 1)*10^{floor(log(x))} - 11111...11
        //      >= (floor(log(x)))*10^{floor(log(x))}

        // What is the largest x st len(s(x)) < k
        // We can binary search


        ll x=0;
        for(ll b=(1e17 / 2); b>0; b>>=1)
            while(ok(x+b, k)) x+=b;

        string number = to_string(x);
        int pos = k - len(x);
        char res = number[pos];
        cout << res << '\n';
    }
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
