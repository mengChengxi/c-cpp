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



int move(int from, int layers, int to){

    if(layers==1){
        cout<<layers<<' ' <<from<<' ' <<to<<endl;
        return 0;
    }
    int mid=6-from-to;
    move(from,layers-1,mid);
    cout<<layers<<' ' <<from<<' ' <<to<<endl;
    move(mid,layers-1,to);
    return 0;
}
void solve() {
    int n;
    cin>>n;
    vector<int> cakes(n);
    for(int i=0; i<n; i++){
        cin>>cakes[i];
    }

    int type=2;
    for(int i=0; i<n; i++){
        if(cakes[i]!=0){
            type=1;
            break;
        }
    }
    if(type==1){
        for(int i=0; i<n; i++){
            if(cakes[i]!=i){
                type=0;
                break;
            }
        }
    }
    if(type==0){
        cout<<"NO"<<endl;
    }else if(type==1){
        cout<<"YES"<<endl;
        cout<<n<<endl;

        for(int i=n; i>=1; i--){
            cout<<i<<' '<< 1<<' '<<3<<endl;
        }

    }else{
        cout<<"YES"<<endl;
        cout<<fastPower(2,n)-1<<endl;
        move(1,n,3);

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