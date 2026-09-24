#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair


struct DSU {
    vector<int> parent;
    vector<int> sz;
    int max_size;
    int number;

    DSU(int n) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        iota(parent.begin(), parent.end(), 0);
        max_size = 1;
        number=n;
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
            number--;
            return true;

        }
        return false;
    }

    int getSize(int i) {
        return sz[find(i)];
    }
};
void solve() {
    int n ,m;
    cin>>n>>m;

    DSU city(n);

    for(int i=0; i<m; i++){
        int a,b;

        cin>>a>>b;

        city.unite(a, b);

        cout<<city.number<<" "<<city.max_size<<endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
   
 
        solve();
    
    return 0;
}