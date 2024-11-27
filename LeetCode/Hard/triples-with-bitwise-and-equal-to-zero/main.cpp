#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countTriplets(vector<int>& nums) {
        int n = nums.size();

        vector<int> counts((1<<16), 0);
        for(auto v1 : nums) for(auto v2 : nums) ++counts[v1 & v2];

        int res = 0;
        for(auto v : nums) for(int m=0; m<(1<<16); ++m)
            if ((v&m) == 0) res += counts[m];

        // for each value in [0, 2^16-1] count the number of (i, j) pairs with & that value
        //  for each value in [0, 2^16-1] count the number of k with & 0

        return res;
    }
};
