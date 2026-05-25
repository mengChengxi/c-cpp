#include <bits/stdc++.h>
#include <typeindex>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n,m;
    cin>>n>>m;
    vector<int> nums(m);
    for(int i=0; i<m; i++){
        cin>>nums[i];
    }

    int prev=nums[0];
    for(int i=1; i<m; i++){
        if(nums[i]<=prev){
            cout<<1<<endl;
            return;
        }
        prev=nums[i];
    }

    cout<<n-nums[m-1]+1<<endl;
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