#include <bits/stdc++.h>
#include <mutex>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;
    cin>>n;
    vector<int> nums(n);

    for(int i=0; i<n ; i++){
        cin>>nums[i];
    }

    vector<int> gcdleft(n);
    gcdleft[0]=nums[0];
    vector<int> gcdright(n);
    gcdright[n-1]=nums[n-1];

    for(int i=1; i<n; i++){
        gcdleft[i]=gcd(gcdleft[i-1],nums[i]);
    }
    for(int i=n-2; i>=0; i--){
        gcdright[i]=gcd(gcdright[i+1],nums[i]);
    }

    long long sum=gcdleft[n-1];
    for(int i=1; i<n-1; i++){
        sum+=min(gcdleft[i],gcdright[i]);
    }
    cout<<sum<<endl;
}   

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

        solve();
    
    return 0;
}