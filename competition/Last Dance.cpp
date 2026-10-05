#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n,q,g;
    cin>>n>>q>>g;

    unordered_map<int, int> songs;
    unordered_map<int, int> people;

    for(int i=0; i<q; i++){
        char type;
        cin>>type;
        if(type=='P'){
            int s,a;
            cin>>s>>a;

            for(int i=0 ; i<a; i++){
                int c;
                cin>>c;

                if(people.count(c)!=0){
                    songs[people[c]]--;
                }
                people[c]=s;
                songs[s]++;
            }
        }else{
            int a;
            cin>>a;
            
            cout<<songs[a]<<endl;
        }
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