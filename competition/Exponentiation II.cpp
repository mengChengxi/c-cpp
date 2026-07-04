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
    long long a,b,c;
    cin>>a>>b>>c;

    mod=1e9 + 6;
    long long e=fastPower(b, c);
    mod=1e9 + 7;
    long long res=fastPower(a, e);
    
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