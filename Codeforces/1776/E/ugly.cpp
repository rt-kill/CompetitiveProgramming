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

#define rewv(a, x)  _re_(a); x.rsz(a); each(b, x) _re_(b);

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


int n, m, s, v;
ve<arr<int, 4>> trains;
ve<ve<arr<int, 4>>> tracks;

class Node {
public:
    int track, ptrain, ntrain, startTime, endTime;
    ve<arr<int, 3>> doublePaths, speedPaths;

    Node(int Track, int Ptrain, int Ntrain, int StartTime, int EndTime) {
        track = Track, ptrain = Ptrain, ntrain = Ntrain, startTime = StartTime, endTime = EndTime;
    }

    void appendDoublePath(int startTime, int endTime, int endNode) {
        doublePaths.push_back({startTime, endTime, endNode});
    }

    void appendSpeedPath(int startTime, int endTime, int endNode) {
        speedPaths.push_back({startTime, endTime, endNode});
    }

    void sortPaths() {
        sort(all(doublePaths));
        sort(all(speedPaths));
    }
};


ve<Node> nodes;
vi nodeAbove, nodeBelow;





void solve() {
    re(n, m, s, v);
    trains.rsz(n), tracks.rsz(m);
    For(i, 0, n) {
        arr<int, 4> &train = trains[i];
        re(train[0], train[1], train[2]);
        --train[2], train[3] = i;
        tracks[train[2]].pb(train);
    };

    For(i, 0, m) {
        ve<arr<int, 4>> &track = tracks[i];
        sort(all(track));

        For(j, 0, track.sz+1) {
            int ptrain = (j > 0) ? track[j-1][3] : -1;
            int ntrain = (j < track.sz) ? track[j][3] : n;

            int startTime = (ptrain >= 0) ? trains[ptrain][1] : 0;
            int endTime = (ntrain < n) ? trains[ntrain][0] : s;

            Node cur(i, ptrain, ntrain, startTime, endTime);

            nodes.pb(cur);
            if (ptrain >= 0) nodeAbove[ptrain] = int(nodes.sz)-1;
            if (ntrain < n) nodeBelow[ntrain] = int(nodes.sz)-1;
        }
    }

    // finds paths that touch two start/stops
    For(leftTrack, 0, m) For(rightTrack, leftTrack+1, m) {
        int distance = rightTrack - leftTrack;

        each(leftTrain, tracks[leftTrack]) each(rightTrain, tracks[rightTrack]) {
            vi leftTimes = {leftTrain[0], leftTrain[1]};
            vi rightTimes = {rightTrain[0], rightTrain[1]};

            For(i, 0, 2) For(j, 0, 2) {
                int st = leftTimes[i], et = rightTimes[i];
                int timeDelta = et - st;
                if (timeDelta < distance*v) continue;

                int good = 1;
                For(midTrack, leftTrack+1, rightTrack) {
                    upper_bound(all(tracks[midTrack]), {  });
                }
            }
        }
    }






    // we can think of a 2d grid, where the x axis are the tracks, and the y axis is time
    //      x is in [0, m+1], y is in [0, s]
    //  we can put wall starts and ends according to the trains
    //  at any point,
    //      we can either travel up 1 unit (stand still)
    //      or move diagonally with a slope of at most v
    //  we can not travel between wall start/ends

    // diagonal edges have a weight of 1, where as vertical edges have a weight of 0
    //  what is the min path to the right of the grid (if any exist)

    // clearly we would rather get to a track sooner rather than later

    // suppose in some state, we choose to NOT run full speed
    //  if our path is not uniquely determined by the trains we intersect (our path does not have a start and end wall touching it)
    //      we should wait until either
    //          our speed maxes out
    //          our path touches both a start and end wall
    // so any path we take should either be max speed, or touching a start and end wall

    // suppose along some path, we end at a wall
    //  unless the path is upper and lower bounded, we may as well wait
    //  so no path, unless upper and lower bounded should hit a wall

    // so from any single state, we either
    //  go max speed
    //  if we can wait: take paths uniquely determined by start and end position
    //  if we can't wait: take paths that touch some train

    // approach
    //  we build a graph, where the nodes are the gaps between trains
    //  in each node, we store a sorted list of paths by start times
    //      any path stored must either
    //          intersect with a start and end of a train
    //          be max speed and intersect with the start of a train
}


int main() {
    /* cout << fixed << setprecision(6); */
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
