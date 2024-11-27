// #!/bin/cpp

#include <bits/stdc++.h>
using namespace std;

int n; int x;
int c[500000 + 5] = { 0 };

int main() {
    cin >> n >> x;

    int tmp;
    for (int i = 0; i < n; i++) { cin >> tmp; c[tmp]++; }

    string res = "Yes";
    for (int i = 1; i < x; i++) {
        if (c[i] % (i+1) != 0) { res = "No"; break; }
        c[i+1] += c[i]/(i + 1);
    }
    cout << res;
}
