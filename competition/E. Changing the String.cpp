#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n,q;
    cin>>n>>q;
    string s;
    cin>>s;

    string f=s;
    vector<int> bchars;
    vector<int> cchars;

    bchars.push_back(INF);
    cchars.push_back(INF);
    for(int i=n-1; i>=0; i--){
        if(s[i]=='b'){
            bchars.push_back(i);
        }
        if(s[i]=='c'){
            cchars.push_back(i);
        }
    }

    int btoc=0;
    int ctob=0;

    for(int i=0; i<q; i++){

        // string froms;
        // string tos;
        // cin>>froms;
        // cin>>tos;
        
        // char from=froms[0];
        // char to=tos[0];

        char from;
        char to;
        cin>>from>>to;
        

        if(from==to){
            continue;
        }
        if(from=='a'){
            continue;
        }

        if(from=='b'&&to=='c'){
            btoc++;
            continue;
        }
        if(from=='c'&&to=='b'){
            ctob++;
            continue;
        }
        if(cchars[cchars.size()-1]==INF&&bchars[bchars.size()-1]==INF){
            continue;
        }
        if(from=='c'){
            if(cchars[cchars.size()-1]<bchars[bchars.size()-1]){
                f[cchars[cchars.size()-1]]='a';
                cchars.pop_back();
            }else{
                if(btoc>0){
                    btoc--;
                    f[bchars[bchars.size()-1]]='a';
                    bchars.pop_back();
                }else if(cchars[cchars.size()-1]!=INF){
                    f[cchars[cchars.size()-1]]='a';
                    cchars.pop_back();
                }
            }
            continue;
        }

        if(from=='b'){
            if(bchars[bchars.size()-1]<cchars[cchars.size()-1]){
                f[bchars[bchars.size()-1]]='a';
                bchars.pop_back();
            }else{
                if(ctob>0){
                    ctob--;
                    f[cchars[cchars.size()-1]]='a';
                    cchars.pop_back();
                }else if(bchars[bchars.size()-1]!=INF){
                    f[bchars[bchars.size()-1]]='a';
                    bchars.pop_back();
                }
            }
            continue;
        }

    }

    for(int i=0; i<ctob; i++){
        if(cchars[cchars.size()-1]==INF){
            break;
        }
        f[cchars[cchars.size()-1]]='b';
        cchars.pop_back();
    }

    cout<<f<<endl;
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
