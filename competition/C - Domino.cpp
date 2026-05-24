#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;
    cin>>n;
    vector<int> d(n);
    for(int i=0; i<n; i++)
    {
        cin>>d[i];
    }

    int far=0;
    for(int i=0; i<n; i++){
        if(i>far){
            cout<<far+1<<endl;
            return;
        }
        far=max(far,i+d[i]-1);
        
    }
    cout<<n<<endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int dashabi;
    
        solve();
    
    return 0;
}