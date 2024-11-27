#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll ta, tb;
string a, b;

ll ma[20][11][2] = {};
ll dpa(int k=0, char prev=('9'+1), bool lt=0) {
    if(k == a.size()) return 1;
    if(ma[k][prev - '0'][lt] > 0)
        return ma[k][prev - '0'][lt];

    ll res = 0;
    for(char i='0'; i<='9'; ++i) {
        if (i == prev) continue;
        if (!lt && i > a[k]) continue;

        if (prev == ('9' + 1) && i == '0')
            res += dpa(k+1, '9' + 1, 1);
        else
            res += dpa(k+1, i, lt || (i < a[k]));
    }

    ma[k][prev - '0'][lt] = res;
    return res;
}

ll mb[20][11][2] = {};
ll dpb(int k=0, char prev=('9'+1), bool lt=0) {
    if(k == b.size()) return 1;
    if(mb[k][prev - '0'][lt] > 0) return mb[k][prev - '0'][lt];

    ll res = 0;
    for(char i='0'; i<='9'; ++i) {
        if (i == prev) continue;
        if (!lt && i > b[k]) continue;

        if (prev == ('9' + 1) && i == '0')
            res += dpb(k+1, '9' + 1, 1);
        else
            res += dpb(k+1, i, lt || (i < b[k]));
    }

    mb[k][prev - '0'][lt] = res;
    return res;
}

void solve() {
    cin >> ta >> tb;
    --ta;
    a = to_string(ta), b = to_string(tb);

    ll res = dpb();
    if (ta >= 0) res -= dpa();

    cout << res << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
