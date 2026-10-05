#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n,m;
    cin>>n>>m;

    bool fail=false;

    vector<int > nums(n+3,1);
    for(int i=0; i<m; i++){
        int a,e;
        cin>>a>>e;
        if(e<a){
            fail=true;
        }
        if(e-a==1){
            nums[a]=0;
        }
    }

    if(fail==true){
        cout<<-1<<endl;
        return;
    }
    int count=0;
    for(int i=1; i< n; i++){
        count+=nums[i];
    }

    cout<<count<<endl;
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