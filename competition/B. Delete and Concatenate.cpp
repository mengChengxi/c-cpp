#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    long long n;
    long long c;
    cin>>n;
    cin>>c;

    vector<long long> nums(n);
     for(int i=0; i<n; i++){
        
        cin>>nums[i];
    }
    for(int i=0; i<n; i++){

        nums[i]-=c;
    }

    sort(nums.begin(),nums.end());

    int de=n/2;
    int keep=n-de;

    long long sum=0;
    for(int i=de; i<n; i++){
        sum+=nums[i];
    }
    for(int i=0; i<de; i++){
        if(nums[i]>0){
            sum+=nums[i];
        }
        
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

struct Kosaraju {
    int n;
    int scc_cnt;
    vector<vector<int>> adj;
    vector<vector<int>> rev_adj;
    vector<bool> vis;
    vector<int> order;
    vector<int> scc;

    Kosaraju(int _n) : 
        n(_n), 
        scc_cnt(0), 
        adj(_n + 1),
        rev_adj(_n + 1), 
        vis(_n + 1, false), 
        scc(_n + 1, 0) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        rev_adj[v].push_back(u);
    }

    void dfs1(int u) {
        vis[u] = true;
        for (int v : adj[u]) {
            if (!vis[v]) dfs1(v);
        }
        order.push_back(u);
    }
 
    void dfs2(int u) {
        vis[u] = true;
        scc[u] = scc_cnt;
        for (int v : rev_adj[u]) {
            if (!vis[v]) dfs2(v);
        }
    }

    int build() {
        for (int i = 1; i <= n; i++) {
            if (!vis[i]) dfs1(i);
        }
        fill(vis.begin(), vis.end(), false);
        for (int i = n - 1; i >= 0; i--) {
            int u = order[i];
            if (!vis[u]) {
                scc_cnt++;
                dfs2(u);
            }
        }
        return scc_cnt;
    }
};