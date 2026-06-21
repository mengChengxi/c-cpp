#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    string s;
    cin>>s;


    

    vector<int> ds;

    for(int i=2; i<s.size(); i++){
        if(s[i]=='A'){
            if(s[i-1]=='B'&&s[i-2]=='C'){
                ds.push_back(-1);
            }
        }else if(s[i]=='C'){
            if(s[i-1]=='B'&&s[i-2]=='A'){
                ds.push_back(1);
            }
        }
    }

    int sum=0;
    for(int i=0; i<ds.size(); i++){
        if(ds[i]==1){
            sum++;
        }
    }
    int tsum=0;
    int maxn=0;
    for(int i=0; i<ds.size(); i++){
        tsum+=ds[i];
        if(tsum<0){
            tsum=0;
        }
        maxn=max(maxn,tsum);

        
    }

    cout<<sum-maxn<<endl;



}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
   
   
        solve();
    
    return 0;
}