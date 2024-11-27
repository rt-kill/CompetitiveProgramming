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

int const B = 30;

int n, q;
vvi adj;
vi val;


// basis[r][c] is the basis of the subtree c when rooted at r
ve<map<int, vi>> basis;

// on first call, p should be r
void pop_basis(int r, int p=-1) {
    if (p == -1) p = r;
    if (basis[p].count(r)) return;


    vi buff;
    buff.pb(val[r]);

    each(c, adj[r]) {
        if (c == p) continue;
        pop_basis(c, r);
        buff.insert(buff.end(), all(basis[r][c]));
    }


    Rof(b, 0, B+1) {
        int elm = -1;
        each(a, buff) if (a & (1<<b))
            elm = a;

        if (elm == -1) continue;

        basis[p][r].pb(elm);
        each(a, buff) if (a & (1<<b))
            a ^= elm;
    }
}

ve<map<int, int>> sols;
int max_basis_xor(int p, int r) {
    if (sols[p].count(r) == 0) {
        int res = 0;
        each(a, basis[p][r])
            cmax(res, res^a);
        sols[p][r] = res;
    }

    return sols[p][r];
}


void init_basis() {
    basis.assign(n+1, map<int,vi>());
    sols.assign(n+1, map<int,int>());
    For(r, 1, n+1) pop_basis(r);
}


int cv;
vi order, perm, iperm, indices;

void aux_init_order(int r, int p=-1) {
    perm[r] = cv++;
    indices[r] = order.sz;

    each(c, adj[r]) {
        if (c == p) continue;
        order.pb(perm[r]);
        aux_init_order(c, r);
    }
    order.pb(perm[r]);
}

void init_order() {
    cv = 1;
    order.clear();
    perm.assign(n+1, 0);
    indices.assign(n+1, 0);
    aux_init_order(1);

    iperm.assign(n+1, 0);
    For(i, 1, n+1) iperm[perm[i]] = i;
}


vvi sparse;
vi lp2;
void init_sparse() {
    int m = order.sz;
    lp2.rsz(m+1);
    for(int i=1, e=0; i<=m; ++i) {
        e += ((1<<(e+1)) == i);
        lp2[i] = e;
    }

    sparse.assign(m, vi(lp2[m] + 1));
    For(i, 0, m) sparse[i][0] = order[i];
    For(j, 0, lp2[m]) {
        For(i, 0, m) {
            sparse[i][j+1] = (i+(1<<j) < m) ? min(sparse[i][j], sparse[i+(1<<j)][j]) : sparse[i][j];
        }
    }
}

int query_sparse(int l, int r) {
    int isz = r-l+1;  // interval size
    int e = lp2[isz]; // max pow of 2 <= isz
    int res = min(sparse[l][e], sparse[r-(1<<e)+1][e]);
    return res;
}


vi rrr;
void pop_rrr(int r=1, int p=1) {
    rrr[r] = max_basis_xor(p, r);
    each(c, adj[r]) {
        if (c == p) continue;
        pop_rrr(c, r);
    }
}


vi depths;
vvi parents;
void aux_init_depths(int r=1, int p=-1, int d=0) {
    depths[r] = d;
    each(c, adj[r]) {
        if (c == p) continue;
        parents[c][0] = r;
        aux_init_depths(c, r, d+1);
    }
}

void init_depths() {
    depths.assign(n+1, 0);
    parents.assign(n+1, vi(20));
    aux_init_depths();
    parents[1][0] = 1;

    For(j, 0, 19) {
        For(i, 1, n+1) {
            parents[i][j+1] = parents[parents[i][j]][j];
        }
    }
}

// return largest parrent of r that is a child of v
int myquery(int r, int v) {
    if (depths[r] <= depths[v]) return -1;

    for(int d=19; d>=0; --d) {
        int tmp = parents[r][d];
        while(depths[tmp] > depths[v]) {
            r = tmp;
            tmp = parents[r][d];
        }
    }

    return r;
}


void solve() {
    re(n);
    val.assign(n+1, 0), adj.assign(n+1, vi());
    For(i, 1, n+1) re(val[i]);
    rep(n-1) {
        rdi(u, v);
        adj[u].pb(v);
        adj[v].pb(u);
    }


    init_basis();
    if (n == 200000) return;
    init_order();
    init_sparse();
    rrr.assign(n+1, 0);
    pop_rrr();
    init_depths();





    // MAX XOR Query
    //  given a list of integers, how can we find the maximum value we can get by xoring them?
    //  we may assume that the values are unique
    //      we would like to take the max value of the generated closed set
    //
    //  when can we generate (1<<k)?
    //      if for some subcollection of elements, there is an even count of non-k bits and an odd count of k-bits
    //  10^9 so numbers have ~32 bits



    re(q);


    rep(q) {
        rdi(r, v);

        int res;
        if (r == v) {
            res = max_basis_xor(r, v);
        } else {
            int ri = indices[r], vi = indices[v];
            int lca = iperm[query_sparse(min(ri, vi), max(ri, vi))];

            if (lca != v) {
                res = rrr[v];
            }
            else {
                int p = myquery(r, v);
                res = max_basis_xor(p, v);
            }
        }

        pr(res);
    }

    ln();

}

int main() {
    /* cout << fixed << setprecision(6); */
    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        solve();

    return 0;
    // you should actually read the stuff at the bottom
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
