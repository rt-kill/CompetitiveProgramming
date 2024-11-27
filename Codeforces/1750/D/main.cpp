#include <bits/stdc++.h>
using namespace std;

int const MM = 998244353;
using ll = long long;
int n, m, a[int(2e5) + 9];

vector<int> primes;
void factorize(int f) {
    primes.clear();
    for(int p=2;(p*p)<=f;p++) {
        if(f%p == 0) {
            primes.push_back(p);
        }
        while(f%p == 0)
            f/=p;
    }
    if (f > 1)
        primes.push_back(f);
}

// How many values for b[i] can there be
int b_ops(int i) {
    int val = a[i]/a[i+1]; // gcd(a[i], b[i+1]) = a[i+1] <-> gcd(a[i]/a[i+1], b[i+1]/a[i+1]) = 1;
    factorize(val);
    for(auto p : primes)
        cout << p << ' ';
    cout << '\n';

    int M = m/a[i+1];

    ll res = 0;
    for(int i=0;i<(1<<primes.size());i++){
        cout << bitset<10>(i) << '\n';
        int c=0,t=i,mult=1,ind=0;
        while(t>0) {
            if (t&1) {
                c++;
                mult*=primes[ind];
            }

            ind++;
            t>>=1;
        }

        int par = c&1 ? -1 : 1;
        res += par*(M/mult);
    }

    cout << res << '\n';

    return (res%MM);

    // How many values 1 <= k <= m/a[i+1] are there for which gcd(val, k) = 1?
    // How many values 1 <= k <= m/a[i+1] are there for which gcd(val, k) > 1?
    //  for each p in primes, there are M/p multiples of p
    //  for each (p,q) in primes^2, we count M/(pq) multiples in both p and q
    //  for each (p,q,r) in primes^3, we count M/(pqr) multiples
    //      in p q and r
    //      in pq, pr, qr
    //  for (p1,...,pj) in primes we cound M/(p1...pj) multiples
    //      in p1,...,pj
    //      in (j choose 2)...
    //      in (j choose 3)...

    // (M/p1 + M/p2 - M/(p1p2)) + M/p3 - M/(p1p3) - M/(p2p3) + M/(p1p2p3)

    //  for each p in primes, there are M/p multiples of p
    //  for each (p,q) in primes^2, we count M/(pq) twice
    //  for each (p,q,r) in primes^3, we count M/(pqr)
    //      three times over single primes (p q and r)
    //      three times over 2 primes (pq, pr, qr)
    //  for (p1,...,pj) in primes we cound M/(p1...pj) multiples
    //      in p1,...,pj
    //      in (j choose 2)...
    //      in (j choose 3)...
}

void solve() {
    cin >> n >> m;
    for(int i=0;i<n;i++)
        cin >> a[i];

    for(int i=0;i<n-1;i++)
        if (a[i] % a[i+1] != 0) { // a[i+1] must divide a[i]
            cout << 0 << '\n';
            return;
        }

    int res = 1;
    for(int i=0;i<n-1;i++) {
        // for how many nubmers b<=m is gcd(a[i-1], b) = a[i]
        // how many numbers are relatively prime to a[i-1]/a[i]
        // what prime factors does a[i-1]/a[i] have
        //  Suppose we know that p is the set of prime factors not in a[i-1]/a[i] leq m
        //  what numbers are not relatively prime to a[i-1]/a[i] -- what numbers share a common divisor
        //  for each


        res = (res * b_ops(i))%MM;
    }

    cout << res << '\n';

    // we notice that b[0] = a[0] always
    // gcd(b[0], b[1]) = a[1]

    // we notice that a[i] divides a[j] for i <= j
    //  This is because a[j] divides b[i] for all i <= j

    // notice gcd(b1,...,bi) = gcd(gcd(b1,...,bi-1), bi) = gcd(ai-1, bi)
    //  It also follows that b[i] is "independent" of b[j] for all j < i

    // If we want to factorize a, we first factorize a[n], then a[n-1]/a[n], then ...
}

int main() {
    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        cout << '\n' << "TEST " << i << '\n', solve();

    return 0;
}
