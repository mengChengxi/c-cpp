#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

long long sum(vector<long long> &a){
    return a[0]+a[1]+a[2];
}

void solve() {

    int n;
    cin>>n;

    vector<long long > nums(n);
    for(int i=0; i<n; i++){
        cin>>nums[i];
    }

    

    if(n==2){
        cout<<max(abs(nums[0]-nums[1])*2,nums[0]+nums[1])<<endl;

    }else if(n==3&&nums[1]>nums[0]&&nums[1]>nums[2]){
        long long maxn=nums[0]+nums[1]+nums[2];
        auto left=nums;
        auto right=nums;

        long long mean=abs(left[0]-left[1]);
        left[0]=mean;
        left[1]=mean;
        maxn=max(maxn,sum(left));
        mean=abs(left[1]-left[2]);
        left[2]=mean;
        left[1]=mean;
        maxn=max(maxn,sum(left));

        mean=abs(right[1]-right[2]);
        right[2]=mean;
        right[1]=mean;
        maxn=max(maxn,sum(right));
        mean=abs(right[0]-right[1]);
        right[0]=mean;
        right[1]=mean;
        maxn=max(maxn,sum(right));

        maxn=max(maxn,3*abs(nums[1]-nums[0]));
        maxn=max(maxn,3*abs(nums[1]-nums[2]));
        maxn=max(maxn,3*nums[0]);
        maxn=max(maxn,3*nums[2]);
        

        cout<<maxn<<endl;
    }else{
        long long maxn=0;
        for(int i=0; i<n; i++){
            maxn=max(maxn,(long long)nums[i]);
        }
        cout<<maxn*n<<endl;
    }
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