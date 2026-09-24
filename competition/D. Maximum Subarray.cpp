#include <bits/stdc++.h>
#include <climits>
#include <cstdint>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n,k,x;
    cin>>n>>k>>x;

    vector<long long> nums(n);

    for(int i=0; i<n; i++){
        cin>>nums[i];
    }

    vector<vector<long long>> dp(n,vector<long long>(k+1,LONG_MIN/2));

    dp[0][0]=max(nums[0]-x,0LL);
    if(k>0){
        dp[0][1]=max(nums[0]+x,0LL);
    }
    

    for(int i=1; i<n; i++){
        for (int kk = 0; kk <= min(k, i + 1); kk++) {
            // 空子数组
            dp[i][kk] = 0;

            // 当前元素不选择 +x
            // 前 i 个元素中必须能选择 kk 个位置
            if (kk <= i) {
                dp[i][kk] = max(
                    dp[i][kk],
                    dp[i - 1][kk] + nums[i] - x
                );
            }

            // 当前元素选择 +x
            if (kk > 0) {
                dp[i][kk] = max(
                    dp[i][kk],
                    dp[i - 1][kk - 1] + nums[i] + x
                );
            }
        }
    }
        
    long long res=0;
    for(int i=0; i<n; i++){
        for(int j=0; j<=k; j++){
            if(k - j <= n - i - 1){
                res=max(res,dp[i][j]);
            }
        }
        
    }
    cout<<res<<endl;
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