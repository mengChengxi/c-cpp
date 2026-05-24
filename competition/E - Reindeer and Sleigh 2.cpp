#include <bits/stdc++.h>
#include <pthread.h>
#include <utility>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;
    cin>>n;
    vector<pair<int, int> > reindeer(n);
    for(int i=0; i<n; i++){
        cin>>reindeer[i].first;
        cin>>reindeer[i].second;
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