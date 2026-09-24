#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;

    cin>>n;
    
    vector<int> nums(n);

    for(int i=0; i<n;i++){
        cin>>nums[i];
    }

    int maxn=INF;
    int minn=-INF;
    if(n%2==1){
        cout<<"NO"<<endl;
        return;
    }
    for(int i=0; i<n;i+=2){
        if(nums[i]-nums[i+1]<=1){
            cout<<"NO"<<endl;
            return;
        }

        maxn=min(nums[i],maxn);
        minn=max(nums[i+1],minn);

        if(maxn-minn<=1){
            cout<<"NO"<<endl;
            return;
        }


    }

    cout<<"YES"<<endl;

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