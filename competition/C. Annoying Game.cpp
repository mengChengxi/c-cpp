#include <bits/stdc++.h>
#include <climits>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair





void solve() {
    int n,k;
    cin>>n>>k;

    vector<long long> nums(n);
    for(int i=0;i<n; i++){
        cin>>nums[i];
    }
    vector<long long> b(n);

    for(int i=0;i<n; i++){
        cin>>b[i];
    }
    if(k%2==0){
        int p=0;
        long long mm= LLONG_MIN;
        for(int i=0;i<n; i++){
            if(nums[i]>0){
                p=1;
                break;
            }
            mm=max(nums[i],mm);
        }
        if(p==0){
            cout<<mm<<endl;
            return;
        }



        long long maxn=0;
        long long currentmax=0;
        for(int i=0; i<n; i++){
            currentmax+=nums[i];
            if(currentmax<0){
                currentmax=0;
            }
            maxn=max(maxn,currentmax);
        }
        cout<<maxn<<endl;
        return;
    }
    

    int p=0;
    long long mm=LLONG_MIN;
    for(int i=0;i<n; i++){
        if(nums[i]>0){
            p=1;
            break;
        }
        mm=max(nums[i]+b[i],mm);
    }
    if(p==0){
        cout<<mm<<endl;
        return;
    }
    long long maxn=0;
    long long currentmax=0;
    long long maxadd=0;
    for(int i=0; i<n; i++){
        currentmax+=nums[i];
        if(b[i]>maxadd){
            currentmax=currentmax-maxadd+b[i];
            maxadd=b[i];
        }
        if(currentmax<0){
            currentmax=0;
            maxadd=0;
            continue;
            
        }
        if(currentmax-maxadd<0){
            maxadd+=currentmax-maxadd;
        }
        
        maxn=max(maxn,currentmax);
    }
    cout<<maxn<<endl;
        


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