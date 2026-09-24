#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n,q;
    cin>>n>>q;

    vector<int> nums(n);
    for(int i=0; i<n; i++){
        cin>>nums[i];
    }

    vector<int> snums=nums;
    sort(snums.begin(),snums.end());

    unordered_map<int, int>mp;

    for(int i=0; i<n; i++){
        mp[snums[i]]=i;
    }

    int cost=0;
    for(int i=0; i<n; i++){
        int target=mp[nums[i]];
        //i- target

        for(int j=20; j>=0; j--){
            if(((i>>j)%2) != ((target>>j)%2)){
                cost=max(cost, 1<<j);
            }
        }
    }

    cout<<cost<<endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int dashabi;
    cin >> dashabi;
    while (dashabi--) {
        solve();
    }
    return 0;
}