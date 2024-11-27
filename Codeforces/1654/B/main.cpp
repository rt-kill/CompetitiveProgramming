#include <bits/stdc++.h>
using namespace std;

using ll = long long;

string s;

void solve() {
    cin >> s;

    // The "tail" of a word will never be deleted
    //  the maximal substring that extends to the end and doesn't repeat the first element.
    //  everyother substring will be shrunk

    set<int> chars;
    for (char c : s)
        chars.insert(c);

    int i = s.size();
    while(!chars.empty()) {
        i -= 1;
        chars.erase(s[i]);
    }

    for (; i<s.size(); i++)
        cout << s[i];
    cout << '\n';
}

int main() {
    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
