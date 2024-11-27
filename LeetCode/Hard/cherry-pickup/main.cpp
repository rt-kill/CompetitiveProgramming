#include <bits/stdc++.h>
using namespace std;

/* Macros {{{ */
/* Basics {{{ */
using ll    = long long;
using ull   = unsigned long long;
using ld    = long double;
using str   = string;

using pi    = pair<int,int>;
using pll   = pair<ll, ll>;
using pld   = pair<ld, ld>;

using vi    = vector<int>;
using vll   = vector<ll>;
using vld   = vector<ld>;

using vpi   = vector<pi>;
using vpll  = vector<pll>;
using vpld  = vector<pld>;

using vvi   = vector<vi>;
using vvll  = vector<vll>;
using vvld  = vector<vld>;

using vvpi  = vector<vpi>;
using vvpll = vector<vpll>;
using vvpld = vector<vpld>;

#define arr     array
#define ve      vector
#define pb      push_back
#define rsz(a)  resize(a)
#define mp      make_pair
#define fi      first
#define se      second
#define all(x)  x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define sz      size()

#define For(i, a, b)    for(int i=a; i<b; ++i)
#define Rof(i, a, b)    for(int i = (b)-1; i >= (a); --i)
#define rep(a)          For(_, 0, a)
#define each(a, x)      for(auto &a : x)
#define reach(a, x)     for(auto a = x.rbegin(); a != x.rend(); ++a)

template<typename T, typename U> inline void cmin(T &x, U y) { if(y < x) x = y; }
template<typename T, typename U> inline void cmax(T &x, U y) { if(x < y) x = y; }
/*}}}*/

/* IO {{{ */
// Read
#define _re_(a)     cin >> a;
#define re(...)     FOR_EACH(_re_, __VA_ARGS__)

#define rev(a, x)   x.rsz(a); each(b, x) _re_(b);
#define rewv(a, x)  _re_(a); rev(a, x);

#define _rdi_(a)    int a; _re_(a)
#define rdi(...)    FOR_EACH(_rdi_, __VA_ARGS__)

#define _rdll_(a)   ll a; _re_(a)
#define rdll(...)   FOR_EACH(_rdll_, __VA_ARGS__)

#define _pr_(a)     cout << a << ' ';
#define pr(...)     FOR_EACH(_pr_, __VA_ARGS__)

#define _ln_(...)       cout << '\n';
#define ln()            cout << '\n';
#define _pln_aux_(a)    cout << a << '\n';
#define _pln_(...)      FOR_EACH(_pln_aux_, __VA_ARGS__)
/* #define _pln_fork_(...) TENTH_PARAM(__VA_ARGS__,_pln_,_pln_,_pln_,_pln_,_pln_,_pln_,_pln_,_pln_,_ln_)(__VA_ARGS__) */
#define pln(...)        _pln_(__VA_ARGS__)

/* IO - Helpers {{{*/
#define TENTH_PARAM(_0,_1,_2,_3,_4,_5,_6,_7,_8,NAME,...) NAME

#define PARENS ()
#define EXPAND(arg)     EXPAND1(EXPAND1(EXPAND1(EXPAND1(arg))))
#define EXPAND1(arg)    EXPAND2(EXPAND2(EXPAND2(EXPAND2(arg))))
#define EXPAND2(arg)    EXPAND3(EXPAND3(EXPAND3(EXPAND3(arg))))
#define EXPAND3(arg)    EXPAND4(EXPAND4(EXPAND4(EXPAND4(arg))))
#define EXPAND4(arg)    arg

#define FOR_EACH(macro, ...)                                    \
  __VA_OPT__(EXPAND(FOR_EACH_HELPER(macro, __VA_ARGS__)))
#define FOR_EACH_HELPER(macro, a1, ...)                         \
  macro(a1)                                                     \
  __VA_OPT__(FOR_EACH_AGAIN PARENS (macro, __VA_ARGS__))
#define FOR_EACH_AGAIN() FOR_EACH_HELPER
/*}}}*//*}}}*//*}}}*/

class Solution {
private:
    vector<arr<int, 4>> diffs = { { -1, 0, -1, 0 }, { -1, 0, 0, -1 }, { 0, -1, -1, 0 }, { 0, -1, 0, -1 } };
public:

    int cherryPickup(vector<vector<int>>& grid) {
        int R = grid.sz, C = grid[0].sz;

        int dc = R + C - 1;
        ve<ve<vvi>> memory(R, ve<vvi>(C, vvi(R, vi(C, -1))));
        memory[0][0][0][0] = grid[0][0];

        For(d, 1, dc) {
            int mr = max(0, d - (C-1)), Mr = min(d, R-1);
            For(r1, mr, Mr+1) For(r2, r1, Mr+1) {
                int c1 = d - r1, c2 = d - r2;

                memory[r1][c1][r2][c2] = -1;
                if (grid[r1][c1] < 0 || grid[r2][c2] < 0) continue;

                for(auto [dr1, dc1, dr2, dc2] : diffs) {
                    int nr1 = r1 + dr1, nc1 = c1 + dc1;
                    if (nr1 < 0 || nr1 >= R || nc1 < 0 || nc1 >= C) continue;

                    int nr2 = r2 + dr2, nc2 = c2 + dc2;
                    if (nr2 < 0 || nr2 >= R || nc2 < 0 || nc2 >= C) continue;

                    cmax(memory[r1][c1][r2][c2], memory[nr1][nc1][nr2][nc2]);
                }

                if (memory[r1][c1][r2][c2] >= 0) memory[r1][c1][r2][c2] += grid[r1][c1] + (r1 != r2) * grid[r2][c2];
            }
        }

        int res = max(0, memory[R-1][C-1][R-1][C-1]);
        return res;
    }
};

int main() {
    auto solution = Solution();
    vvi grid;
    int res;

    grid = {{0,1,-1},{1,0,-1},{1,1,1}}, res = solution.cherryPickup(grid);
    pln(res);

    grid = {{1,1,-1},{1,-1,1},{-1,1,1}}, res = solution.cherryPickup(grid);
    pln(res);

    return 0;
}
