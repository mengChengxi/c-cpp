#include <bits/stdc++.h>
#include <iostream>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

vector<int> nodes;
vector<vector<int>> tree;

vector<int> finished;

void dfs(int current, int f){
    unordered_map<int, int> mp;
    //mp.reserve(tree[current].size()+5); // 预分配空间防止多次 rehash
    // mp[key] = val;      // 插入或修改
    // mp.count(key);      // 检查是否存在 (1 or 0)
    // mp.erase(key);      // 删除
    // for (auto const& [k, v] : mp) {  }
    mp[nodes[current]]=1;

    for(int i=0; i<tree[current].size(); i++){
        if(mp.count(nodes[tree[current][i]])==1){
            finished[nodes[tree[current][i]]]=1;
        }else{
            mp[nodes[tree[current][i]]]=1;
        }
        if(tree[current][i]!=f){
            dfs(tree[current][i],current);
        }
    }
}

void solve() {
    int n;
    cin>>n;
    vector<int> tnodes(n+1);
    vector<vector<int>> ttree(n+1);
    vector<int> tfinished(n+1);


    nodes=tnodes;
    tree=ttree;
    finished=tfinished;
    nodes[0]=-1;
    for(int i=1; i<=n; i++){
        cin>>nodes[i];
    }

    for(int i=1; i<=n-1; i++){
        int f,t;
        cin>>f>>t;
        tree[f].push_back(t);
        tree[t].push_back(f);
    }
    dfs(1,0);
    for(int i=1; i<n+1; i++){
        cout<<finished[i];
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