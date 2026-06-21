#include <algorithm>
#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int q,m;
    cin>>q>>m;

    vector<int> piazzs(q);
    for(int i=0; i<q; i++){
        cin>>piazzs[i];
    }

    vector<int> divs;


    for(int i=1; i<(int)sqrt(m)+1; i++){
        if(m%i==0){
            divs.push_back(i);
            divs.push_back(m/i);
        }
    }

    sort(divs.begin(),divs.end());

    for(int i=0; i<piazzs.size(); i++){
        int count=0;
        for(int j=divs.size()-1; j>=0; j--){
            count+=piazzs[i]/divs[j];
            piazzs[i]=piazzs[i]%divs[j];
            if(piazzs[i]==0){
                break;
            }
        }

        cout<<count<<" ";
    }
    cout<<'\n';


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