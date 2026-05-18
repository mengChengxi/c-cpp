#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n,k;
    cin>>n>>k;
    //vector<int> nums(k);

    if(k%2==0){
        cout<<0<<" ";
        for(int i=0; i<k-1; i++){
            cout<<n<<" ";
        }
    }else{
        for(int i=0; i<k; i++){
            cout<<n<<" ";
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