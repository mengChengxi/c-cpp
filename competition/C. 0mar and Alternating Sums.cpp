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

vector<long long> chooseodd(200005);
vector<long long> chooseeven(200005);

void solve() {
    int n;
    cin>>n;
    vector<int> nums(n);

    for(int i=0; i<n; i++){
        cin>>nums[i];
    }

    vector<pair<int, int>> bu;

    for(int i=0; i<n; i++){
        if(bu.size()==0){
            bu.push_back({1,nums[i]});
        }else{
            if(nums[i]==bu[bu.size()-1].second){
                bu[bu.size()-1].first++;
            }else{
                bu.push_back({1,nums[i]});
            }
        }
    }

    long long sum=0;

    long long count=1;
    for(int i=0; i<bu.size(); i++){
        count=count*chooseeven[bu[i].first]%mod;

    }
    sum=(sum+count)%mod;
    if(nums[0]==-1){
        long long inv=modInverse(chooseeven[bu[0].first]);
        count=(count*inv)%mod;
        for(int i=2; i<bu.size(); i++){
            if(bu[i].second-bu[i-1].second==1){
                sum=(sum+(((((count*chooseodd[bu[0].first])%mod*modInverse(chooseeven[bu[i].first]))%mod*modInverse(chooseeven[bu[i-1].first]))%mod*chooseodd[bu[i].first])%mod*chooseodd[bu[i-1].first])%mod)%mod;
            }
        }

    }

    cout<<sum<<endl;


}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    chooseeven[1]=1;
    chooseeven[2]=2;
    chooseodd[1]=1;
    chooseodd[2]=2;

    for(int i=3; i<200005; i++){
        long long even=(chooseeven[i-1]+chooseodd[i-1])%mod;
        long long odd=(chooseeven[i-1]+chooseodd[i-1])%mod;
        chooseeven[i]=even;
        chooseodd[i]=odd;
        
    }
    int dashabi;
    cin >> dashabi;
    while (dashabi--) {
        solve();
    }
    return 0;
}