#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n,m;

    cin>>n>>m;
    vector<int> nums(n);

    for(int i=0; i<n; i++){
        cin>>nums[i];
    }

    vector<vector<long long>> dp(n,vector<long long>(m+2,0));

    
    for(int i=0; i<n; i++){
        if(nums[i]==0){
            if(i!=0){
                for(int j=1; j<=m; j++){
                    dp[i][j]=(dp[i-1][j+1]+dp[i-1][j]+dp[i-1][j-1])%mod;
                }
            }else{
                for(int j=1; j<=m; j++){
                    dp[0][j]=1;
                }
            }
        }else{
            if(i!=0){
                dp[i][nums[i]]=(dp[i-1][nums[i]+1]+dp[i-1][nums[i]]+dp[i-1][nums[i]-1])%mod;
            }else{
                dp[0][nums[i]]=1;
            }
           
        }
    }

    long long res=0;

    for(int i=1; i<=m; i++){
        res=(res+dp[n-1][i])%mod;
    }

    cout<<res<<endl;
    


}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
        solve();
    
    return 0;
}