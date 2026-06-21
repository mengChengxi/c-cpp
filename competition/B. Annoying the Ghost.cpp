#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;
    cin>>n;
    vector<int> a(n);
    vector<int> b(n);

    for(int i=0; i<n; i++){
        cin>>a[i];
    }
    for(int i=0; i<n; i++){
        cin>>b[i];
    }
    int moves=0;
    for(int i=0; i<n; i++){
        int done=0;
        for(int j=i; j<n; j++){
            if(a[j]<=b[i]){
                moves+=(j-i);
                a.erase(a.begin() + j);
                a.insert(a.begin() + i, -1); 
                done=1;
                break;
            }
            
        }
        if(done==0){
            cout<<-1<<endl;
            return;
        }
    }


    cout<<moves<<endl;
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