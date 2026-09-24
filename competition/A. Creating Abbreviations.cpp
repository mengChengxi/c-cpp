#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n,m ; 
    cin>>n>>m;

    vector<int> bag(26,0);

    for(int i=0;i<n;  i++){
        string s;
        cin>>s;

        bag[s[0]-'a']=1;
    }
    int no=0;
    for(int i=0;i<m;  i++){
        string s;
        cin>>s;

        for(int i =0; i<s.size(); i++){
            if(bag[s[i]-'A']==1){

            }else{
                 no=1;
                
            }
        }
    }

    if(no==0){
        cout<<"YES"<<endl;
    }else{
        cout<<"NO"<<endl;
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