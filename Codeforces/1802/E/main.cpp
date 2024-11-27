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

#define lb lower_bound
#define ub upper_bound

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

#define pln(...)        pr(__VA_ARGS__); cout << '\n';

#define _peln_aux_(a)    cout << a << '\n';
#define _peln_(...)      FOR_EACH(_peln_aux_, __VA_ARGS__)
#define peln(...)        _pln_(__VA_ARGS__)

/* IO - Helpers {{{*/
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

vi answers;

int n, k;
vvi a;

vi maxTracks;
vvi buckets;
vvpi scores;

vpi getScores( int bi ) {
    vi& bucket = buckets[bi];

    vpi res;

    each(ind, bucket) {
        auto& album = a[ind];
        vi sub(album.sz, -1);

        stack<pi> stak;
        For(i, 0, album.sz) {
            while(stak.sz && stak.top().fi < album[i]) {
                auto [ _, j ] = stak.top(); stak.pop();
                sub[j] = i;
            }

            stak.push({ album[i], i });
        }

        Rof(i, 0, album.sz) sub[i] = (sub[i] < 0) ? 1 : 1 + sub[sub[i]];

        int pmp = 0;
        For(i, 0, album.sz) if (album[i] > pmp) {
            res.pb({ album[i], sub[i] });
            pmp = album[i];
        }

    }

    sort(all(res), [](auto l, auto r){ return l.fi > r.fi || (l.fi == r.fi && l.se > r.se); });
    auto tmp = unique(all(res), [](auto l, auto r){ return l.se >= r.se; });
    res.erase(tmp, res.end());

    sort(all(res));
    return res;
}

void solve() {
    re(n);
    a.rsz(n);
    each(v, a) { rewv(k, v) };

    // O(∑m + nlog(n))
    maxTracks.rsz(0);
    each(v, a) maxTracks.pb(*max_element(all(v)));
    sort(all(maxTracks));
    maxTracks.rsz(unique(all(maxTracks)) - maxTracks.begin());

    buckets.assign(maxTracks.sz, vi());
    For(i, 0, n) {
        int mt = *max_element(all(a[i]));
        int ind = lb(all(maxTracks), mt) - maxTracks.begin();
        buckets[ind].pb(i);
    }

    scores.rsz(buckets.sz);
    For(i, 0, buckets.sz) scores[i] = getScores(i);


    // { endingTrack, points }
    vpi dp({ { 0, 0 } });
    For(i, 0, buckets.sz) {
        int best = 0;

        For(j, 0, scores[i].sz) {
            auto [st, np] = scores[i][j];
            auto [_,  pp] = *ub(rall(dp), mp(st, INT_MIN), greater{});
            cmax(best, pp + np);
        }

        dp.pb({ maxTracks[i], best });
    }

    int res = dp.back().se;
    answers.pb(res);




    // consider the vector buckets, where buckets[v] stores all tracks with max value v
    //  define dp[v] to be the max points using only buckets[:v]
    //  dp[v] = max{ pv < v } ( dp[pv] + max{buckets[v]}( points[v] ) )





    // let dp[v] be the solution for albums with max track >= v assuming the last track we listened to was (v-1)
    // suppose the first album we listen to has max track v
    //  then res = points from this track + dp[v+1]

    // let v be the max track over all albums
    //  dp[v] = 1
    //  dp[v-1] = (exists track with max value v-1) ? 1 + dp[v] : (exists track with { v-1, v } subseq) ? 1 + dp[v] :


    // after we play an album, there is no point to play an album whose max value is less than that of the current album
    //  we could build a graph where
    //  V(G) := albums
    //  E(G) := { (u, v, w) : u,v ∈ V(G), max(v) > max(u), w := number of points we get by listening to v after u }
    // doesn't work because there are potentially n² edges

    // for each album, we may give each track a value: The number of points if this is the first "good" track
    //  such a list can be populated in O(n) using a stack


}

int main() {
    /* cout << fixed << setprecision(6); */
    int t=1;
    cin >> t;
    for (int i=0;i<t;i++)
        solve();

    each(res, answers) { pln(res); }

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
