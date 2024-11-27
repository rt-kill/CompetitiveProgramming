#include <bits/stdc++.h>
using namespace std;

#define rep(i, s, n)  for(int i = s; i < (n); ++i)

struct Sort {
    bool operator()(int o1, int o2) {
        return o1 < o2;
    }
};

const int N = 5e5 + 5;
int n, x;
int a[N];
int counts[N] = { 0 };

int main() {
    cin >> n >> x;

    int tmp;
    rep(i, 0, n) cin >> tmp; counts[tmp] += 1;

    rep(i, 0, x) {
    }



    // Solution: compress terms
    // If a terms is less than x false, otherwise true

    //

    return 0;
}
