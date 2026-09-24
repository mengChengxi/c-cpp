#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair




void solve() {
    string sa;
    string sb;

    cin>>sa;
    cin>>sb;

    vector<int> a(sa.size());
    vector<int> b(sb.size());


    int asum=0;
    int bsum=0;


    vector<int> prea(sa.size());
    vector<int> preb(sb.size());

    for(int i=0; i<sa.size(); i++){
        a[i]=sa[i]-'0';
        asum+=a[i];
        prea[i]=asum%10;
    }
    for(int i=0; i<sb.size(); i++){
        b[i]=sb[i]-'0';
        bsum+=b[i];
        preb[i]=bsum%10;
    }

    if(bsum%10!=asum%10){
        cout<<-1<<endl;
        return;
    }

    
    vector<vector<int>> dp(sa.size(),vector<int>(sb.size(),0));

    for(int i=0; i<sa.size(); i++){
        for(int j=0; j<sb.size(); j++){
            if(prea[i]==preb[j]){
                if(i>0&&j>0){
                    dp[i][j]=dp[i-1][j-1]+1;
                }else{
                    dp[i][j]=1;
                }
            }else{
                if(j>0){
                dp[i][j]=max(dp[i][j],dp[i][j-1]);
                }
                if(i>0){
                    dp[i][j]=max(dp[i][j],dp[i-1][j]);
                }
            }
            
            
            
        }

    }

    cout<< dp[sa.size()-1][sb.size()-1]<<endl;

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