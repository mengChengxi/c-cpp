#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    string s;
    cin>>s;
    int twos=0;
    int onethrees=0;
    vector<int> end2(s.size()+1);
    end2[end2.size()-1]=twos;
    for(int i=s.size()-1; i>=0; i--){
        if(s[i]=='2'){
            twos++;
        }
        end2[i]=twos;
    }


    vector<int> start13(s.size()+1);
    start13[0]=0;
    for(int i=0; i<s.size(); i++){
        if(s[i]=='1'||s[i]=='3'){
            onethrees++;
        }
        start13[i+1]=onethrees;
    }
    int minn=INF;
    for(int i=0; i<start13.size(); i++){
        minn=min(minn,start13[i]+end2[i]);
    }

    for(int i=0; i<s.size(); i++){
        if(s[i]=='4'){
            minn++;
        }
    }

    cout<<minn<<endl;
    

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