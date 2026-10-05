#include <bits/stdc++.h>
#include <utility>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

int dis(int x1, int y1, int x2, int y2){
    return abs(x1-x2)+abs(y1-y2);
}

void solve() {
    int n,k;
    cin>>n>>k;
    


    vector<vector<pair<int,int>>> rank(k+1);
    
    vector<vector<int>> mapp(n,vector<int>(n));
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            int r;
            cin>>r;
            if(r==1){
                mapp[i][j]=0;
            }else{
                mapp[i][j]=INF;
            }
            
            rank[r].push_back({i,j});
        }
    }

    int glomin=INF;
    for(int i=1; i<k; i++){
        //between i and i+1
        int a=0;
        for(pair<int, int> cur: rank[i+1]){
            for(auto prev: rank[i] ){
                
                if(i+1==k){
                    glomin=min(glomin,mapp[prev.first][prev.second]+dis(cur.first,cur.second,prev.first,prev.second));
                }else{
                    mapp[cur.first][cur.second]=min(mapp[cur.first][cur.second],mapp[prev.first][prev.second]+dis(cur.first,cur.second,prev.first,prev.second));
                }
            }
        }
    }

    if(k==1){
        cout<<0<<endl;
        return;
    }
    if(glomin==INF){
        cout<<-1<<endl;
    }else{
        cout<<glomin<<endl;
    }
    

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
        solve();
    
    return 0;
}