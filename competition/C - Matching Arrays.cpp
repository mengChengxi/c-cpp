#include <bits/stdc++.h>
#include <utility>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n,target;
    cin>>n>>target;

    vector<pair<int,int>> a(n);
    vector<pair<int,int>> b(n);
    for(int i=0; i<n; i++){
        cin>>a[i].first;
        a[i].second=i;
    }
    for(int i=0; i<n; i++){
        cin>>b[i].first;
        b[i].second=i;
    }

    sort(a.begin(),a.end());
    sort(b.begin(),b.end());

    vector<int> out(n);
    vector<pair<int, int>  > newb;
    for(int i=target; i<n; i++){
        newb.push_back(b[i]);
    }
    for(int i=0; i<target; i++){
        newb.push_back(b[i]);
    }
    

    for(int i=0; i<n; i++){
        if(newb[i].first<a[i].first){
            target--;
        }
        out[a[i].second]=newb[i].first;
    }

    if(target!=0){
        cout<<"NO"<<endl;
    }else{
        cout<<"YES"<<endl;
        for(int i=0; i<n; i++){
            cout<<out[i]<<" ";
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