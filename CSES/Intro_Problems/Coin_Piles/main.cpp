#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int a, b;
void solve() {
    cin >> a >> b;
    // |1 2| * |x| = |a|
    // |2 1| * |y| = |b|

    // A := this matrix
    // det(A) = -3

    //          |-1/3  2/3|
    // inv(A) = | 2/3 -1/3|

    // Question: is inv(A) * (a, b) positive integral
    // Revised Question: is 3*inv(A) * (a, b) positive divisible by 3

    int x = -a + 2*b;
    int y = 2*a - b;

    if (min(x, y) >= 0 && 3*(x/3) == x && 3*(y/3) == y)
        cout << "YES" << '\n';
    else
        cout << "NO" << '\n';
}

int main() {
    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
