#include <bits/stdc++.h>
#include <deque>
#include <unordered_map>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int v;
    cin>>v;

    unordered_map<int, int> mp;
    deque<int> dq;
    for(int i=0; i<v-1; i++){
        int u,v,x,y;

        cin>>u>>v>>x>>y;
        if(mp.count(u)==1){
            if(x>y){
                if(u>v){
                    dq.push_back(v);
                    mp[v]=1;
                }else{
                    dq.push_front(v);
                    mp[v]=1;
                }
            }else{
                if(u>v){
                    dq.push_front(v);
                    mp[v]=1;
                }else{
                    dq.push_back(v);
                    mp[v]=1;
                }
            }
        }else if(mp.count(v)==1){
            if(x>y){
                if(v>u){
                    dq.push_back(u);
                    mp[u]=1;
                }else{
                    dq.push_front(u);
                    mp[u]=1;
                }
            }else{
                if(v>u){
                    dq.push_front(u);
                    mp[u]=1;
                }else{
                    dq.push_back(u);
                    mp[u]=1;
                }
            }
        }else{
            mp[u]=1;
            mp[v]=1;

            if(x>y){
                if(u>v){
                    dq.push_back(u);
                    dq.push_back(v);
                }else{
                    dq.push_back(v);
                    dq.push_back(u);
                }
            }else{
                if(u>v){
                    dq.push_back(v);
                    dq.push_back(u);
                    
                }else{
                    dq.push_back(u);
                    dq.push_back(v);
                    
                }
            }

        }
        
    }
    vector<int> out(v+1);
    for(int i=0; i<dq.size(); i++){
        out[dq[i]]=i+1;
    }

    for(int i=1; i<v+1; i++){
        cout<<out[i]<<" ";
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