#include <algorithm>
#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

vector<int> times(32);
vector<int> mult(32);

void solve() {
    int n,k;

    cin>>n>>k;

    vector<int> current(n);
    for(int i=0; i<n; i++){
        cin>>current[i];
    }

    sort(current.begin(),current.end());

    long long res=1;
    while (k>0) {
        vector<int> newcurrent;
        for(int i=0; i<current.size(); i++){
            if(k<=0){
                break;
            }
            int o=current[i];
            if(current[i]>=31)
            {
                current[i]=31;
            }

            if(times[current[i]]<=k){
                res=res*mult[current[i]]%mod;
                k-=times[current[i]];
            }else {
                k--;
                res=res*o%mod;
                for(int j=1; j<current[i]; j++){
                    newcurrent.push_back(j);
                }
                break;
            }
        }
        current=newcurrent;
    }

    cout<<res<<endl;
    


}

int main() {

    times[1]=1;
    mult[1]=1;
    long long prepro=1;
    for(int i=2; i<32; i++){
        times[i]=times[i-1]*2;
        mult[i]=i*prepro%mod;
        prepro=prepro*mult[i]%mod;
    }


    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int dashabi;
    cin >> dashabi;
    while (dashabi--) {
        solve();
    }
    return 0;
}