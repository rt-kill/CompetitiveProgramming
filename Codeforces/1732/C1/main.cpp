#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = int(1e5) + 9;

int t;
int n, q;
int a[MAXN];
int L[MAXN], R[MAXN];

ll ps[MAXN], px[MAXN];

void solve() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= q; i++)
        cin >> L[i] >> R[i];

    ps[0] = 0; px[0] = 0;
    for (int i = 1; i <= n; i++) {
        ps[i] = ps[i-1] + ll(a[i]);
        px[i] = px[i-1] ^ ll(a[i]);
    }

    // cout << "PREFIX" << '\n';

    // for (int i = 0; i <= n; i++)
    //     cout << ps[i] << ' ';
    // cout << endl;
    // for (int i = 0; i <= n; i++)
    //     cout << px[i] << ' ';
    // cout << endl;
    // cout << endl;


    for (int aq = 1; aq <= q; aq++) {
        int Lq = L[aq]; int Rq = R[aq];
        int sl = Lq; int sr = Rq;

        ll mf = (ps[Rq] - ps[Lq - 1]) - (px[Rq] ^ px[Lq - 1]);

        int lil = 0; int ril = Rq - Lq;
        while (lil < ril) {
            int mil = lil + (ril - lil) / 2;
            // cout << "MIL " << mil << '\n';

            bool exists = false;
            for (int l = Lq; l <= Rq - mil; l++) {
                int r = l + mil;
                ll f = (ps[r] - ps[l - 1]) - (px[r] ^ px[l - 1]);

                // cout << "L,R,f " << l << ' ' << r << ' ' << f << '\n';

                if (f == mf) {
                    sl = l; sr = r;
                    exists = true;
                    break;
                }
            }

            if (exists) ril = mil;
            else lil = mil + 1;
        }

        cout << sl << ' ' << sr << '\n';
    }

    // a + b = a ^ b + 2*(a & b)
    // a + b + c = (a ^ b + 2*(a&b)) ^ c + 2*((a ^ b + 2*(a&b)) & c)

    // a + b >= a ^ b

    // s(l, m) - x(l, m) + s(m+1, r) - x(m+1, r) = (s(l, m) + s(m+1, r)) - (x(l, m) + x(m+1, r)) <= s(l, r) - x(l, r)

    // sum(l, r)    = ps[r] - ps[l-1]
    // xor(l, r)    = px[r] ^ px[l-1]
    // f(l, r)      = ps[r] - ps[l-1] - px[r] ^ px[l-1]

}

int main() {
    cin >> t;
    for (int i = 0; i < t; i++) {
        // cout << "TEST " << i << " ------------------" << '\n' << '\n';
        solve();
        // cout << '\n' << '\n';
    }
}
