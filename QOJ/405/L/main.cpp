#include <bits/stdc++.h>
using namespace std;
#define int long long
int f(pair<int,int>a, pair<int,int> b){
    int v = abs(a.first-b.first);
    v*=(a.second + b.second);
    return v;
}
signed main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int>arr(n+1);
    for(int i = 1; i<=n; i++){
        cin >> arr[i];
    }
    vector<pair<int,int>>stk;
    stk.push_back({n,arr[n]});
    int ans = 0;
    for(int i = n-1; i>=1; i--){
        while(stk.size()>=2){
            pair<int,int>p = stk.back();
            stk.pop_back();
            pair<int,int>p2 = stk.back();

            // p2y - y / p2x - x > p1y -  y / p1x - x
            // p2y - y * p1x - x > p1y - y * p2x - x
            if((p2.second - arr[i]) * (p.first - i) >= (p.second - arr[i]) * (p2.first - i)){
                continue;
            }
            else{
                stk.push_back(p);
                break;
            }
        }

        int low = -1; int high = stk.size()-1;
        while(low + 1 < high){
            int mid = (low+high)/2;
            if(f({i,arr[i]},stk[mid]) < f({i,arr[i]},stk[mid+1])){
                low = mid;
            }
            else{
                high = mid;
            }
        }

        if(low>=0)ans = max(ans,f({i,arr[i]}, stk[low]));
        if(high>=0)ans = max(ans,f({i,arr[i]}, stk[high]));
        if(high+1 <stk.size()){
            ans = max(ans,f({i,arr[i]},stk[high+1]));
        }
        stk.push_back({i,arr[i]});
    }
    cout << ans << '\n';
    return 0;
}
