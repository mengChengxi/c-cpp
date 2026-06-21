#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;
    cin>>n;
    vector<int> tower(n);
    for(int i=0; i<n; i++){
        cin>>tower[i];
    }

    int minnh=INF;

    int o=0;
    for(int i=0; i<n; i++){
        minnh=min(minnh,tower[i]);
        o+=minnh;
    }

    cout<<o<<endl;
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