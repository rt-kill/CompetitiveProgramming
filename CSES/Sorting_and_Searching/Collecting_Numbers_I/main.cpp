#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n;
vector<int> numbers;
vector<int> inverse;
/* vector<vector<int>> lists; */

void solve() {
    cin >> n;
    numbers.resize(n);
    inverse.resize(n);
    for(int i=0;i<n;i++) {
        cin >> numbers[i];
        inverse[numbers[i]-1] = i;
    }

    int last=0, res=1;
    for(auto i : inverse) {
        if (i < last) res++;
        last=i;
    }

    cout << res << '\n';



    /* lists.resize(n); */
    /* int li = 0; */
    /* set<pair<int, int>, greater<pair<int, int>>> last_nums; */

    /* for(auto i : numbers) { */
    /*     auto it = last_nums.upper_bound({ i, 0 }); */

    /*     if(it != last_nums.end()) { */
    /*         auto [ cv, ci ] = *it; */
    /*         last_nums.erase(it); */
    /*         last_nums.insert({ i, ci }); */
    /*         lists[ci].push_back(i); */
    /*     } else { */
    /*         lists[li].push_back(i); */
    /*         last_nums.insert({ i, li++ }); */
    /*     } */

    /* } */

    /* cout << last_nums.size() << '\n'; */
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
