#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;
    cin>>n;
    vector<int> time(2*n);
    for(int i=0; i<2*n; i++){
        cin>>time[i];
    }

    vector<long long> layers(n);
    for(int i=0; i<n; i++){
        layers[i]=time[n+i]-time[n-1-i];
    }

    vector<long long> sum(n);
    sum[0]=layers[0];
    for(int i=1; i<n; i++){
        sum[i]=sum[i-1]+layers[i];
    }


    vector<long long> out(n);
    out[n-1]=sum[n-1];
    for(int i=n-2; i>=0; i--){
        out[i]=2*(sum[n-1]-sum[n-2-i])-out[i+1];
    }

    for(int i=0; i<n; i++){
        cout<<out[i]<<" ";

    }
    cout<<endl;
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