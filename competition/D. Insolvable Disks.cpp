#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;
    cin>>n;

    vector<int> center(n);
    for(int i=0; i<n; i++){
        int t;
        cin>>t;
        center[i]=t;
    }

    int count=n-1;
    int leftbound=-1;
    int rightbound=-1;//cannot reach for both.

    for(int i=0; i<n; i++){
        if(leftbound==-1){
            leftbound=center[i];
            rightbound=center[i+1];
            continue;
        }
        if(center[i]<=leftbound){
            leftbound=center[i];
            rightbound=center[i]+(center[i]-center[i-1]);
            count--;
        }else if(leftbound<center[i]&&rightbound>center[i]){
            rightbound=center[i]+(center[i]-leftbound);
            leftbound=center[i];
        }else if(rightbound<=center[i]){
            int temp=rightbound;
            rightbound=center[i]+(center[i]-leftbound);

            leftbound=center[i]+(center[i]-temp);
        }

    }

    cout<<count<<endl;

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