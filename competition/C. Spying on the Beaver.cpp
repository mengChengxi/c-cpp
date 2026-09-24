#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;

    cin>>n;

    vector<int> tree(n-1);
    vector<int> level(n+5);
    for(int i=0; i<n-1; i++){
        cin>>tree[i];
    }
    
    level[1]=0;

    for(int i=0 ; i<n-1; i++){
        level[i+2]=level[tree[i]]+1;
    }


    int m;
    cin>>m;
    vector<int> dam(m);
    for(int i=0; i<m; i++){
        cin>>dam[i];
    }

    cout<<m-1<<" ";

    int minn=INF;
    int mini=-1;
    for(int i=0; i<m; i++){
        if(level[dam[i]]<minn){
            mini=i;
            minn=level[dam[i]];
        }
    }
    
    for(int i=0 ; i<m; i++){
        if(i!=mini){
            cout<<dam[i]<<" ";
        }
        
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