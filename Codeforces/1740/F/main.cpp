#include <bits/stdc++.h>
using namespace std;

int n, a[2009];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    sort(a, a + n);

    // The most multiset can be made when no two terms in a are the same
    // any multiset that can be made if a[i] == a[j], can be made if a[i] != a[j]

    // one multi set with n ones
    // if two terms are not the same, there will be a multi set with one 2 and n-2 ones

    // What is the most nubmer of multisets we can make?
}
