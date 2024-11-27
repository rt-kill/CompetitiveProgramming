#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int const max_val = 1e9;
int sqrt_max_val;

vector<int> primes;
void populate_primes(int N) {
    vector<bool> is_prime(N+1, true);
    for(int p=2; p<=N; ++p) {
        if(is_prime[p])
            for(int q=p*p; q<=N; q+=p)
                is_prime[q] = 0;
    }

    for(int p=2; p <= N; ++p) if (is_prime[p])
        primes.push_back(p);
}

void solve() {
    int n;
    cin >> n;

    vector<ll> a(n);

    int tmp;
    for(int i=0; i<n; i++) {
        cin >> tmp;
        a[i] = tmp;
    }

    for(auto p : primes) {
        int count = 0;
        for(int i=0; i<n; i++) {
            count += (a[i] % p == 0);
            while(a[i] % p == 0) a[i] /= p;
        }

        if (count > 1) {
            cout << "Yes" << '\n';
            return;
        }
    }

    vector<int> na;
    copy_if(a.begin(), a.end(), back_inserter(na), [](auto v){return v != 1;});
    set<int> sa(na.begin(), na.end());


    if (sa.size() == na.size()) cout << "No" << '\n';
    else cout << "Yes" << '\n';
}

int main() {
    sqrt_max_val = sqrt(max_val);
    populate_primes(sqrt_max_val);

    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
