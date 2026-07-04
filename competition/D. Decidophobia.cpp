#include <bits/stdc++.h>

using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    long long n,d;
    cin>>n>>d;

    long long field=2*d+1;
    vector<long long> nums(n);
    for(int i=0; i<n; i++){
        cin>>nums[i];
    }

    //vector<int> take(n);
    

    long long sum=0;

    for(int i=n-d; i<n; i++){
        
        sum+=nums[i];
    }
    for(int i=0; i<=d; i++){
        
        sum+=nums[i];
    }

    long long res=0;
    for(int i=0; i<n; i++){


        if(sum>nums[i]*field){
            res+=(sum-nums[i]);
            res-=(nums[i]*2*d);
        }

        int out=(i-d+n)%n;
        int in=(i+d+1+n)%n;
        sum-=nums[out];
        sum+=nums[in];

    }

    cout<<res<<endl;
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