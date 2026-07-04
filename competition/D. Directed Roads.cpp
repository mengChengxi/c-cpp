#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

vector<vector<int>> g;
vector<int> dis;
vector<int> nodes;
long long loopsize=0;
long long gsize=0;

void dfs(int currentdis, int node, int parent){

    gsize++;
    dis[node]=currentdis;

    if(nodes[node-1]==parent&&nodes[parent-1]==node){
        loopsize=2;
    }

    for(int i=0; i<g[node].size(); i++){
        if(g[node][i]==parent){
            continue;
        }

        if(dis[g[node][i]]!=-1){
            if(loopsize!=0){
                continue;
            }else{
                loopsize=currentdis-dis[g[node][i]]+1;
            }
        }else{
            dfs(currentdis+1,g[node][i],node);
        }
    }
}

long long fastPower(long long base, long long exp) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

long long modInverse(long long n) {
    return fastPower(n, mod - 2);
}

void solve() {
    
    int n;
    cin>>n;

    vector<vector<int>> gt(n+1);
    g=gt;
    vector<int> tdis(n+1,-1);
    dis=tdis;
    loopsize=0;

    vector<int> tnodes(n);
    nodes=tnodes;
    for(int i=0; i<n; i++){
        cin>>nodes[i];
    }

    for(int i=1; i<n+1; i++){
        int t=nodes[i-1];

        g[i].push_back(t);
        g[t].push_back(i);
    }
    long long res=1;
    for(int i=1; i<n+1; i++){

        loopsize=0;
        gsize=0;
        if(dis[i]==-1){
            dfs(1,i,0);
            res=(res*((fastPower(2,gsize))-(fastPower(2, gsize-loopsize+1))+mod)%mod)%mod;
        }
        
    }
    


    cout<<res<<endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int dashabi;
    
        solve();
    
    return 0;
}