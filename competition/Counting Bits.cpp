#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    long long n;
    cin>>n;

    n++;

    long long count=0;

    for(int i=0; i<62; i++){
        long long period=2l<<i;

        count+=(n/period)*period/2;

        if((n%period)-(period/2)>0){
            count+=((n%period)-(period/2));
        }

        if(n<period/2){
            break;
        }


    }

    cout<<count<<endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
   
        solve();
    
    return 0;
}