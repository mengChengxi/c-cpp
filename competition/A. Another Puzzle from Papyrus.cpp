#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n,c;
    cin>>n>>c;

    vector<int> a(n);
    vector<int> b(n);

    for(int i=0; i<n; i++){
        cin>>a[i];
    }

    for(int i=0; i<n; i++){
        cin>>b[i];
    }

    int sum=0;

    for(int i=0; i<n; i++){
        if(a[i]-b[i]>=0){
            sum+=a[i]-b[i];
        }else{
            sum=INF;
            break;
        }
    }

    int sum2=0;
    sort(a.begin(),a.end());

    sort(b.begin(),b.end());

    for(int i=0; i<n; i++){
        if(a[i]-b[i]>=0){
            sum2+=a[i]-b[i];
        }else{
            sum2=INF;
            break;
        }
        
    }
    sum2+=c;

    sum=min(sum,sum2);

    if(sum>=INF){
        cout<<-1<<endl;
    }else{
        cout<<sum<<endl;
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