#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;
    cin>>n;

    vector<int> nums(n);

    for(int i=0; i<n; i++){
        cin>>nums[i];
    }

    vector<long long> dp(n,0);
    vector<vector<long long>> atr(n,vector<long long>(n,0));
    vector<vector<long long>> sumatr(n,vector<long long>(n,0));

    vector<long long> sumdp(n);

    for(int i=0; i<n; i++){
        for(int j=0; j<i; j++){
            //find val <=2*nums[j]-nums[i]  
            
            auto it = lower_bound(nums.begin(), nums.end(), 2*nums[j]-nums[i]  );//first element >= i
            
            int index=distance(nums.begin(),it)-1;//index
            if(j>0){
                if(index>=0){
                    atr[i][j]=(sumdp[j-1]-sumdp[index]+mod)%mod;
                }else{
                    atr[i][j]=sumdp[j-1]%mod;
                }
                sumatr[i][j]=sumatr[i][j-1]+atr[i][j];
                
            }
            
            auto it2 = lower_bound(nums.begin(), nums.end(), 2*nums[j]-nums[i]  );//first element >= i

            
            int index2= distance(nums.begin(),it2)-1;//index
            
          
            dp[i]=(dp[i]+dp[j])%mod;
            

            if(index2>=0){
                dp[i]=(dp[i]+sumatr[j][index2])%mod;
            }
                
            
            
            
        }
        dp[i]=(dp[i]+1)%mod;
        if(i>0){
            sumdp[i]=(sumdp[i-1]+dp[i])%mod;
        }else{
            sumdp[i]=dp[i];
        }
        
    }

    cout << (sumdp[n-1] - n % mod + mod) % mod << "\n";    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
   
        solve();
    
    return 0;
}