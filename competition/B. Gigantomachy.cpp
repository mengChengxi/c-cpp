#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n,m;
    cin>>n>>m;

    vector<int> a(n);
    vector<int> b(m);


    for(int i=0; i<n; i++){
        cin>>a[i];
    }
    for(int i=0; i<m; i++){
        cin>>b[i];
    }

    long long suma=n-1;
    long long sumb=m-1;

    
        suma+=a[0];
    
    
        sumb+=b[0];
    

    if(suma>=sumb){
        cout<<1<<endl;
    }else{
        cout<<2<<endl;
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