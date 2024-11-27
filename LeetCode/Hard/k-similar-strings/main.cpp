#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int kSimilarity(string s1, string s2) {
        set<string> seen;
        queue<pair<string, int>> q({ { s1, 0 } });

        while(q.size()) {
            auto [ s, d ] = q.front(); q.pop();
            if (s == s2) return d;

            if (seen.count(s)) continue;
            seen.insert(s);

            int fb = 0;
            while(s[fb] == s2[fb]) ++fb;

            for(int si = fb+1; si < s.size(); ++si) if (s[si] == s2[fb]) {
                swap(s[fb], s[si]);
                q.push({ s, d+1 });
                swap(s[fb], s[si]);
            }
        }

        return -1;
    }
};
