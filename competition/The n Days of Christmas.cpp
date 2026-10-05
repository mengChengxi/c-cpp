#include <bits/stdc++.h>
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


    long long n;
    cin>>n;

    // cout<<modInverse(12)<<endl;
    // cout<<modInverse(4)<<endl;

    // 582309206
    // 748683265

    cout<<(((n%mod)*((n+1)%mod)%mod*(2*(n%mod)+1)%mod*582309206%mod)+(((1+n)%mod)*(n%mod)%mod*748683265%mod))%mod<<endl;


}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    solve();
    
    return 0;
}