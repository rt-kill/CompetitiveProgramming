#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n = 8;
string board[8];

int dd(int r, int c) { return r - c + n - 1; }
int ud(int r, int c) { return r + c; }

bool cc[8]={}, ddc[15]={}, udc[15]={};

int dfs(int r) {
    if(r == n) return 1;

    int res = 0;
    for(int c=0;c<n;c++) {
        if(board[r][c] != '*' && !cc[c] && !ddc[dd(r, c)] && !udc[ud(r, c)]) {
            cc[c]=1, ddc[dd(r, c)]=1, udc[ud(r, c)]=1;
            res += dfs(r+1);
            cc[c]=0, ddc[dd(r, c)]=0, udc[ud(r, c)]=0;
        }
    }

    return res;
}

void solve() {
    for(int i=0;i<n;i++)
        cin >> board[i];

    int res = dfs(0);
    cout << res << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();


    return 0;
}
