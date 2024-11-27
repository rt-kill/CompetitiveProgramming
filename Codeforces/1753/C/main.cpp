#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MM=998244353; // PRIME

int t=1, n, a[int(2e5) + 9];
int nz, nb;

int invmm(int q) {
    // since MM is prime, in Z(MM) as long as q is non-zero, there exists an inverse element mod MM
    // by fermat, q*q^{p-2} == 1 (MOD p)

    ll b=q; ll off=1; int p=MM-2;

    while(p>1){
        if(p&1) {
            off=(off*b)%MM;
            p-=1;
        }
        if(p>=2) {
            b=(b*b)%MM;
            p/=2;
        }
    }

    return (b*off)%MM;
}

int dp[int(2e5) + 9] = {};

void solve() {
    cin>>n;
    for (int i=0;i<n;i++)
        cin>>a[i];

    // a move i only good if we select a 1 where a 0 should be and a 0 where a 1 should be
    // there should be 0's in the first #0 positions
    // there should be 1's in the last #1 positions (=n-#0)
    // supposing there are x 1's in the first #0 positions (and thus x0's in the last #1 positions), the probability of making a good move is (x^2)/(n choose 2)
    // using the equation for ev in terms of x
    //  ev(x) = p(b)ev(x) p(g)ev(x-1) + 1 -> ev(x) = (p(g)ev(x-1) + 1)/p(g) = ev(x-1) + 1/p(g)
    // via induction, we see
    //  ev(x) = 1/g(x) + 1/g(x-1) + 1/g(x-2) + ... + 1/g(1) + ev(0)

    int nc2 = ll(n)*ll(n-1)/2%MM;
    nz=n;nb=0;
    for (int i=0;i<n;i++) nz-=a[i];
    for (int i=0;i<nz;i++) nb+=a[i];
    for (int i=1;i<=nb;i++) dp[i] = (dp[i-1] + (ll(nc2)*ll(invmm(ll(i)*ll(i)%MM))%MM))%MM;
    cout << dp[nb] << '\n';
}

int main() {
    cin>>t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
