#include <bits/stdc++.h>
using namespace std;

/* Macros {{{ */
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ii = pair<int,int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
using vvi = vector<vi>;
using vvll = vector<vll>;
using vvii = vector<vii>;

#define arr array
#define ve vector
#define pb push_back
#define rsz(a) resize(a)
#define mp make_pair
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define sz size()

#define For(i, a, b) for(int i=a; i<b; ++i)
#define Rof(i, a, b) for(int i = (b)-1; i >= (a); --i)
#define rep(a) For(_, 0, a)
#define each(a, x) for (auto &a : x)
#define reach(a, x) for (auto a = x.rbegin(); a != x.rend(); ++a)
/* }}} */

vvi t;
vi v;

struct treeNode {
    int *seg;
    int size;
    int exitPoint; // point you must reach to travel to parrent
    int enterPoint; // point you enter the parrent at
    struct treeNode *parrent;
};

vi myMap1; // a map from nodes in (1-n) to their location in their corresponding treeNode
vector<struct treeNode *> myMap2;
vi depth;

int used[(int) 2e5 + 1] = {};

ii lpAux(int r, int p=-1) {/*{{{*/
    ii res = {-1, r};
    each(c, t[r]) {
        if (c == p || used[c]) continue;
        res = max(res, lpAux(c, r));
    }

    ++res.fi;
    return res;
}

vi myPath;
int pathBuilder(int r, int tar, int p = -1) {
    if (r == tar) {
        myPath.pb(r);
        return 1;
    }

    each(c, t[r]) {
        if (c == p || used[c]) continue;
        if (pathBuilder(c, tar, r)) {
            myPath.pb(r);
            return 1;
        }
    }

    return 0;
}

void longestPath(int r) {
    ii p1 = lpAux(r); ii p2 = lpAux(p1.se);
    myPath.clear();
    pathBuilder(p1.se, p2.se);
}/*}}}*/

void rec(int r=1, int flag=0) {
    longestPath(r);
    vi pathCopy(all(myPath));
    int pl = pathCopy.sz;

    For(i, 0, pl) used[pathCopy[i]] = 1;
    if(flag && !used[r]) rec(r);

    struct treeNode *parr=NULL;
    int d=INT_MAX, exp=-1, enp=-1;

    each(v, pathCopy) each(c, t[v])
        if (used[c] && depth[c] < d) {
            enp = c, exp = v;
            d = depth[c] + 1;
            parr = myMap2[c];
            break;
        }

    int *mySeg = (int*) malloc(2*pl * sizeof(int));
    For(i, 0, pl) mySeg[i + pl] = v[pathCopy[i]];
    Rof(i, 1, pl) mySeg[i] = max(mySeg[2*i], mySeg[2*i + 1]);
    mySeg[0] = 0;

    struct treeNode *node = (struct treeNode*) malloc(sizeof(struct treeNode));
    node -> seg = mySeg;
    node -> size = pl;
    node -> exitPoint = exp;
    node -> enterPoint = enp;
    node -> parrent = parr;

    For(i, 0, pl) {
        myMap1[pathCopy[i]] = i;
        myMap2[pathCopy[i]] = node;
        depth[pathCopy[i]] = d;
    }

    each(v, pathCopy) {
        each(c, t[v]) {
            if (used[c]) continue;
            rec(c);
        }
    }
}

void updateTn(int r, int nv) {
    int i = myMap1[r];
    struct treeNode *node = myMap2[r];
    int siz = node -> size;
    int *mySeg = node -> seg;

    mySeg[i + siz] = nv;
    for(int j=((i + siz)>>1); j>0; j>>=1) {
        mySeg[j] = max(mySeg[2*j], mySeg[2*j + 1]);
    }
}

int querySeg(int l, int r, int siz, int *mySeg) {
    int res = 0;
    if (l > r) swap(l, r);

    l += siz, r += siz;

    while(l <= r) {
        if (l&1) res = max(res, mySeg[l++]);
        if (!(r&1)) res = max(res, mySeg[r--]);
        l>>=1, r>>=1;
    }

    return res;
}

ii queryExit(int r) {
    int i = myMap1[r];
    struct treeNode *node = myMap2[r];
    int siz = node -> size;
    int *mySeg = node -> seg;
    int exp = node -> exitPoint;
    int enp = node -> enterPoint;

    int c = querySeg(myMap1[r], myMap1[exp], siz, mySeg);
    return { c, enp };
}

int querySame(int a, int b) {
    if (myMap2[a] != myMap2[b]) return -1;

    struct treeNode *node = myMap2[a];
    int siz = node -> size;
    int *mySeg = node -> seg;

    int l = myMap1[a];
    int r = myMap1[b];

    int c = querySeg(l, r, siz, mySeg);
    return c;
}

int query(int a, int b) {
    int res = 0;
    if (depth[a] < depth[b]) swap(a, b);

    while(depth[a] > depth[b]) {
        auto [ c, na ] = queryExit(a);
        res = max(res, c);
        a = na;
    }

    while(myMap2[a] != myMap2[b]) {
        auto [ c1, na ] = queryExit(a);
        res = max(res, c1);
        a = na;

        auto [ c2, nb ] = queryExit(b);
        res = max(res, c2);
        b = nb;
    }

    auto fc = querySame(a, b);
    res = max(res, fc);

    return res;
}


int n, q;
void solve() {
    cin >> n >> q;
    v.rsz(n+1), t.rsz(n+1);
    For(i, 1, n+1) cin >> v[i];
    rep(n-1) {
        int a, b;
        cin >> a >> b;
        t[a].pb(b);
        t[b].pb(a);
    }

    myMap1.rsz(n+1), myMap2.rsz(n+1), depth.rsz(n+1);
    rec();

    rep(q) {
        int type, a, b; cin >> type >> a >> b;
        /* cout << type << ' ' << a << ' ' << b << '\n'; */
        if (type == 1) {
            updateTn(a, b);
        } else {
            int re = query(a, b);
            cout << re << ' ';
        }
    }

    cout << '\n';




    // Find longest path in graph: O(n)
    // if longest path is <= sqrt(n), every query can be easily processed in sqrt(n) time brute force
    //      Simple: Root the tree, move nodes up until they are the same
    //      This might not even be needed

    // Otherwise, we can "remove" this path, and have a manual max-seg tree over it
    //  we will be left with many components,
    //  each component can have a path of length at most (ML/2)

    // For each component, find the max length of a path in it
    //  Over components with a path of length > sqrt(n), delete and repeat
    //  Total: O(n) per "whole step"
    //  max length paths of component decrease by a factor of 2 each time, so at most log(n) iterations

    // the final structure will be
    //  max-seg
    //  exit point
    //  parrent structure

    // we continue with a union find data structure for nodes to find their corresponding max seg
    // from here, we query query query

    // we convert a tree to a tree of seg-trees!
}

int main() {
    int t=1;
    /* cin >> t; */
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
