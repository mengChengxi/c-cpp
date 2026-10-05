#include <algorithm>
#include <bits/stdc++.h>
#include <cstdint>
#include <functional>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n,m,k;
    cin>>n>>m>>k;

    vector<int> isfriends(k+1,0);
    vector<int> newfriends(k+1,0);
    
    for(int i=0; i<n; i++){
        int f;

        cin>>f;
        isfriends[f]=1;

    }

    unordered_map<long long, int> mess;

    vector<vector<int>> adj(k+3);
    for(int i=0; i<m; i++){
        int a,b;
        cin>>a>>b;

        adj[a].push_back(b);
        adj[b].push_back(a);


        if(a>b){
            swap(a,b);
        }
        mess[a*1000000LL+b]++;
    }

    //case 1 seperate friends;

    for(int i=1; i<=k; i++){
        if(isfriends[i]==0){
            int add=0;
            for(int mes: adj[i]){
                
                if(isfriends[mes]==1&&i!=mes){
                    newfriends[i]++;
                }else if(i==mes){
                    newfriends[i]+=add;
                    add=1-add;
                }
            }
        }
    }
    auto nnewfriends=newfriends;
    sort(nnewfriends.begin(),nnewfriends.end(),greater<int>());

    int incre=nnewfriends[1]+nnewfriends[0];

    for(int i=1; i<=k; i++){
        if(isfriends[i]==0){
            for(int mes: adj[i]){
                if(mes==i){
                    continue;
                }
                if(isfriends[mes]==0){
                    int rela;
                    if(mes<=i){
                        rela=mess[mes*1000000LL+i];
                    }else{
                        rela=mess[i*1000000LL+mes];
                    }
                    incre=max(incre,rela+newfriends[i]+newfriends[mes]);
                }
            }
        }
    }
    
    int original=0;
    for(int i=1; i<=k; i++){
        if(isfriends[i]==1){
            for(int mes: adj[i]){
                if(isfriends[mes]==1){
                    original++;
                }
            }
        }
    }

    cout<<original/2+incre<<endl;


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