#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;
    cin>>n;
    
    int one=0;
    int zero=0;
    for(int i=0 ; i<n; i++){
        int t;
        cin>>t;
        one+=t;
        zero+=(1-t);
    }

    if(one>=zero){
        cout<<"Bessie"<<endl;
    }else{
        cout<<"Elsie"<<endl;
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