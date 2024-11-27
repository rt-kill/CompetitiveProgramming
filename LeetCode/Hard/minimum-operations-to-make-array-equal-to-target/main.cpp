#include <bits/stdc++.h>
#include <execution>
using namespace std;

class Solution {
public:
    long long minimumOperations(vector<int>& nums, vector<int>& target) {
        return transform_reduce(
            execution::seq,
            nums.begin(),
            nums.end(),
            target.begin(),
            0ll,
            [db=0](long long acc, int v) mutable {
                acc += abs(v);
                if ( (v^db) < 0 ) acc -= min(abs(v), abs(db));
                db = -v;
                return acc;
            },
            [](int v1, int v2){ return v1-v2; }
        );
    }
};
