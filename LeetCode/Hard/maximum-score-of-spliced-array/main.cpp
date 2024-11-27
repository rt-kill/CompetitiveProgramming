#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumsSplicedArray(vector<int>& nums1, vector<int>& nums2) {
        // we would like to solve for max{i,j}( sum(nums1[:i]) + sum(nums2[i:j]) + sum(nums3[j:]) )
        //  this is the same as solving for min{i,j}( sum(nums1[:i]) + sum(nums2[i:j]) + sum(nums3[j:]) )
        //  this is the same as solving for max/min{i,j}( sum(nums1[i:j]) - sum(nums2[i:j]) )
        //  this is the same as solving for the max sum subarray of nums3[i] = nums1[i] - nums2[i]

        int n=nums1.size(), sn1=0, sn2=0;
        int v, pv=0;
        int mvp = 0, Mvp = 0, mds = 0, Mds = 0;
        for(int i=0;i<n;++i) {
            sn1 += nums1[i], sn2 += nums2[i];

            v = pv + nums1[i] - nums2[i], pv = v;

            Mds = max(Mds, v - mvp); mvp = min(mvp, v);
            mds = min(mds, v - Mvp); Mvp = max(Mvp, v);
        }

        int res = max(sn1 - mds, sn2 + Mds);
        return res;
    }
};
