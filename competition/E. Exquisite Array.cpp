#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

struct DSU {
    vector<int> parent;
    vector<int> sz;
    int max_size;


    long long count=0;
    DSU(int n) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        iota(parent.begin(), parent.end(), 0);
        max_size = 1;
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
            count+=((long long)sz[root_i]*(long long)sz[root_j]);
            parent[root_j] = root_i;
            
            sz[root_i] += sz[root_j];
            max_size = max(max_size, sz[root_i]);
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
    cin>>n;
    vector<int> nums(n);

    for(int i=0; i<n; i++){
        cin>>nums[i];
    }
    vector<vector<pair<int,int>>> dif(n);

    for(int i=1; i<n;i++){
        dif[abs(nums[i]-nums[i-1])].push_back({i,i-1});
    }
    DSU d(n);
    vector<long long> out(n-1);

    for(int i=n-1; i>=1; i--){
        for(int j=0; j<dif[i].size(); j++){
            d.unite(dif[i][j].first, dif[i][j].second);
        }
        out[i-1]=d.count;
    }

    for(int i=0; i<n-1; i++){
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