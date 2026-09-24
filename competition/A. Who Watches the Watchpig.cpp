#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;
    cin>>n;
    int k;
    cin>>k;

    string s;
    cin>>s;

    if(n<2*k){
        cout<<-1<<endl;
        return;
    }
    int c=0;
    for(int i=0; i<k; i++){
        if(s[i]=='L'){
            c++;
        }
    }

    for(int i=n-1; i>=n-k; i--){
        if(s[i]=='R'){
            c++;
        }
    }

    cout<<c<<endl;



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