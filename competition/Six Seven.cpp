#include <bits/stdc++.h>
#include <iostream>
#include <iterator>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    string s;
    cin>>s;
    int i=0;
    bool jinwei=false;
    bool increse=false;

    for(i=0; i<s.size()-1; i++){
        if(s[i]<s[i+1]){
            if(s[i+1]-s[i]==1){

            }else{
            increse=true;
                break;
            }
        }else{
            
            break;
        }
    }
    
    if(increse==true){
        if(s[0]=='9'){
            jinwei=true;
        }else{
            s[0]+=1;
        }
    }
    if(increse==true){
        for(i=0; i<s.size()-1; i++){
            if(s[i]<=s[i+1]){
                if(s[i+1]-s[i]==1){

                }else{
                    increse=true;
                    break;
                }
            }else{
                
                break;
            }
        }
    }
    
    if(jinwei!=true){
        for(; i<s.size()-1; i++){
            s[i+1]=s[i]+1;
            if(s[i+1]>'9'){
                jinwei=true;
            }
        }
    }

    if(jinwei==true){
        for(int i=0; i<s.size()+1; i++){
            cout<<(i+1);
        }
        cout<<endl;
    }else{
        cout<<s<<endl;
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