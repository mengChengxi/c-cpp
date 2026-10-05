#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;
    cin>>n;

    int s1=0;
    int s2=0;
    int s3=0;
    int s4=0;


    for(int i=0; i<n; i++){
        int t;
        cin>>t;

        if(t>=1&&t<=10){
            s1=1;
        }else if(t>=11&&t<=20){
            s2=1;
        }else if(t>=21&&t<=30){
            s3=1;
        }else if(t>=31&&t<=40){
            s4=1;
        }
    }

    cout<<s1+s2+s3+s4<<endl;
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