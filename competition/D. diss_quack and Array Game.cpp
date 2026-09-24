#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

long long times(int n){
    long long times=0;
    while(n!=0){
        times++;
        if(n%2==0){
            n/=2;
        }else{
            n--;
        }
    }
    return times;


}

void solve() {
    long long n;
    cin>>n;

    vector<int> nums(n);
    for(int i=0; i<n; i++){
        cin>>nums[i];
    }

    long long total=0;
    vector<long long> ot(n);
    for(int i=0; i<n; i++){
        ot[i]=times(nums[i]);
        total+=ot[i];

    }

    long long maxsave=0;

    for(long long k=20; k>=0; k--){
        long long save=k*(n-1);

        
        for(int j=0; j<n; j++){
            long long maxtempsave=-1e18; 
    
            
            if(nums[j]%(1ll<<k)==0){
                maxtempsave=0;
            }
            for(int i=k;i<=20;i++){
                long long tempsave=0;
                if((nums[j]%(1l<<i))!=0){
                    tempsave-=((1l<<i)-(nums[j]%(1l<<i)));
                    tempsave+=(ot[j]-times(((nums[j]/(1l<<i))+1l)*(1l<<i)));
                }
                maxtempsave=max(maxtempsave,tempsave);
            }
            save+=maxtempsave;
           
        }

        maxsave=max(maxsave,save);

    }

    cout<<total-maxsave<<endl;


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