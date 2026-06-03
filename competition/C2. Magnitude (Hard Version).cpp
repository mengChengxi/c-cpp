#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod =  998244353;
#define mkp make_pair

void solve() {
    int n;
    cin>>n;

    vector<int> nums(n);
    for(int i=0; i<n; i++){
        cin>>nums[i];
    }

    long long minn=0;
    long long  maxn=0;

    long long mintimes=1;
    long long maxtimes=1;

    for(int i=0; i<n; i++){
        long long  newminn=0;
        long long  newmaxn=0;
        newminn=min(abs(minn+nums[i])
                ,min(abs(maxn+nums[i]),
                min(minn+nums[i],maxn+nums[i])));
        newmaxn=max(abs(minn+nums[i])
                ,max(abs(maxn+nums[i]),
                max(minn+nums[i],maxn+nums[i])));
        long long methodminn=0;
        if(abs(minn+nums[i])==newminn){
            methodminn+=mintimes;
        }
        if(abs(maxn+nums[i])==newminn){
            methodminn+=maxtimes;
        }
        if(minn+nums[i]==newminn){
            methodminn+=mintimes;
        }
        if(maxn+nums[i]==newminn){
            methodminn+=maxtimes;
        }
        


        long long methodmaxn=0;
        if(abs(minn+nums[i])==newmaxn){
            methodmaxn+=mintimes;
        }
        if(abs(maxn+nums[i])==newmaxn){
            methodmaxn+=maxtimes;
        }
        if(minn+nums[i]==newmaxn){
            methodmaxn+=mintimes;
        }
        if(maxn+nums[i]==newmaxn){
            methodmaxn+=maxtimes;
        }
        if(maxn==minn){
            methodmaxn/=2;
            methodminn/=2;

        }

        minn=newminn;
        maxn=newmaxn;

        mintimes=methodminn%mod;
        maxtimes=methodmaxn%mod;
    }

    cout<<maxtimes<<endl;
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