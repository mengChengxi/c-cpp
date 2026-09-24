#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n,k;
    cin>>n>>k;
    
    if(k>=2*n||k<n){
        cout<<-1<<endl;
        return;
    }

    int two=2*n-k;

    int one=k-two;

    vector<vector<int>> m(n,vector<int>(n,-1));
    for(int i=0; i<two; i++){
        m[i][i]=i+1;
    }

    int s=two+1;
    for(int i=two; i<n; i++){
        m[0][i]=s;
        s++;
    }
    for(int i=two; i<n; i++){
        m[i][0]=s;
        s++;
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(m[i][j]==-1){
                m[i][j]=s;
                s++;
            }
        }
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            
                cout<<m[i][j]<<" ";
                
        }
        cout<<endl;
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