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
    int n;
    vi seg, lazy, children;

    void initSeg() {
        n = (1<<14);
        seg.assign(2*n, 1), lazy.assign(2*n, 0), children.assign(2*n, 1);
        Rof(i, 1, n) seg[i] = seg[2*i] + seg[2*i+1], children[i] = children[2*i] + children[2*i+1];
    }

    void prop(int k) {
        if (lazy[k]) {
            seg[k]=0;
            if (k < n) lazy[2*k]=1, lazy[2*k+1]=1;
            lazy[k]=0;
        }
    }

    int query(int l, int r, int cn, int cl, int cr) {
        prop(cn);

        if (cr < l || r < cl)   return 0;
        if (l <= cl && cr <= r) return seg[cn];

        int lhs = query(l, r, 2*cn, cl, (cl+cr)/2);
        int rhs = query(l, r, 2*cn+1, (cl+cr)/2+1, cr);
        return lhs + rhs;
    }

    int query(int k) {
        return query(0, k, 1, 0, n-1);
    }

    int select(int c, int cn) {
        prop(cn);
        if (cn >= n)        return cn - n;

        prop(2*cn), prop(2*cn+1);
        if (seg[2*cn] >= c) return select(c, 2*cn);
        else                return select(c-seg[2*cn], 2*cn+1);
    }

    int select(int c) {
        return select(c, 1);
    }

    int update(int l, int r, int cn, int cl, int cr) {
        prop(cn);

        if (cr < l || r < cl)   return seg[cn];
        if (l <= cl && cr <= r) { lazy[cn] = 1; return 0; }

        int lhs = update(l, r, 2*cn, cl, (cl+cr)/2);
        int rhs = update(l, r, 2*cn+1, (cl+cr)/2+1, cr);
        seg[cn] = lhs + rhs;
        return seg[cn];
    }

    void update(int l, int r) {
        update(l, r, 1, 0, n-1);
    }

public:
    int scheduleCourse(vector<vector<int>>& courses) {
        initSeg();

        each(course, courses) --course[1]; // 0 index days
        sort(all(courses));

        int res = 0;
        each(course, courses) {
            int d = course[0], ld = course[1];
            int room = query(ld);
            if (room < d) continue;

            ++res;
            int ind = select(room-d+1);
            update(ind, ld);
        }

        return res;

        /* vvpi buckets(1e4); */
        /* each(course, courses) { */
        /*     if (course[1] <= course[0]) continue; */
        /*     buckets[course[1] - course[0]].pb({course[0], course[1]}); */
        /* } */

        // suppose we have an array where a[i] is 1 if a class is being taken at that time, and 0 otherwise
        //  we use a bit for range query and update

        // in order of increasing d then ld
        //      check if there are at least d free time slots before ld
        //          to do this, range sum a[:ld]
        //      if so, find the index of the dth 0 before ld
        //      set all bits from this index to ld to 1

        // we prefer classes of minimal duration
        // in order of duration, if we can take the class, take it
        // additionally, take it as late as possible


        // assume as soluiton of length 1 exists

        // there exists a solution that contains the course for which (ld - d) is maximal
        //  if the course with maximal (ld - d) is not taken, we can easily replace the last taken course with it

        // if this course is taken last, we proceed on the subproblem
        // otherwise, there exists a solution for which this course is taken second to last
        //      suppose this class can not be swapped with the class to its right
        //          by maximality of (ld - d), the class afterwards starts ≤ (ld - d)
        //          since it can not be swapped, the class ends strictly after ld
        //          if there is another class after it, the class must have a larger (ld - d) contraditing maximality
        // additionally such a soluiton may contain the next course for which (ld - d) is maximal (via the same argument)

        // so we find some class c1 for which (ld - d) is maximal
        //  then we find class c2 ≠ c1 for which (ld - d) is maximal

        // sort the courses by (ld - d)
        //  for some i, there exists a solution with c[i] as the last class that contains all courses c[j] for j<i
        //      any soluiton has some last class, replace it with the smallest unused j < i
        //  additionally there exists such a soluion such that the last i+1 classes are c[:i]


        // after choosing an i, we calculate s := c[i].ld - sum{0-i}(d)
        //  then for each j>i, cmin(c[i].ld, s)


        // take c1 for which (ld-d) is maximal, with maximal ld
        //  if c1 can not go last, the last class must have a strictly larger ld, and thus a strictly smaller (ld-d)
        //  thus we would take all classes for which (ld-d) is the same as c1's
        //
    }
};

int main() {
    auto solution = Solution();

    vvi courses;
    int res;

    courses = { {100,200},{200,1300},{1000,1250},{2000,3200} }, res = solution.scheduleCourse(courses);
    pln(res);

    courses = { { 1, 2 } }, res = solution.scheduleCourse(courses);
    pln(res);

    courses = { {3,2},{4,3} }, res = solution.scheduleCourse(courses);
    pln(res);

    return 0;
}
