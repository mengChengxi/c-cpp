#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;
    cin>>n;
    vector<int> nums(n);

    vector<int> numafter(n+2,0);
    vector<int> pairafter(n+2,0);
    int count=1;
    for(int i=0; i<n; i++){
        cin>>nums[i];
    }

    for(int i=0; i<n; i++){

        int must=count-pairafter[nums[i]+1];
        count=(count+must)%mod;

        vector<int> oldpairafter=pairafter;


        for(int j=0; j<=pairafter.size(); j++){
            if(j<=nums[i]){
                pairafter[j]=(pairafter[j]+numafter[nums[i]+1]-pairafter[nums[i]+1])%mod;
            }
        }
        for(int j=0; j<numafter.size(); j++){
            if(j<=nums[i]){
                numafter[j]=(numafter[j]+must)%mod; 
            }else if(numafter[j]>0){
                numafter[j]=(numafter[j]+must-oldpairafter[nums[i]+1])%mod; 
            }
            
        }
    }
    cout<<count<<endl;


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