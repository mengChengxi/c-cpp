#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;
    cin>>n;
    int max1=-1;
    int max2=-1;
    for(int i=0; i<n; i++){
        int t;
        cin>>t;
        if(t>max2){
            if(t>max1){
                max2=max1;
                max1=t;
            }else{
                max2=t;
            }
        }
    }
    cout<<max1+max2<<endl;
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