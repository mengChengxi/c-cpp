#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair



struct DSU {
    vector<int> parent;
    vector<int> sz;
    int max_size;
    int compents;

    DSU(int n) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        iota(parent.begin(), parent.end(), 0);
        max_size = 1;
        compents=n;
    }

    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }

    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            if (sz[root_i] < sz[root_j]) swap(root_i, root_j);
            parent[root_j] = root_i;
            sz[root_i] += sz[root_j];
            max_size = max(max_size, sz[root_i]);
            compents--;
            return true;
        }
        return false;
    }

    int getSize(int i) {
        return sz[find(i)];
    }
};


void solve() {
    int n;
    int m1;
    int m2;

    cin>>n>>m1>>m2;

    DSU f(n);
    DSU g(n);

    vector<pair<int, int>> edges_F(m1);
    for(int i = 0; i < m1; i++){
        cin >> edges_F[i].first >> edges_F[i].second;
    }

    for(int i=0; i<m2; i++){
        int s,t;
        cin>>s>>t;

        g.unite(s, t);
    }

    int mustdelete=0;
    for(int i=0; i<m1; i++){
        int s=edges_F[i].first;
        int t=edges_F[i].second;

        if(g.find(s)!=g.find(t)){
            mustdelete++;
        }else{
            f.unite(s, t);
        }
    }

    cout<<mustdelete+f.compents-g.compents<<endl;

    


    
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