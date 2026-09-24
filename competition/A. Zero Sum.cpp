#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;
    cin>>n;
    int sum=0;
    for(int i=0; i<n; i++){
        int t;
        cin>>t;
        sum+=t;

    }

    if(sum%4==0){
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