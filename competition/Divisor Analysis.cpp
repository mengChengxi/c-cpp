#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
 int mod = 1e9 + 7;
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
    vector<long long> prime(n);
    vector<long long> power(n);

    for(int i=0; i<n; i++){
        cin>>prime[i];
        cin>>power[i];
    }

    long long divisors=1;

    for(int i=0; i<n; i++){
        divisors=(divisors*(power[i]+1))%mod;
    }

    long long sum=1;

    for(int i=0; i<n; i++){
        sum=(sum*(fastPower(prime[i], power[i]+1)-1+mod)*modInverse(prime[i]-1))%mod;
    }

    long long product=1;
    long long times=0;
    for(int i=0; i<n; i++){
        times+=power[i];
    }

    
    vector<long long> timespower(n);
    mod-=1;
    for(int i=0; i<n; i++){
        timespower[i]=(power[i]%mod*times)%mod;
    }
    mod++;
    for(int i=0; i<n; i++){
        product=product*fastPower(prime[i], timespower[i])%mod;
    }

    cout<<divisors<<" "<<sum<<" "<<product<<endl;

    


    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

        solve();
    
    return 0;
}