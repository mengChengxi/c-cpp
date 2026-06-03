#include <bits/stdc++.h>
#include <climits>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;
    cin>>n;
    vector<int> nums(n);
    for(int i=0; i<n; i++){
        cin>>nums[i];
    }
    long long minus=0;
    long long maxminus=LLONG_MAX;
    int maxi=0;
    for(int i=n-1; i>=0; i--){
        minus+=nums[i];
        if(minus>=0){
            minus=0;
        }
        if(minus<maxminus){
            maxi=i;
            maxminus=minus;
        }
    }
    long long sum=0;
    for(int i=0; i<maxi; i++){
        sum+=nums[i];
    }

    cout<<sum<<endl;
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