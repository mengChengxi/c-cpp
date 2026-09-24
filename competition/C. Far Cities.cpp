#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;
    cin>>n;
    int dis=1;
    int far=-1;
    for(int i=2; i<=n; i++){
        cout<<"? "<<1<<" "<<i<<" "<<dis<<endl;
        fflush(stdout);
        int res;
        cin>>res;
        if(res==1){
            dis++;
            far=i;
            i--;
        }else{

        }
    }
    int far2=1;
    for(int i=1; i<=n; i++){
        if(i==far){
            continue;
        }
        cout<<"? "<<far<<" "<<i<<" "<<dis<<endl;
        fflush(stdout);
        int res;
        cin>>res;
        if(res==1){
            dis++;
            far2=i;
            i--;
        }else{

        }
    }

    cout<<"! "<<far<<" "<<far2<<" "<<dis-1<<endl;

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