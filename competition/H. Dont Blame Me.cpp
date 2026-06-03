#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
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
    int n,k;
    cin>>n>>k;
    vector<int> nums(64,0);
    for(int i=0; i<n; i++){
        int tt;
        cin>>tt;
        nums[tt]++;
    }


    vector<long long > methods(64,0);

    for(int i=0; i<64; i++){
        if(nums[i]==0){
            continue;
        }
        long long methodi=fastPower(2,nums[i])-1;
        vector<long long > newmethods(64,0);
        newmethods=methods;
        for(int j=0; j<64; j++){
            newmethods[i&j]=(newmethods[i&j]+(methods[j]*methodi)%mod)%mod;
        }
        newmethods[i]=(methods[i]+methodi)%mod;
        methods=newmethods;

    }
    int count=0;
    for(int i=0; i<64;i++){
        int c=0;
        for(int j=0; j<9; j++){
            if((i>>j)%2==1){
                c++;
            }
        }
        if(c==k){
            count=(count+methods[i])%mod;
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