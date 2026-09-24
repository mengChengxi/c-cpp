#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;

    cin>>n;
    vector<int> nums(2*n);
    vector<int> mp(n+3,-1);

    for(int i=0; i<2*n; i++){
        cin >> nums[i];
    }

    long long maxn=0;
    vector<int> dp(2*n);
    for(int i=0; i<2*n; i++){
        if(mp[nums[i]]==-1){
            maxn+=1;
            mp[nums[i]]=i;
        }else{
            if(mp[nums[i]]==0){
                maxn=(i-mp[nums[i]]+1LL)*(i-mp[nums[i]]+1LL);
            }else{
                maxn=max(maxn+1,(i-mp[nums[i]]+1LL)*(i-mp[nums[i]]+1LL)+dp[mp[nums[i]]-1] );
            }
            
            
        }

        dp[i]=maxn;
    }

    cout<<maxn<<endl;



    

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