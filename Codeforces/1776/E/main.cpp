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


ll n, m, s, v;
ve<arr<ll, 3>> trains;
vvpll tracks;


// checks if a constant speed path is valid
arr<int, 3> pathIsValid(ll leftTrack, ll leftTime, ll rightTrack, ll rightTime) {
    ll trackDeltaTot = rightTrack - leftTrack;
    ll timeDeltaTot = rightTime - leftTime;
    ll invSpeed = timeDeltaTot/trackDeltaTot;
    if (v*invSpeed < 1) return { 0, 0, 0 };

    int good = 1, loBounded = 0, upBounded = 0;
    For(track, leftTrack, rightTrack+1) {
        ll dist = track - leftTrack;
        ll time = leftTime + dist*invSpeed;

        // index of first train on track that starts >= timeUb
        int ind = lower_bound(all(tracks[track]), mp( time, -1 ), less<pll>()) - tracks[track].begin();
        // end time of previous train
        ll endTime = (ind > 0) ? trains[tracks[track][ind-1].se][1] : 0;
        // start time of next train
        ll startTime = (ind < tracks[track].sz) ? tracks[track][ind].se : s;

        good &= (endTime <= time);
        loBounded |= ( time == endTime );
        upBounded |= ( time ==  startTime);
    }

    return { good, loBounded, upBounded };
}

arr<int, 2> extendEdge(ll leftTrack, ll leftTime, ll rightTrack, ll rightTime) {
    ll trackDeltaTot = rightTrack - leftTrack;
    ll timeDeltaTot = rightTime - leftTime;
    ll invSpeed = timeDeltaTot/trackDeltaTot;

    int track;

    track = leftTrack;
    while(track >= 0) {
        ll dist = track - leftTrack;
        ll time = leftTime + dist*invSpeed;

        int ind = lower_bound(all(tracks[track]), mp( time, -1 ), less<pll>()) - tracks[track].begin();
        ll endTime = (ind > 0) ? trains[tracks[track][ind-1].se][1] : 0;

        if (endTime > time) break;
        --track;
    }
    int l = track+1;

    track = rightTrack;
    while(track < m) {
        ll dist = track - leftTrack;
        ll time = leftTime + dist*invSpeed;

        int ind = lower_bound(all(tracks[track]), mp( time, -1 ), less<pll>()) - tracks[track].begin();
        ll endTime = (ind > 0) ? trains[tracks[track][ind-1].se][1] : 0;

        if (endTime > time) break;
        ++track;
    }
    int r = track-1;

    return { l, r };
}


// track store a sorted list of {startTime, endTime, endTrack}
//  the only edges stored in edges are either max velocity edges that touch a single train end
//  or edges that are upper and lower bounded by a train edge

ve<ve<arr<ll, 3>>> edges;
void popEdges() {
    ve<ve<arr<ll, 3>>> edgesBuff(m);

    // populate with edges that start and end on their bounds
    For(lt, 0, m) For(rt, lt+1, m) {
        For(ltr, 0, tracks[lt].sz) For(rtr, 0, tracks[rt].sz) {
            int ltInd=tracks[lt][ltr].se, rtInd=tracks[rt][rtr].se;

            // upBounded by ltr, loBounded by rtr
            auto p1 = pathIsValid(lt, trains[ltInd][0], rt, trains[rtInd][1]);
            if (p1[0]) edgesBuff[lt].pb({trains[ltInd][0], trains[rtInd][1], rt});

            // loBounded by ltr, upBounded by rtr
            auto p2 = pathIsValid(lt, trains[ltInd][1], rt, trains[rtInd][0]);
            if (p2[0]) edgesBuff[lt].pb({trains[ltInd][1], trains[rtInd][0], rt});
        }
    }

    // populate edges of max velocity that touch some bound
    For(lt, 0, m-1) For(ltr, 0, tracks[lt].sz) {
        int ltInd=tracks[lt][ltr].se;

        arr<ll, 4> inp1 = { lt, trains[ltInd][0], lt+1, trains[ltInd][0] + v };
        auto p1 = pathIsValid( inp1[0], inp1[1], inp1[2], inp1[3] );
        if (p1[0]) edgesBuff[lt].pb({ inp1[1], inp1[3], inp1[2] });

        arr<ll, 4> inp2 = { lt, trains[ltInd][1], lt+1, trains[ltInd][1] + v };
        auto p2 = pathIsValid( inp2[0], inp2[1], inp2[2], inp2[3] );
        if (p2[0]) edgesBuff[lt].pb({ inp2[1], inp2[3], inp2[2] });
    }

    edges.rsz(m);
    For(lt, 0, m) each(edge, edgesBuff[lt]) {
        ll leftTrack=lt, leftTime=edge[0], rightTrack=edge[2], rightTime=edge[1];

        ll trackDeltaTot = rightTrack - leftTrack;
        ll timeDeltaTot = rightTime - leftTime;
        ll invSpeed = timeDeltaTot/trackDeltaTot;

        auto [ ml, Mr ] = extendEdge(leftTrack, leftTime, rightTrack, rightTime);
        For(st, leftTrack, lt+1) {
            ll ldist = st - lt;
            ll ltime = leftTime + ldist*invSpeed;

            For(et, rightTrack, Mr+1) {
                ll rdist = et - rightTrack;
                ll rtime = rightTime + rdist*invSpeed;

                edges[st].pb({ ltime, rtime, et });
            }
        }
    }

    each(edgeSet, edges) sort(all(edgeSet));
}


int dfs(int track, ll time) {
    if (track == m-1) return 0;
    int res = INT_MAX-1;

    arr<ll, 3> sq1 = { time, -1, -1 };

    // index of first edge we can take
    int lInd = lower_bound(all(edges[track]), sq1) - edges[track].begin();

    // index of first train that starts >= time
    int nextTrain = lower_bound(all(tracks[track]), mp(time, -1), less<pll>())->se;
    ll startTime = trains[nextTrain][0];
    arr<ll, 3> sq2 = { startTime, -1, -1 };
    // index of the first edge we can't take
    int rInd = upper_bound(all(edges[track]), sq2) - edges[track].begin();

    For(i, lInd, rInd) {
        auto edge = edges[track][i];
        int cost = dfs(edge[2], edge[1]);
        cmin(res, cost+1);
    }

    // only other option is to immediately try the fastest speed
    arr<ll, 4> inp = { track, time, track+1, time + v };
    auto p1 = pathIsValid( inp[0], inp[1], inp[2], inp[3] );
    if (p1[0]) {
        auto [ _, Mr ] = extendEdge( inp[0], inp[1], inp[2], inp[3] );
        For(et, track+1, Mr+1) {
            ll dist = et - track;
            ll ntime = time + v*dist;

            int cost = dfs(et, ntime);
            cmin(res, cost+1);
        }
    }

    return res;
}


void solve() {
    re(n, m, s, v);
    trains.rsz(n), tracks.rsz(m);

    // to make all speeds integral, we multiple by (m-1)! so that everything is divisible by (endTrack-startTrack)
    ll myMult = 1;
    For(i, 1, m) myMult *= i;

    s *= myMult, v *= myMult;
    For(i, 0, n) {
        auto &train = trains[i];
        re(train[0], train[1], train[2]);
        train[0] *= myMult, train[1] *= myMult, --train[2];
        tracks[train[2]].pb( { train[0], i } );
    }
    each(track, tracks) sort(all(track));

    popEdges();
    int res = dfs(0, 0);
    pln(res);
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
