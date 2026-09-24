#include <bits/stdc++.h>
#include <string>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;
    cin>>n;

    string a;
    string b;

    cin>>a;
    cin>>b;

    vector<int> a1(n,0);
    vector<int> a2l(n,0);
    vector<int> a2r(n,0);
    vector<int> a2lr(n,0);

    for(int i=1; i<n-1; i++){
        if(b[i-1]=='1'&&b[i+1]=='1'&&a[i]=='0'){
            a1[i]=1;
        }
    }
    vector<int> b1(n,0);
    for(int i=1; i<n-1; i++){
        if(a[i-1]=='0'&&a[i+1]=='0'&&b[i]=='0'){
            b[i]='1';
            b1[i]=1;
        }
    }

    for(int i=1; i<n-1; i++){
        if(b[i-1]=='1'&&b[i+1]=='1'&&a[i]=='0'&&a1[i]==0&&b1[i-1]==1&&b1[i+1]==0){
            a2l[i]=1;
        }
    }
    for(int i=1; i<n-1; i++){
        if(b[i-1]=='1'&&b[i+1]=='1'&&a[i]=='0'&&a1[i]==0&&b1[i+1]==1&&b1[i-1]==0){
            a2r[i]=1;
        }
    }
    for(int i=1; i<n-1; i++){
        if(b[i-1]=='1'&&b[i+1]=='1'&&a[i]=='0'&&a1[i]==0&&b1[i+1]==1&&b1[i-1]==1){
            a2lr[i]=1;
        }
    }

    vector<int> prea(n+1,0);
    for(int i=1; i<=n; i++){
        if(a[i-1]=='1'){
            prea[i]=prea[i-1]+1;
        }else{
            prea[i]=prea[i-1];
        }
    }
    vector<int> prea1(n+1,0);
    for(int i=1; i<=n; i++){
        if(a1[i-1]==1){
            prea1[i]=prea1[i-1]+1;
        }else{
            prea1[i]=prea1[i-1];
        }
    }
    vector<int> prea2l(n+1,0);
    for(int i=1; i<=n; i++){
        if(a2l[i-1]==1){
            prea2l[i]=prea2l[i-1]+1;
        }else{
            prea2l[i]=prea2l[i-1];
        }
    }
    vector<int> prea2r(n+1,0);
    for(int i=1; i<=n; i++){
        if(a2r[i-1]==1){
            prea2r[i]=prea2r[i-1]+1;
        }else{
            prea2r[i]=prea2r[i-1];
        }
    }
    vector<int> prea2lr(n+1,0);
    for(int i=1; i<=n; i++){
        if(a2lr[i-1]==1){
            prea2lr[i]=prea2lr[i-1]+1;
        }else{
            prea2lr[i]=prea2lr[i-1];
        }
    }

    int q;
    cin>>q;
    while (q--) {
        int l,r;
        cin>>l>>r;

        int res=0;
        res+=prea[r]-prea[l-1];
        if(r-1>l){
            res+=prea1[r-1]-prea1[l];
        }
        if(r-1>l+1){
            res+=prea2l[r-1]-prea2l[l+1];
        }
        if(r-2>l){
            res+=prea2r[r-2]-prea2r[l];
        }
        if(r-2>l+1){
            res+=prea2lr[r-2]-prea2lr[l+1];
        }

        cout<<res<<endl;
        
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