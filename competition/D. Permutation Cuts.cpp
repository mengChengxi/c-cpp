#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 998244353;
#define mkp make_pair

void solve() {
    int n;

    cin>>n;

    vector<int> nums(n-1);

    for(int i=0; i<n-1; i++){
        cin>>nums[i];
    }

      vector<int> pre(n,0);
    for(int i=0; i<n-1; i++){
        if(nums[i]==n){
            cout<<0<<endl;
            return;
        }
        pre[nums[i]]=1;
    }

    int free=0;
    int last=n-1;

    if(pre[n-1]==0){
        cout<<0<<endl;
        return;
    }

    vector<int> bas(n,0);
    int increase=1;
    for(int i=0 ; i<n-2; i++){
        if(nums[i]<nums[i+1]){
            if(increase==0){
                cout<<0<<endl;
                return;
            }
            increase=1;
            
        }else if(nums[i]>nums[i+1]){
            increase=0;
         
        }else{
            bas[nums[i]]++;
        }
    }
  
    long long ans=1;
    for(int i=n-2; i>=1; i--){
        if(pre[i]==1){
            continue;
        }

        for(int j=last; j>i; j--){
            free+=bas[j];
        }
        last=i;
        ans=ans*free%mod;
        free--;
    }

    cout<<ans*2%mod<<endl;



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