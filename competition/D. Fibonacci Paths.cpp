#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 998244353;
#define mkp make_pair
//#define int long long


struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
unordered_map<long long, int, custom_hash> safe_map;

vector<long long> vertices;
vector<pair<int,int>> edges;
vector<unordered_map<long long, pair<int,vector<pair<int, int>>>, custom_hash>> g;

vector<int> dp;



int dfs(int e){

    if(dp[e]!=-1){
        return dp[e];
    }

    int l=1;
    long long target= vertices[edges[e].first]+vertices[edges[e].second];

    if(g[edges[e].second].count(target)==1){
        if(g[edges[e].second][target].first==-1){
            for(int i=0; i<g[edges[e].second][target].second.size(); i++){
            
                l+=dfs(g[edges[e].second][target].second[i].second);
                l%=mod;
            
            
            }
            g[edges[e].second][target].first=l-1;

        }else{
            l+=g[edges[e].second][target].first;
        }

        


    }

    
    
    dp[e]=l;

    return l;

}


void solve() {
    int v,e;
    cin>>v>>e;
    vector<long long> tvertices(v+1);
    vector<pair<int,int>> tedges(e+1);
    //vector<vector<pair<int, int>>> tg(v+1,vector<pair<int, int>>());
    vector<unordered_map<long long, pair<int,vector<pair<int, int>>>, custom_hash>> tg(v+1);

    vector<int> tdp(e+1,-1);
    for(int i=0; i<v; i++){
        long long t;
        cin>>t;
        tvertices[i+1]=t;
    }

    for(int i=0; i<e; i++){
        int f,t;
        cin>>f>>t;
        tedges[i+1]={f,t};
        tg[f][tvertices[t]].second.push_back({t,i+1});
        tg[f][tvertices[t]].first=-1;
    }
    g = move(tg);

    vertices = move(tvertices);
    edges = move(tedges);
    dp = move(tdp);



    for(int i=1; i<e+1; i++){
        dfs(i);
    }

    int sum=0;
    for(int i=1; i<e+1; i++){
        sum+=dp[i];
        sum%=mod;
    }

    cout<<sum<<endl;

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