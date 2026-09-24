#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n,m; 

    cin>>n>>m;
    vector<int> nums(n);
    vector<int> bas(m+3,0);
    for(int i=0; i<n; i++){
        cin>>nums[i];
    }
    for(int i=0; i<n; i++){
        bas[nums[i]]++;
    }
    vector<int> prebas(m+3);
    prebas[0]=bas[0];
    for(int i=1; i<prebas.size(); i++){
        prebas[i]=prebas[i-1]+bas[i];
    }
    vector<long long> eachmax(m+1);

    for(int i=1; i<=m; i++){
        long long blocks=0;
        blocks+=(bas[i]);
        for(int j=1;j*i<=m; j++){
            
            if((j+1)*i<=m){
                blocks+=(bas[(j+1)*i]);
            }
            blocks+=(n-prebas[j*i]);
            
            int time=__lg(j)+1;
            eachmax[time]=max(eachmax[time],blocks);
        }
    }

    
        cout<<eachmax[1]<<endl;

    
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