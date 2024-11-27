#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    int s,n; cin >> s >> n;
    vector<int> no(n); vector<int> yes(n); int x; char q;
    for (int i=0; i<n; i++) {
        cin >> x >> q;
        if (q == 'n') {
            no.push_back(x);
        } else {
            yes.push_back(x);
        }
    }

    sort(no.begin(), no.end());
    sort(yes.begin(), yes.end());
    int curryes = 0;
    int currno = 0;
    bool occupied = false;
    bool nodone = false;
    bool yesdone = false;
    for (int t = 1; t < n/s + 2; t++) {
        for (int i = 0; i < s; i++) {
            if ((yes[curryes] <= no[currno] && yes[curryes] <= t && !occupied) || nodone) {
                curryes++; occupied = true;
                if (curryes >= yes.size()) {yesdone = true;}
            } else if ((no[currno] < yes[curryes] || occupied) && no[currno] <= t) {
                currno++;
                if (currno >= no.size()) {nodone = true;}
            } else if (nodone && occupied) {
                continue;
            } else {
                cout << "No" << endl;
                return;
            }
        }
        occupied = false;
        if (nodone && yesdone) {
            break;
        }
    }
    cout << "Yes" << endl;
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
