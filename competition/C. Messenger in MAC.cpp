#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n,l;
    cin>>n>>l;
    vector<int> a(n);
    vector<int> b(n);
    unordered_map<int, int> mapb;
    for(int i=0; i<n; i++){
        cin>>a[i];
        cin>>b[i];
        mapb[b[i]]=i;
    }

    vector<vector<int> > dp(n,vector<int>(n,-1));

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){

          
        }
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