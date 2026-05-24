#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n,q;
    cin>>n>>q;

    vector<int> nums(n);
    for(int i=0; i<n; i++){
        cin>>nums[i];
    }

    vector<long long> pren(n);
    pren[0]=nums[0];
    for(int i=1; i<n; i++){
        pren[i]=pren[i-1]+nums[i];
    }

    int indent=0;
    while(q--){
        int t;
        cin>>t;

        if(t==1){
            int in;
            cin>>in;
            indent=(indent+in)%n;
        }else{
            int l,r;
            cin>>l>>r;

            l+=indent;
            l--;
            l%=n;
            
            
            r+=indent;
            r--;
            r%=n;
            
            if(r<l){

                long long sum=pren[r]+pren[n-1]-pren[l-1];
                cout<<sum<<endl;

            }else{
                if(l==0){
                    long long sum=pren[r];
                    cout<<sum<<endl;
                    continue;
                }
                long long sum=pren[r]-pren[l-1];
                cout<<sum<<endl;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}