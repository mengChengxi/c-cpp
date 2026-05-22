#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    string s;
    cin>>s;
    int sum=0;
    int twos=0;
    int threes=0;
    for(int i=0; i<s.size(); i++){
        sum+=(s[i]-'0');
        if(s[i]=='2'){
            twos++;
        }
        if(s[i]=='3'){
            threes++;
        }
    }

    if(sum%9==0){
        cout<<"YES"<<endl;
        return;
    }
    if(twos>=2){
        twos=twos+threes*3;
        if((sum%9)%2==1){
            if((9-sum%9)/2<=twos){
                cout<<"YES"<<endl;
                return;
            }

        }else{
            if((18-sum%9)/2<=twos){
                cout<<"YES"<<endl;
                return;
            }
        }
    }else if(twos==1){
        for(int i=0; i<=threes; i++){
            if((sum+i*6)%9==0){
                cout<<"YES"<<endl;
                return;
            }
            if((sum+i*6+2)%9==0){
                cout<<"YES"<<endl;
                return;
            }
        }
        cout<<"NO"<<endl;
        return;
    }else if(twos==0){
        for(int i=0; i<=threes; i++){
            if((sum+i*6)%9==0){
                cout<<"YES"<<endl;
                return;
            }
        }
        cout<<"NO"<<endl;
        return;

    }
    cout<<"NO"<<endl;
    
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