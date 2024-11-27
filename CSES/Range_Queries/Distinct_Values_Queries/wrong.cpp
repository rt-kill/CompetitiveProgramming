#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, q;
vector<int> x, c, low_reps, high_reps;
vector<ll> pfx, pflr, pfhr;

void read_and_init() {
    cin >> n >> q;

    x = vector<int>(n), low_reps = vector<int>(n), high_reps = vector<int>(n);

    int val = 0;
    map<int, int> comp;

    int tmp;
    for(int i=0; i<n; i++) {
        cin >> tmp;
        if (!comp.count(tmp)) comp[tmp] = val++;
        x[i] = comp[tmp];
    }


    c = vector<int>(val, 0);
    for(auto v : x) c[v]++;


    int thresh = sqrt(n);
    for(int i=0; i<n; i++) {
        int v = x[i];
        low_reps[i] = (c[v] <= thresh) ? v : -1;
        high_reps[i] = (c[v] > thresh) ? v : -1;
    }


    pfx = vector<ll>(n), pflr = vector<ll>(n), pfhr = vector<ll>(n);
    pfx[0] = x[0], pflr[0] = low_reps[0], pfhr[0] = high_reps[0];
    for(int i=1; i<n; i++) {
        pfx[i] = pfx[i-1] + x[i];
        pflr[i] = pflr[i-1] + low_reps[i];
        pfhr[i] = pfhr[i-1] + high_reps[i];
    }
}

// is there a -1 in [a, b] for low_reps
bool lrm1(int a, int b) {
    ll lrs = pflr[b];
    ll xs = pfx[b];
    if (a > 0) lrs -= pflr[a-1], xs -= pfx[a-1];

    return (lrs < xs);
}

// is there a -1 in [a, b] for high_reps
bool hrm1(int a, int b) {
    ll hrs = pfhr[b];
    ll xs = pfx[b];
    if (a > 0) hrs -= pfhr[a-1], xs -= pfx[a-1];

    return (hrs < xs);
}


void lr_setup() {
}




void solve() {
    read_and_init();

    int a, b;
    while(q--) {
        cin >> a >> b;

    }

    // if the number of unique values is <= sqrt(n)
    //  compress values to [0, #uv)
    //  maintain an n by #uv array that sends (k, v) to the number of v's in [0, k]
    //  when queryig (a, b), for each v, add (res[0, b] - res[0, a-1] > 0) to the answer

    // if the number of unique values is >= sqrt(n)
    //  at most sqrt(n) values appear >= sqrt(n) times
    //  handle these values seperately
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
