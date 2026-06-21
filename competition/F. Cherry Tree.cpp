#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

vector<vector<int>> tree;

int dfs(int node, int parent){

    if(tree[node].size() == 1 && node != 1){
        return 1;
    }
    int status=-1;
    for(int i=0; i<tree[node].size(); i++){
        if(tree[node][i]==parent){
            continue;
        }

        int s=dfs(tree[node][i],node);
        if(status==-1){
            status=s;
            continue;
        }
        int s1=0;
        int s2=0;
        int s3=0;
        if(s%2==1){
            s1=(status<<1);
            s1=((s1>>3)+s1)%8;
        }
        if((s>>1)%2==1){
            s2=(status<<2);
            s2=((s2>>3)+s2)%8;
        }
        if((s>>2)%2==1){
            s3=(status<<3);
            s3=((s3>>3)+s3)%8;
        }

        status=s1|s2|s3;

        
        


    }
    return status|1;
}

void solve() {
    int n;
    cin>>n;
    vector<vector<int>> ttree(n+1);

    tree=ttree;
    for(int i=0; i<n-1; i++){
        int f,t;
        cin>>f>>t;

        tree[f].push_back(t);
        tree[t].push_back((f));
    }

    if(dfs(1,0)&4){
        cout<<"YES"<<endl;
    }else{
        cout<<"NO"<<endl;
    }







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