#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

// <4 dif:2  -1+2*(2+1) (1-2-3),  3  answer 6.
// <8 dif:6  -1+ 6*(4+1) (3-4-5-6-7),  7
//  

void solve() {
    int n,m;
    cin>>n>>m;
    int tn=n;
    int times=0;
    while(tn>0){
        tn=tn>>1;
        times++;
    }

    if(n==1){
        cout<<1%m<<endl;
        return;
    }
    times-=2;// interate times.
    // n-2^(times+1)+1  how many more need

    int need=2;
    need=need<<times;
    need=n-need+1;

    
    long long dif=2;

    for(int i=0; i<times; i++){\
        /// -1+(2^(i+1)+1)*div
        dif=(((1<<(i+1))+1)*dif)%m;
    }


    long long res=(m-1+dif*(need+1))%m;

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