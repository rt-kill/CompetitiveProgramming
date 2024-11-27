#include <bits/stdc++.h>
using namespace std;

using ll = long long;

string s;
vector<int> counts('Z' - 'A' + 1);
vector<char> uc;

ll choose(int a, int b) {
    if (a == b) return 1;
    ll sub = choose(a-1, b);
    return (a * sub)/(a-b);
}

vector<char> bs;
void pbs() {
    for(auto c : bs) cout << c;
    cout << '\n';
}

void dfs(int k) {
    if (k == s.size()) {
        pbs();
        return;
    }

    for(auto c : uc) {
        if (counts[c - 'A'] > 0) {
            --counts[c-'A'];
            bs.push_back(c);

            dfs(k+1);

            ++counts[c-'A'];
            bs.pop_back();
        }
    }
}

void solve() {
    cin >> s;
    sort(s.begin(), s.end());
    for(auto c : s) ++counts[c - 'A'];

    uc = vector<char>(s.begin(), s.end());
    uc.erase( unique(uc.begin(), uc.end()), uc.end() );

    ll am = 1, lef = s.size();
    for(auto c : uc) {
        ll cc = counts[c - 'A'];
        ll choices = choose(lef, cc);
        am *= choices;
        lef -= cc;
    }

    cout << am << '\n';

    dfs(0);
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
