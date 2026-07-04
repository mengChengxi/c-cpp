#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

vector<vector<int>> tree;
long long total=0;


int dfs(int node, int parent){
    int first=0;
    int second=0;
    for(int i=0; i<tree[node].size(); i++){
        if(tree[node][i]==parent){
            continue;
        }
        int v=dfs(tree[node][i],node);
        if(v>first){
            second=first;
            first=v;
        }else if(v>second){
            second=v;
        }


    }   

    total+=second+1;


    return first+1;
}

void solve() {
    int n;
    cin>>n;
    total=0;

    vector<int> numtree(n-1);

    for(int i=0; i<n-1; i++){
        cin>>numtree[i];
    }

    vector<vector<int>> ttree(n+1);

    tree=ttree;
    for(int i=0; i<n-1; i++){
        int from =i+2;
        int to = numtree[i];

        tree[from].push_back(to);
        tree[to].push_back(from);

    }

    dfs(1,0);

    cout<<total<<endl;

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