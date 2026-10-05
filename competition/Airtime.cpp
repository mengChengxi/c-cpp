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
    for(int i=0; i<n; i++){
        cin>>nums[i];
    }

    int count=0;
    for(int i=2; i<n; i++){
        if(nums[i-1]-nums[i-2]>nums[i]-nums[i-1]){
            count++;
        }
    }
    
    cout<<count<<endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

        solve();
    
    return 0;
}