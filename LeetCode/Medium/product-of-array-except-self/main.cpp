#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int f0 = find(nums.begin(), nums.end(), 0) - nums.begin();
        int l0 = nums.rend() - find(nums.rbegin(), nums.rend(), 0) - 1;

        int flag = (f0 < l0) + (f0 < nums.size());

        vector<int> res(nums.begin(), nums.end());
        if (flag == 0) {
            int tprod = accumulate(nums.begin(), nums.end(), 1, multiplies{});
            for(auto &val : res) val = tprod / val;

        } else if (flag == 1) {
            int prod = transform_reduce(nums.begin(), nums.end(), 1, multiplies{}, [](auto v){ return (v == 0) + (v != 0)*v; });
            for(auto &val : res) val = (val != 0) ? 0 : prod;

        } else { res.assign(nums.size(), 0); }

        return res;
    }

    void printRes(vector<int>& nums) {
        auto res = productExceptSelf(nums);
        for(auto v : res) cout << v << ' ';
        cout << '\n';
    }
};

int main() {
    auto solution = Solution();

    vector<int> t1 = { -1, 1, 0, -3, 3 };
    solution.printRes(t1);
}
