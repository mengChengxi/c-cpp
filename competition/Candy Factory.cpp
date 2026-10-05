#include <bits/stdc++.h>
#include <functional>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n,k;
    cin>>n>>k;

    vector<int> nums(n);

    for(int i=0; i<n; i++){
        cin>>nums[i];
    }
    nums.push_back(0);
    sort(nums.begin(),nums.end(), greater());
    while(nums[k-1]!=0){
        int sub=nums[k-1]-nums[k];
        if(sub==0){
            sub++;
        }
        
        for(int j=0; j<k ; j++){
            nums[j]-=sub;
        }
        sort(nums.begin(),nums.end(), greater());
    }
    long long sum=0;
    for(int j=0; j<k ; j++){
        sum+=nums[j];
    }

    cout<<(long long)k*nums[0]-sum<<endl;


}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
        solve();
    
    return 0;
}