#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    
    vector<int> a(n);
    vector<int> S(n, 0); 

    

    
    for  (int i=0;i<n;i++) {
        cin>>a[i];
        S[i]=(a[i]==1||a[i]==2)?1:-1;
        if(i>0){
            S[i]+=S[i-1];
        }
    }


    
    vector<int> max_S(n, -1e9);
    max_S[n-2]=S[n-2];
    for(int i=n-3;i >=0;i--) {
        max_S[i]=max(S[i],max_S[i+1]);
    }

    int cnt1=0;
    int cnt2=0;
    int cnt3=0;
    
    
     

    for(int i=0;i<n-2;i++){
        if(a[i]==1)   cnt1++;
        else if(a[i]==2) cnt2++;
        else cnt3++;

        if(cnt1>=cnt2+cnt3){
            if(max_S[i+1]>=S[i]){
                cout<<"YES\n";
                return;
            }
        }
    }
    
    cout<<"NO\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}