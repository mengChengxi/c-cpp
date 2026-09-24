#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;
    cin>>n;

    vector<int> dp(n+5,INF);

    dp[0]=0;

    for(int i=1; i<=n; i++){
        int current=i;
        
        while(current!=0){
            dp[i]=min(dp[i-current%10]+1,dp[i]);
            current=(current-current%10)/10;
        }
    }

    cout<<dp[n]<<endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
  
        solve();
    
    return 0;
}