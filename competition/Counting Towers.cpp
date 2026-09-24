#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    vector<long long> res(10000005);
    
    res[0]=1;
    res[1]=2;
    res[2]=8;
    long long sum=3;
    for(int i=3; i<res.size(); i++){
        res[i]=((res[i-1]-sum+mod)*3+res[i-1]+sum+res[i-1])%mod;
        sum=(sum+res[i-1])%mod;
    }

    int t;
    cin>>t;

    while(t--){
        int c;
        cin>>c;

        cout<<res[c]<<endl;
    }



}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
        solve();
    
    return 0;
}