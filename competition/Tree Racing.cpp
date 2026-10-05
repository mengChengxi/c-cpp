#include <bits/stdc++.h>
#include <pthread.h>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair
vector<vector<int>> tree;
vector<int> racer;
vector<int> isspec;
vector<priority_queue<pair<long long,int>>> spectime;
int k;

void dfs(int node,int p, int prevspec,int length){
    if(isspec[node]){
        if(racer[node]!=-1){
            spectime[node].push({0,node});
        }
    }
   
    
    for(int i=0; i<tree[node].size(); i++){
        if(tree[node][i]!=p){
            if(isspec[node]){
                dfs( tree[node][i], node,node,1);
            }else{
                dfs( tree[node][i], node,prevspec,length+1);
            }

        }
    }
    if(isspec[node]){
        if(racer[node]!=-1){
            for(int i=0; i<k; i++){
                spectime[prevspec].push(spectime[node].top());
                spectime[node].pop();
            }
            
        }
    }

    if(racer[node]!=-1){
        spectime[prevspec].push({racer[node]*length,node});
    }

}


void solve() {
    int n,m;
    cin>>n>>m>>k;

    vector<vector<int>> ttree(n+3);
    vector<int> tisspec(n+3,0);
    vector<int> tracer(n+3,-1);
    isspec=tisspec;
    racer=tracer;
    tree=ttree;
    for(int i=0 ; i<n-1; i++){
        int a,b;
        cin>>a>>b;

        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    for(int i=0; i<m; i++){
        int pos,v;
        cin>>pos>>v;
        racer[pos]=v;
    }
    int e;
    cin>>e;
    int c;
    cin>>c;


    vector<priority_queue<pair<long long, int>>> tspectime(n+3);
    spectime=tspectime;

    for(int i=1 ;i<=c; i++){
        int x;
        cin>>x;
        isspec[x]=i;
    }

    for(int i=0; i<n; i++){

    }

    
    

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    solve();
    
    return 0;
}

const long long LLINF = 1e18;

// adj[u] = {v, weight}
vector<long long> dijkstra(int n, int start, const vector<vector<pair<int, long long>>>& adj) {
    vector<long long> dist(n + 1, LLINF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (const auto& edge : adj[u]) {
            int v = edge.first;
            long long w = edge.second;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}