#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;


#define mkp make_pair
int i;


    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t ran(uint64_t x)  {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }



void solve() {
    for(int  j=0;j<100; j++){
        i++;
        long long r=ran(i);
        if(r%10%2==0){
            cout<<'F'<<endl;
        }else{
            cout<<'T'<<endl;
        }
        char corect;
        cin>>corect;
        if(corect=='T'){
            cout<<'F'<<endl;
        }else{
            cout<<'T'<<endl;
        }
        cin>>corect;


        
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