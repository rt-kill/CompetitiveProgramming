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
public:
    int findMinMoves(vector<int>& machines) {
        int n = machines.sz;
        int count = accumulate(all(machines), 0);
        if (count/n*n != count) return -1;

        int req = count/n;
        if (all_of(all(machines), [&req](auto m){ return m == req; })) return 0;

        vi pfx(all(machines));
        For(i, 1, n) pfx[i] += pfx[i-1];


        vi dp(n, 0), ft(n, 0);

        int i=0;
        while(i<n) {
            if (pfx[i] < (i+1)*req) {
                int l=i, r=i;
                while(pfx[r] < (r+1)*req) ++r;

                /* pr("F"); */
                /* pr(l, r); */
                /* ln(); */

                dp[r] = 0; // r is a resovoire
                Rof(i, l, r) dp[i] = max(0, dp[i+1]+1 - machines[i]); // continuous stream does not begin until one turn after the next dudes

                // ft[i] = [ time when i makes last move ] = [ max(0, offset - initial) + passes to be made ]
                ft[l] = 0, ft[r] += r*req - pfx[r-1];
                Rof(i, l+1, r) ft[i] = max(0, dp[i] - machines[i]) + (i*req - pfx[i-1]);

                i=r;

            } else if (pfx[i] > (i+1)*req){
                int l=i, r=i;
                while(pfx[r] > (r+1)*req) ++r;

                /* pr("S"); */
                /* pr(l, r); */
                /* ln(); */

                dp[l] = ft[l];
                For(i, l+1, r+1) dp[i] = max(0, dp[i-1]+1 - machines[i]); // same as above

                ft[l] += pfx[l] - (i+1)*req, ft[r] = 0;
                For(i, l+1, r) ft[i] = max(0, dp[i] - machines[i]) + (pfx[i] - (i+1)*req);

                i=r;

            } else ++i; // machine already has its assigned dresses
        }


        int res = *max_element(all(ft));
        return res;



        // I think that for machines that pass either left or right, the order in which they pass does not matter?
        //  strategy: find smallest i with enough clothes to fill up machines [0:i]
        //      solve m[i:] assuming i only passes right
        //



        // what if we first prioritize machine 1 getting all its dresses
        //  machine 1's dresses are spread out through machines 1-i
        //  in the first x turns (number of 1's dresses in machine i), machines 1-i will be out of commission (machine i can still recieve dresses)
        //      on turn x+1, machines 1-(i-1) will be out of commission
        //      etc...

        // semi-in parallel, we prioritize machine 2 getting its dresses

        // for any i, sum(m[:i+1]) + sum(m[i:])

        // two solutions i see:
        //  find the center
        //      only ever pass to the machine with less dresses
        //  find the center, and whose machines dresses it has


        // there will be exactly one i for which m[0:i] and m[i+1:] do not have enough dresses
        //  all machines to its left will only pass left
        //  all machines to its right will only pass right
        // from a different point of view, in a single move
        //  this machine passes a dress to the first 0, or last non-full machine on some side
        //  all machines on the other side pass if they can
        // there is no point for this center to pass to a machine with surplus (the machine does not immediately need it)


        // let i be the first machine with too many dresses
        //  all machines to its left will always pass left if they have a dress
        //  additionally, there is no point in machine i passing left until it will pass all needed dresses left
        //      that is, there exists a soluiton where before move k, machine i has passed 0 dresses left
        //          for the next t moves, it will pass left every turn
        //          after move k+t, it will never pass left again
        //  to see this:
        //      if we think of dresses as individual objects, each dress has a start machine and an end machine
        //          use the intuition below to see that the dresses machine i offloads left have a specific ending machine
        //

        // if for some 0, machines to its left still need dresses, we need to fill it as soon as possible
        //  same for 0's where machines to the right need dresses

        // lets try to think of dresses as individual objects
        //  we enumerate them:
        //  machine 0 has dresses (0, m[0]]
        //  machine 1 has dresses (m[0], m[1]]
        //  machine i has dresses (m[i-1], m[i]]
        // there exists an optimal solution where machine i ends up with dresses (req*i, req*(i+1)]
        //  every turn, a machine will dump some dress that does not belong to it either left or right
        //  in a way, in any continuous sequence of machines dumping left,
        //      the last machine imediately dumps to the first







        // there exists an optimal solution for which any single machine falls into only one of the following categories
        //  machine only recieves from right and only passes left
        //  machine only recieves from left and only passes right
        //  machine never recieves anything (can pass left or right)


        // machines that pass clothes have a total ammount that they will have passed at the end
        //  whenever they have some cloths and have not passed that ammount yet, they always pass





        // choose some l < r (maximal/minimal respectively )for which
        //  sum(machines[:l]) < req*(l+1)
        //  sum(machiles[r:]) < req*(n-r+1)
        // if no such l and r exist, then all machines already have an equal number of dresses


        // we have the following properties:
        //  machine l will never pass a dress right
        //  machine r will never pass a dress left

        // starting with just the left hand side:




        // if the first washing machine has >= req dresses, it will always be included in the first n-req moves
        //      additionally, the second machine will never pass left

        // select some washing machine i that has too many dresses
        //  if the machines to some side have too many dresses
        //      we ask two questions about the machines
        //          q1: what is the required time to make the machines all have req dresses
        //          q2: what is the required time to pass all the extra dresses to i
        //      clearly q2 ≤ q1 as in order to make all machines have req dresses, the surplus must be offloaded

        //      wlog, assume machines to its left have too many dresses
        //          if at some index j, machines to the left of j don't have enough dresses, j will never pass a dress to its right





    }
};



int main() {
    auto solution = Solution();

    vi machines;
    int res;

    machines = { 1, 0, 5 };
    res = solution.findMinMoves(machines);
    pln(res);

    machines = { 0, 3, 0 };
    res = solution.findMinMoves(machines);
    pln(res);

    machines = { 0, 2, 0 };
    res = solution.findMinMoves(machines);
    pln(res);



    // 0,0,4,0,5,0,5,0,4
    // 0,1,3,1,4,1,4,1,3
    // 1,1,3,1,4,1,3,2,2
    // 2,1,3,1,3,2,2,2,2
    // 2,2,2,2,2,2,2,2,2
    machines = { 0,0,4,0,5,0,5,0,4 };
    res = solution.findMinMoves(machines);
    pln(res);

    return 0;
}
