#include <bits/stdc++.h>

using namespace std;

int main() {
    std::stringstream ss;

    ss.clear();
    ss.str("");
    std::string input = "";

    vector<vector<int>> rations = { vector<int>() };
    int val, nv=0;

    while (nv++ < 2) {
        getline(cin, input);

        if (input.empty())
            rations.push_back(vector<int>());
        else {
            nv=0;

            ss.str(input);
            ss >> val;

            ss.clear();
            ss.str("");
            input.clear();

            rations.back().push_back(val);
        }
    }

    vector<int> ration_sums(rations.size());
    transform(rations.begin(), rations.end(), ration_sums.begin(),
        [](auto val) { return reduce(val.begin(), val.end()); } );
    sort(ration_sums.begin(), ration_sums.end(), greater<int>());

    int res1 = ration_sums[0];
    int res2 = ration_sums[0] + ration_sums[1] + ration_sums[2];

    cout << res1 << '\n';
    cout << res2 << '\n';



    return 0;
}
