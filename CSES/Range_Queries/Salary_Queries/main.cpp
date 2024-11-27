#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n, q;
vector<int> s;
vector<array<int, 3>> queries;
vector<int> salary_range;


int N;
vector<int> counts;
vector<int> bit;
void update(int k, int u) {
    counts[k] += u;
    for(int i=k; i<=N; i += (i&-i))
        bit[i] += u;
}

int aux_query(int a) {
    int res = 0;
    for(int i=a; i>0; i -= (i&-i))
        res += bit[i];
    return res;
}

int query(int a, int b) {
    int res = aux_query(b) - aux_query(a-1);
    return res;
}


int lmap(int salary) {
    int i = upper_bound(salary_range.begin(), salary_range.end(), salary-1) - salary_range.begin();
    return i;
}

int rmap(int salary) {
    int i = upper_bound(salary_range.begin(), salary_range.end(), salary) - salary_range.begin() - 1;
    return i;
}


void solve() {
    cin >> n >> q;

    s.resize(n+1);
    for(int i=1; i<=n; ++i)
        cin >> s[i];

    queries.resize(q);
    for(int i=0; i<q; ++i) {
        char t;
        int a, b;
        cin >> t >> a >> b;
        queries[i] = { (t == '!'), a, b };
    }

    salary_range = vector<int>(s.begin(), s.end());
    for(auto query : queries)
        if (query[0] == 1)
            salary_range.push_back(query[2]);

    sort(salary_range.begin(), salary_range.end());
    salary_range.erase( unique( salary_range.begin(), salary_range.end() ), salary_range.end() );

    N = salary_range.size();
    counts.resize(N);
    bit.resize(N);
    for(int i=1; i<=n; ++i) {
        int index = rmap(s[i]);
        update(index, 1);
    }


    /* for(auto v : s) cout << v << ' '; */
    /* cout << '\n'; */
    /* cout << '\n'; */


    /* for(auto v : salary_range) cout << v << ' '; */
    /* cout << '\n'; */
    /* cout << '\n'; */

    /* for(auto v : counts) cout << v << ' '; */
    /* cout << '\n'; */
    /* cout << '\n'; */

    /* for(auto v : bit) cout << v << ' '; */
    /* cout << '\n'; */
    /* cout << '\n'; */


    for (auto [t, a, b] : queries) {
        if (t == 1) {
            int remove_index = rmap(s[a]);
            update(remove_index, -1);

            int add_index = rmap(b);
            update(add_index, 1);

            s[a] = b;
        }

        if (t == 0) {
            int start_index = lmap(a);
            int end_index = rmap(b);



            int res = query(start_index, end_index);
            cout << res << '\n';
        }
    }
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
