#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n,m;
    cin>>n>>m;
    vector<string> grid(n);
    for(int i=0; i<n; i++){
        cin>>grid[i];
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if((i+j)%2==0){
                if(grid[i][j]=='A'){
                    cout<<"C";
                }else{
                    cout<<"A";
                }
            }else{
                if(grid[i][j]=='B'){
                    cout<<"D";
                }else{
                    cout<<"B";
                }
            }
            
            
        }
        cout<<"\n";
        
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    
        solve();
    
    return 0;
}