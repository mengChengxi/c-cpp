#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    string s;
    cin>>s;
    //ioioi

    int n=0;
    int count=0;
    
    for(int i=0; i<s.size(); i++){
        if(n%2==0){
            if(s[i]=='i'){
                
            }else{
                count++;
                i--;
            }
        }else{
            if(s[i]=='o'){
                
            }else{
                count++;
                i--;
            }

        }
        n++;

    }
    if(((count+s.size())%2)==0){
        cout<<count<<endl;
    }else{
        cout<<count+1<<endl;
    }
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int dashabi;

    
        solve();
    
    return 0;
}