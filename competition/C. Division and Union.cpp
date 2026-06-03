#include <bits/stdc++.h>
#include <utility>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;
    cin>>n;


    vector<int> line(20,0);
    vector<pair<int, int>> segs(n);

    for(int i=0; i<n; i++){
        cin>>segs[i].first;cin>>segs[i].second;
    }
    for(int i=0; i<n; i++){
        line[segs[i].first]++;
        line[segs[i].second+1]--;
    }

    vector<int> sumline(20,0);
    //200005
    sumline[0]=line[0];
    for(int i=1; i<sumline.size(); i++){
        sumline[i]=sumline[i-1]+line[i];
    }

    int sep=-1;
    for(int i=1; i<sumline.size(); i++){
        if(sumline[i]!=0){
            sep=-2;
        }
        if( sumline[i]==0&&sep==-2){
            sep=i;
            break;
        }


    }
    vector<int> out(n);
    int s=0;
    for(int i=0; i<n; i++){
        if(segs[i].second<sep){
            out[i]=1;
            
        }else{
            out[i]=2;
            s=1;
        }
    }
    if(s==0){
        cout<<"-1"<<endl;
    }else{
        for(int i=0; i<n; i++){
            cout<<out[i]<<" ";
        }
        cout<<endl;
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