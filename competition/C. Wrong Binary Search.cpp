#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;
    cin>>n;
    string s;
    cin>>s;

    vector<int> nums(n);
    for(int i=1; i<=n; i++){
        nums[i-1]=i;
    }

    int invers=-1;
    for(int i=0; i<n; i++){
        if(s[i]=='0'){
            if(invers==-1){
                invers=i;
            }else{

            }
        }else{
            if(invers!=-1){
                if(i-invers==1){
                    cout<<"NO"<<endl;
                    return;
                }
                for(int j=invers; j<i; j++ ){
                    nums[j]=i-(j-invers);
                }
            }
            invers=-1;
        }
    }
    if(invers!=-1){
        if(n-invers==1){
            cout<<"NO"<<endl;
            return;
        }
        for(int j=invers; j<n; j++ ){
            nums[j]=n-(j-invers);
        }
    }
    cout<<"YES"<<endl;
    for(int i=0; i<nums.size();i++){
        cout<<nums[i]<<" ";
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