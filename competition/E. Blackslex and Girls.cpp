#include <bits/stdc++.h>
#include <iostream>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n,x,y;
    cin>>n>>x>>y;

    string result;
    cin>>result;


    vector<int> p(n);
    for(int i=0; i<n; i++){
        cin>>p[i];
    }

    bool one=false;
    bool zero=false;

    for(int i=0; i<n; i++){
        if(result[i]=='0'){
            if(p[i]%2==0){
                x-=(p[i]/2+1);
                y-=(p[i]/2-1);
            }else{
                x-=(p[i]/2+1);
                y-=(p[i]/2);
            }
            zero=true;
        }else{
            if(p[i]%2==0){
                y-=(p[i]/2+1);
                x-=(p[i]/2-1);
            }else{
                y-=(p[i]/2+1);
                x-=(p[i]/2);
            }
            one=true;

        }
        if(x<0||y<0){
            cout<<"NO"<<endl;
            return;;
        }
    }


    
    
    if(x==y){

    }else if(x>y){
        if(zero==true){

        }else{
            cout<<"NO"<<endl;
            return;
        }
    }else{
        if(one==true){

        }else{
            cout<<"NO"<<endl;
            return;
        }

    }

    cout<<"YES"<<endl;
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