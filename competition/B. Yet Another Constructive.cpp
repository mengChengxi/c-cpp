#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n,k,m;
    cin>>n>>k>>m;

    if(k>m){
        cout<<"NO"<<endl;
        return;
    }
    cout<<"YES"<<endl;
    cout<<m-(k-1)<<" ";
    for(int i=1; i<n; i++){
        cout<<1<<" ";
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