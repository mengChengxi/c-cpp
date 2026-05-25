#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n,m;
    cin>>n>>m;
    vector<vector<int>> nums(n);
    for(int i=0; i<n; i++){
        int t;
        cin>>t;
        for(int j=0; j<t; j++){
            int tt;
            cin>>tt;
            nums[i].push_back(tt);
        }
    }
    vector<int> totalmap(m+1,0);
    for(int i=0; i<n; i++){
        for(int j=0; j<nums[i].size(); j++){
            totalmap[nums[i][j]]++;
        }
    }



    for(int i=1; i<m+1; i++){
        if(totalmap[i]==0){
            cout<<"NO"<<endl;
            return;
        }
    }
    int c=0;
    for(int i=0; i<n; i++){
        int fail=0;
        for(int j=0; j<nums[i].size(); j++){
            totalmap[nums[i][j]]--;
            if(totalmap[nums[i][j]]==0){
                fail=1;
            }
        }
        for(int j=0; j<nums[i].size(); j++){
            totalmap[nums[i][j]]++;
        }
        if(fail==0){
            c++;
        }
    }

    if(c>=2){
        cout<<"YES"<<endl;
    }else{
        cout<<"NO"<<endl;
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