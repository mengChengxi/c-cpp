#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair


long long fastPower(long long base, long long exp) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

long long modInverse(long long n) {
    return fastPower(n, mod - 2);
}
void solve() {
    int n;

    cin>>n;
    int sum=(1+n)*n/2;

    if(sum%2==1){
        cout<<0<<endl;
        return;
    }

    sum/=2;

    vector<long long> dp(sum+1);

    dp[0]=1;
    for(int i=1; i<n; i++){
        for(int j=sum; j-i>=0 ; j--){
            dp[j]=(dp[j]+dp[j-i])%mod;
        }
    }

    cout<<dp[sum]<<endl;

        
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

 
        solve();
    
    return 0;

    
    
    
}