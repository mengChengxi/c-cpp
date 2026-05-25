#include <bits/stdc++.h>
#include <ios>
#include <unordered_map>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair



void solve() {
    int n,m;
    cin>>n>>m;
    string s;
    cin>>s;

    vector<int> black(m);
    unordered_map<int, int> oldb;
    for(int i=0;i<m; i++){
        int t;
        cin>>t;
        black[i]=t;
        oldb[t]=0;
        
    }
    vector<int> newblack;
    int pos=1;
    for(int i=0; i<n; i++){
        if(s[i]=='A'){
            pos++;
            if(oldb.count(pos)==0){
                newblack.push_back(pos);
            }
        }else{
            for(int j=pos+1; j<1e9; j++){
                if(oldb.count(j)==0){
                    pos=j;
                    break;
                }
            }
            if(oldb.count(pos)==0){
                newblack.push_back(pos);
            }
            for(int j=pos+1; j<1e9; j++){
                if(oldb.count(j)==0){
                    pos=j;
                    break;
                }
            }
        }
        
    }
    for(int i=0; i<m; i++){
        newblack.push_back(black[i]);
    }
    sort(newblack.begin(),newblack.end());
    cout<<newblack.size()<<endl;
    for(int i=0; i<newblack.size(); i++){
        cout<<newblack[i]<<" ";
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