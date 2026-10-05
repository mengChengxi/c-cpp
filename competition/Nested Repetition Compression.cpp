#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

int digit(int n){
    int count=0;
    while(n!=0){
        n/=10;
        count++;
    }
    return count;
}
void solve() {
    string s;
    cin>>s;

    int l=s.size();
    vector<vector<int>> dp(l,vector<int>(l,INF));

    for(int i=0; i<l; i++){
        dp[i][i]=1;
    }
    for(int le=1;le<l; le++){
        for(int i=0; i+le<l; i++){
            
            for(int split=0;split+1<=le; split++){
                dp[i][i+le]=min(dp[i][i+split]+dp[i+split+1][i+le],dp[i][i+le]);
            }
            for(int interval=1; interval<=le/2+1; interval++){
                if((le+1)%interval==0&&(le+1)/interval<10){
                    bool fail=false;
                    for(int j=interval; j<=le; j++){
                        if(s[j+i]==s[j%interval+i]){

                        }else{
                            fail=true;
                            break;
                        }
                    }
                    if(fail==false){
                        dp[i][i+le]=min(3+dp[i][i+interval-1],dp[i][i+le]);
                    }

                }
            }   
            
            
        }
    }
    cout<<dp[0][l-1]<<endl;


}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    solve();
    
    return 0;
}