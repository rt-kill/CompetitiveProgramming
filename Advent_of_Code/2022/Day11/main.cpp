#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    string line;
    int monkey=0;
    int item=0;
    string si, op, t, ot, of;

    string p1 = "  Starting items: ";
    string p2 = "  Operation: new = old ";
    string p3 = "  Test: divisible by ";
    string p4 = "    If true: throw to monkey ";
    string p5 = "    If false: throw to monkey ";

    map<int, ll> worry_level;
    map<int, vector<int>> monkey_items;
    map<int, pair<char, string>> monkey_op;
    map<int, int> monkey_test;
    map<int, pair<int, int>> monkey_action;

    while(true) {
        getline(std::cin, line);
        if(line.empty()) break;


        getline(std::cin, si);
        si = si.substr(p1.size());

        vector<int> items;
        for(int i=0; i<si.size(); i+=4)
            items.push_back(stoi(si.substr(i, 2)));

        for (auto it : items) {
            worry_level[item] = it;
            monkey_items[monkey].push_back(item);
            item++;
        }


        getline(std::cin, op);
        op = op.substr(p2.size());

        char o = op[0];
        string ch = op.substr(2);

        monkey_op[monkey] = { o, ch };


        getline(std::cin, t);
        t = t.substr(p3.size());
        int tv = stoi(t);

        monkey_test[monkey] = tv;


        getline(std::cin, ot);
        ot = ot.substr(p4.size());

        int otv = stoi(ot);

        getline(std::cin, of);
        of = of.substr(p5.size());

        int ofv = stoi(of);

        monkey_action[monkey] = { otv, ofv };

        monkey++;
        getline(std::cin,line);
    }


    /* int max_round = 20; */
    /* int max_monkey = monkey - 1; */
    /* vector<int> monkey_business = vector<int>(max_monkey + 1, 0); */

    /* for (int round = 1; round <= 20; round++) { */
    /*     for (int monkey=0; monkey<=max_monkey; monkey++) { */
    /*         for (int const item : monkey_items[monkey]) { */
    /*             // Monkey inspects item */
    /*             auto [ operation, change_string ] = monkey_op[monkey]; */
    /*             int change; */

    /*             if (change_string == "old") */
    /*                 change = worry_level[item]; */
    /*             else */
    /*                 change = stoi(change_string); */

    /*             if (operation == '+') */
    /*                 worry_level[item] += change; */
    /*             else // operation == '*' */
    /*                 worry_level[item] *= change; */


    /*             // Monkey gets bored of item */
    /*             worry_level[item] /= 3; */


    /*             // Monkey throws item */
    /*             auto [ monkey_true, monkey_false ] = monkey_action[monkey]; */
    /*             if (worry_level[item] % monkey_test[monkey] == 0) // true */
    /*                 monkey_items[monkey_true].push_back(item); */
    /*             else */
    /*                 monkey_items[monkey_false].push_back(item); */
    /*         } */

    /*         monkey_business[monkey] += monkey_items[monkey].size(); */
    /*         monkey_items[monkey] = vector<int>(); */
    /*     } */
    /* } */

    /* int best_buisness[2] = { 0, 0 }; */
    /* for (auto buisness : monkey_business) { */
    /*     best_buisness[0] = max(best_buisness[0], buisness); */
    /*     sort(best_buisness, best_buisness + 2); */
    /* } */

    /* int res1 = accumulate(best_buisness, best_buisness + 2, 1, multiplies<int>()); */
    /* cout << res1 << '\n'; */

    int max_round = 10000;
    int max_monkey = monkey - 1;
    vector<ll> monkey_business = vector<ll>(max_monkey + 1, 0);

    // 2, 7, 13, 19, 11, 5, 3, 17

    int const MM = transform_reduce(monkey_test.begin(), monkey_test.end(), 1l,
                [](auto l, auto r) { return l*r; },
                [](auto v){ return v.second; }
            );

    cout << MM << '\n';

    // let k be the product of these
    // [ a | b ] <=> [ b = am ]
    //      <=> [ x*k + r = am ]
    //      <=> [ x*(l*a) + r = am ]
    //      <=> [ r = a(m - x*l) ]
    //      <=> [ a | r ]


    for (int round = 1; round <= max_round; round++) {
        for (int monkey=0; monkey<=max_monkey; monkey++) {
            for (int const item : monkey_items[monkey]) {
                // Monkey inspects item
                auto [ operation, change_string ] = monkey_op[monkey];
                int change;

                if (change_string == "old")
                    change = worry_level[item];
                else
                    change = stoi(change_string);

                if (operation == '+')
                    worry_level[item] += change;
                else // operation == '*'
                    worry_level[item] *= change;

                if (worry_level[item] <= 0) cout << "BAD" << '\n';
                worry_level[item] %= MM;


                // Monkey gets bored of item
                /* worry_level[item] /= 3; */


                // Monkey throws item
                auto [ monkey_true, monkey_false ] = monkey_action[monkey];
                if (worry_level[item] % monkey_test[monkey] == 0) // true
                    monkey_items[monkey_true].push_back(item);
                else
                    monkey_items[monkey_false].push_back(item);
            }

            monkey_business[monkey] += monkey_items[monkey].size();
            monkey_items[monkey] = vector<int>();
        }
    }

    ll best_buisness[2] = { 0, 0 };
    for (auto buisness : monkey_business) {
        best_buisness[0] = max(best_buisness[0], buisness);
        sort(best_buisness, best_buisness + 2);
    }

    ll res1 = accumulate(best_buisness, best_buisness + 2, 1l, multiplies<ll>());
    cout << res1 << '\n';
}

int main() {
    int t=1;
    /* cin >> t; */
    for (int i=0;i<t;i++)
        solve();

    return 0;
}
