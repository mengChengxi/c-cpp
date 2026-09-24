#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;
    cin>>n;
    if(n==1){
         cout<<1<<endl;
    }else if(n==2){
        cout<<-1<<endl;
    }else{
        vector<long long> a(n,0);
        a[0]=1;
         a[1]=2;
          a[2]=3;
        long long sum=6;
        for(int i=3; i<n; i++){
            a[i]=sum;
            sum*=2;
        }
        for(int i=0; i<n; i++){
            cout<<a[i]<<" ";
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