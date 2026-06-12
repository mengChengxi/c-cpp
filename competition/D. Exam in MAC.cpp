#include <algorithm>
#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    long long n,c;
    cin>>n>>c;
    long long count=((c+1)+1)*(c+1)/2;

    vector<int> nums(n);
    for(int i=0; i<n; i++){
        cin>>nums[i];
    }

    vector<int> even;
    vector<int> odd;

    for(int i=0; i<n; i++){
        if(nums[i]%2==0){
            even.push_back(nums[i]);
        }else{
            odd.push_back(nums[i]);
        }
    }
    sort(even.begin(),even.end());
    sort(odd.begin(),odd.end());
    for(int i=0; i<n; i++){
        count-=((nums[i])/2+1);
        // 03 12 
    }

    for(int i=0; i<n; i++){
        long long minus=c-nums[i]+1;

        //01,12,23,1,3,5
        //sum in [nums[i],2c-nums[i]]
        if(nums[i]%2==1){
            auto left = lower_bound(odd.begin(), odd.end(), nums[i]);//first element >= i
            auto right = upper_bound(odd.begin(), odd.end(), 2*c-nums[i])-1;//first element > i
            minus-=(right-left+1);
        }else{
            auto left = lower_bound(even.begin(), even.end(), nums[i]);//first element >= i
            auto right = upper_bound(even.begin(), even.end(), 2*c-nums[i])-1;//first element > i
            minus-=(right-left+1);

        }
       
        count-=minus;
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