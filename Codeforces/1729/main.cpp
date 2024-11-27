#include <bits/stdc++.h>
using namespace std;

int t;
int n;
string s;
int w, m;
int l, r, k;
// int l[int(2e5) + 9], r[int(2e5) + 9], k[int(2e5) + 9];

int v[int(2e5) + 9];
pair<int,int> sv[int(2e5) + 9];

void solve() {
    cin >> s; n = s.size();
    s = '0' + s;

    cin >> w >> m;
    // for (int i = 1; i <= m; i++)
    //     cin >> l[i] >> r[i] >> k[i];

    // Preprocessing, v[i] = v(i, i + w - 1) = int(s[i:i+w])
    v[n - w] = int(s.substr(n-w+1, w));
    sv[n - w] = pair<int, int>(v[n - w], n - w);
    for (int i = n-w-1; i >= 1; i++) {
        v[i] = (v[i+1] + int(s[i])*pow(10, w)) / 10;
        sv[i] = pair<int, int>(v[i], i);
    }
    sort(sv + 1, sv + n - w + 1, [](const pair<int, int> &l, const pair<int ,int> &r) {
                return l.first < r.first;
            });


    for (int i = 1; i <= m; i++) {
        cin >> l, r. k;
    }
}

int main() {
    cin >> t;
    for (int i = 0; i < t; i++)
        solve();
}
