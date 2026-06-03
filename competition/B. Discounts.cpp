#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n,k;
    cin>>n>>k;
    vector<int> ns(n);
    vector<int> ks(k);
    for(int i=0; i<n; i++){
        cin>>ns[i];
    }
    for(int i=0; i<k; i++){
        cin>>ks[i];
    }

    sort(ns.begin(),ns.end());
    sort(ks.begin(),ks.end());


    long long cost=0;
    int pay=n-1;

    for(int i=0; i<k; i++){
        if(ks[i]==1){
            if(pay<0){
                break;
            }
            cost+=ns[pay];
            pay--;
            
            continue;
        }else{
            if(pay-(ks[i]-1)<0){
                break;
            }
            pay-=(ks[i]-1);
            
            cost+=ns[pay];
            pay--;
        }
    }
    long long total=0;
    for(int i=0; i<n; i++){
        total+=ns[i];
    }

    cout<<total-cost<<endl;

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