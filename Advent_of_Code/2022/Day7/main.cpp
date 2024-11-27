#include <bits/stdc++.h>
using namespace std;

using ll = long long;

map<string, set<string>> tree;
map<string, ll> sizes;
set<string> dirs;
map<string, ll> memory;

ll dfs(string root) {
    if (memory.count(root))
        return memory[root];

    if (sizes.count(root))
        return sizes[root];
    if (tree.count(root) == 0)
        return 0;

    ll res = 0;
    for (auto child : tree[root]) {
        res += dfs(child);
    }

    memory[root] = res;
    return memory[root];
}

string line;
void solve() {
    vector<string> curdir;
    while (true) {
        getline(std::cin, line);
        if (line.empty())
            break;

        if (line.substr(0,4) == "$ cd") {
            string con = line.substr(5);
            if (con == "..") curdir.pop_back();
            else curdir.push_back(con);
        } else if (line.substr(0,4) == "$ ls") {
            continue;
        }
        else {
            string lead = line.substr(0, line.find(' '));
            string tail = line.substr(line.find(' ') + 1);

            int i=0;
            string currep = accumulate(curdir.begin(), curdir.end(), string(), [&i](auto l, auto r) {return (l + ((i++ > 1) ? "/" : "") + r);});
            i=0;
            curdir.push_back(tail);
            string nrep = accumulate(curdir.begin(), curdir.end(), string(), [&i](auto l, auto r) {return (l + ((i++ > 1) ? "/" : "") + r);});
            curdir.pop_back();

            tree[currep].insert(nrep);


            if (lead != "dir") sizes[nrep] = stoi(lead);
            else dirs.insert(nrep);
        }
    }


    ll freespace = 70000000 - dfs("/");
    ll best_dir = dfs("/");
    cout << freespace << ' ' << best_dir << '\n';

    ll res = 0;
    for(auto dir : dirs) {
        ll tmp = dfs(dir);
        if (tmp <= 100000) res += tmp;

        if (tmp < best_dir && (freespace + tmp)  >= 30000000)
            best_dir = tmp;
    }

    cout << res << ' ' << best_dir << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
