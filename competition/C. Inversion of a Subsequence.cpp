#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    vector<int> b(n);
    for(int i=0; i<n; i++){
        cin>>a[i];
    }
    for(int i=0; i<n; i++){
        cin>>b[i];
    }

    int count10=0; 
    int count01=0; 
    int count11=0; 
    int count00=0;

    for(int i=0; i<n; i++) {
        if(a[i]==1&&b[i]==0) count10++;
        if(a[i]==0&&b[i]==1) count01++;
        if(a[i]==1&&b[i]==1) count11++;
        if(a[i]==0&&b[i]==0) count00++;
    }


    if(count10==0&&count01==0) {
        cout<<0<<endl;
        return;
    }


    if(count10>0) {
        if(count10%2==1) {
            cout<<1<<endl;
        }else{
            cout<<2<<endl;
        }
        return;
    }

    if(count11==0||count00==0) {
        cout<<-1<<endl;
    }else{
        cout<<2<<endl;
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