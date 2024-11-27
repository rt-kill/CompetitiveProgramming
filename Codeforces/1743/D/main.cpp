#include <bits/stdc++.h>
using namespace std;


int n;
string s;

string solve() {
    cin >> n;
    cin >> s;

    // s1 will be s[i:] where i is the index of the first 1
    // s2 will have length (len(s1) - j) where j is the index of the first 0 in s1

    int i = 0;
    while (i < s.size() && s[i] == '0') i++;
    if (i == s.size()) return "0";

    string s1 = s.substr(i);

    vector<int> zs;
    for (int l = 0; l < s1.size(); l++)
        if (s1[l] == '0')
            zs.push_back(l);
    if (zs.size() == 0) return s1;

    int s2s = s1.size() - zs[0];
    int b = 0; int fz = zs[0];

    for (int k = 0; k < zs[0]; k++) {
        // s2 = s1[k: s2s - k]
        // s2[0] = s1[k]
        // (s1 or s2)[i] = s1[i] or s2[i - zs[0]] = s1[i] or s1[k + i - zs[0]]
        int iz = 0;
        // (s1 or s2)[z] = (('0' * zs[0]) + s2)[z] = s2[z - zs[0]] = s1[k + z - zs[0]]
        while (iz < zs.size() && s1[k + zs[iz] - zs[0]] != '0') iz++;

        if (iz < zs.size() && zs[iz] >= fz) {
            fz = zs[iz];
            b = k;
        } else if (iz == zs.size()) {
            fz = s1.size();
            b = k;
        }
    }

    string s2 = s1.substr(b, s2s);
    for (int l = 0; l < s2.size(); l++)
        if (s2[l] == '1')
            s1[zs[0] + l] = '1';

    return s1;
}

int main() {
    cout << solve();
    return 0;
}
