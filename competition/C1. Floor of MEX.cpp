#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;

    cin>>n;

    vector<int> nums(n);
    vector<int> res(n,1);

    for(int i=0; i<n; i++){
        cin>>nums[i];


    }
    for(int i=0; i<n; i++){
        
        for(int j=nums[i]*(i+1); j<nums[i]*(i+1)+i+1; j++){
            if(j<n){
                res[j]=0;
            }else{
                break;
            }
            
        }
    }
    int count=0;
    for(int i=0; i<n; i++){
       if (res[i]==1) {
            count++;
       }
    }

    cout<<count<<endl;
    for(int i=0; i<n; i++){
       if (res[i]==1) {
            cout<<i<<" ";
       }
    }
    cout<<endl;


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