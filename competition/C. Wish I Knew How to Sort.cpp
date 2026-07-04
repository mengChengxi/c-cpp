#include <bits/stdc++.h>
#include <exception>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 998244353;
#define mkp make_pair


long long fastPower(long long base, long long exp) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

long long modInverse(long long n) {
    return fastPower(n, mod - 2);
}
void solve() {
    int n;
    cin>>n;

    vector<int> nums(n);
    for(int i=0; i<n; i++){
        cin>>nums[i];
    }

    int ones=0;
    long long inverse=0;
    long long totaldis=0;
    long long currentdis=0;

    for(int i=0; i<n; i++){
        currentdis=(currentdis+ones)%mod;
        if(nums[i]==0){
            inverse+=ones;
            totaldis=(totaldis+currentdis)%mod;
        }else {
            ones++;
        }

    }

    long long total=n*(n-1)/2;

    long long res=((inverse*total)%mod*modInverse(totaldis))%mod;

    cout<<res<<endl;





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