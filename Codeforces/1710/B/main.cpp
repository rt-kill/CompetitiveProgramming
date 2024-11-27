#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int t;
int n, m;
int x[int(2e5) + 9], p[int(2e5) + 9];

tuple<int, int, int> s[int(2e5) + 9];
ll W[int(2e5) + 9]; // The water levels without any "magic"
char res[int(2e5) + 9];

int md(pair<int, int> point) {
    return point.first + point.second;
}
auto fcomp = [](const auto & l, const auto & r) -> bool {
    return get<0>(l) < get<0>(r);
};
auto qcomp = [](const auto & l, const auto & r) -> bool {
    return md(l) > md(r);
};


void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> x[i] >> p[i];

    for (int i = 1; i <= n; i++)
        s[i] = make_tuple(x[i], p[i], i);
    sort(s+1, s+n+1, fcomp);


    ll count = 0; int amount = 0;
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= n; i++) {
        if (!pq.empty())
        while (!pq.empty() && pq.top() <= get<0>(s[i])) {
            count -= pq.top();
            amount -= 1;
            pq.pop();
        }

        pq.push(get<0>(s[i]) + get<1>(s[i]));
        count += ll(get<0>(s[i])) + ll(get<1>(s[i]));
        amount += 1;


        W[i] = count - ll(get<0>(s[i]))*ll(amount);
    }

    count = 0; amount = 0;
    pq = priority_queue<int, vector<int>, greater<int>>();
    for (int i = n; i >= 1; i--) {
        while (!pq.empty() && pq.top() <= (get<0>(s[n]) - get<0>(s[i]))) {
            count -= pq.top();
            amount -= 1;
            pq.pop();
        }

        pq.push((get<0>(s[n]) - get<0>(s[i])) + get<1>(s[i]));
        count += ll(get<0>(s[n]) - get<0>(s[i])) + ll(get<1>(s[i]));
        amount += 1;

        W[i] += count - ll(get<0>(s[n]) - get<0>(s[i]))*ll(amount);
    }

    for (int i = 1; i <= n; i++)
        W[i] -= get<1>(s[i]);

    fill(res + 1, res + 1 + n, '1');

    // Using a max priority q, we sweep right
    priority_queue<tuple<int, int>, vector<tuple<int, int>>, greater<tuple<int, int>>> npq; // fcomp might be reversed here (i dont think so tho)
    for (int i = 1; i <= n; i++) {
        while ( !npq.empty() && W[i] - max(0, get<0>(npq.top()) - get<0>(s[i])) > m) {
            // res[get<1>(npq.top())] = '0';
            res[get<2>(s[get<1>(npq.top())])] = '0';
            npq.pop();
        }
        npq.push(make_tuple(get<0>(s[i]) + get<1>(s[i]), i));
    }

    npq = priority_queue<tuple<int, int>, vector<tuple<int, int>>, greater<tuple<int, int>>>(); // fcomp might be reversed here (i dont think so tho)
    for (int i = n; i >= 1; i--) {
        while (!npq.empty() && W[i] - max(0, (get<0>(npq.top()) - (get<0>(s[n]) - get<0>(s[i])))) > m) {
            // res[get<1>(npq.top())] = '0';
            res[get<2>(s[get<1>(npq.top())])] = '0';
            npq.pop();
        }
        npq.push(make_tuple((get<0>(s[n]) - get<0>(s[i])) + get<1>(s[i]), i));
    }

    for (int i = 1; i <= n; i++)
        cout << res[i];
    cout << '\n';


    // If some location has at least m + max(p) < 2e9 level, return false for everything
    // So we suppose this is not the case for any location
    // It follows that locations with large P can not be close to other locations with large P
    //


        // Find i for which W is maximal within an interval
        //  Everything to the right can be discarded
	//  When we remove some rain,
	//
	//  Removing i, will effect W[j] by max(0, P[i] - |x[i] - x[j]}
	//
	// Idea: Sort W[i], and see that any magic that effects

    // We would like to know for all i (in log(n) time)
    //  does there exist j for which
    //      W[x[j]] - (max(0, p[j] - |(x[i] - x[j])|)) >= m


    // We have the sum of n "linear" equations all of slope pm 1
    // How do they cancel?

    // Given i, how many values to the right and left contribute to it?
    // j will contribute to i if and only if |x[i] - x[j]| < p[j]
}

int main() {
    cin >> t;
    for (int i = 1; i <= t; i++) {
        // cout << "--- Test " << i << " ---" << '\n' << '\n';
        solve();
        // cout << '\n' << '\n';
    }

	return 0;
}
