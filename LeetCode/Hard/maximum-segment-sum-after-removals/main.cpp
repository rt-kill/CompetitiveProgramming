#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<long long> maximumSegmentSum(vector<int>& nums, vector<int>& removeQueries) {
        vector<long long> pfx(nums.begin(), nums.end());

        for(int i=1; i<pfx.size(); ++i)  pfx[i] += pfx[i-1];
        auto sum_qury = [pfx](auto l, auto r){ return (l > 0) ? pfx[r] - pfx[l-1] : pfx[r]; };

        set<int> hds, tls;
        set<array<long long, 3>> ms;
        ms.insert({ sum_qury(0, nums.size()-1), 0, (int)nums.size()-1 });
        hds.insert(0), tls.insert(nums.size()-1);

        vector<long long> res;
        for(int i : removeQueries) {
            int hi = *(--(hds.upper_bound(i))), ti = *tls.lower_bound(i);

            ms.erase({ sum_qury(hi, ti), hi, ti });
            hds.erase(hi), tls.erase(ti);

            if (i > hi) {
                ms.insert({ sum_qury(hi, i-1), hi, i-1 });
                hds.insert(hi), tls.insert(i-1);
            }

            if (i < ti) {
                ms.insert({ sum_qury(i+1, ti), i+1, ti });
                hds.insert(i+1), tls.insert(ti);
            }

            res.push_back(ms.size() ? (*ms.rbegin())[0] : 0);
        }

        // we store a map from a (h, t) pair to its segment sum
        return res;
    }
};
