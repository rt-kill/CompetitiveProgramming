#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    int const Mod = 1e9 + 7;
public:
    int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
        // the soluiton will be the max over {i ∈ [1, k]} of the optimal team with i people
        // the solution will be the max over {v ∈ efficncy} of the optimal team with min efficiency v
        //  that is it will be the sum of the k largest speeds over players with efficiency at least v

        // sort with respect to efficiency
        // walk backwards

        vector<pair<int, int>> pairs;
        for(int i=0; i<n; ++i) pairs.push_back({ efficiency[i], speed[i] });
        sort(pairs.begin(), pairs.end());

        priority_queue<int, vector<int>, greater<int>> pq;
        long long pq_sum = 0;

        long long res = -1;
        for(auto it = pairs.rbegin(); it != pairs.rend(); ++it) {
            auto [ e, s ] = *it;
            pq.push(s);
            pq_sum += s;
            while(pq.size() > k) { pq_sum -= pq.top(); pq.pop(); }
            res = max(res, pq_sum * e);
        }

        return res % Mod;
    }
};
