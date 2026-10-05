#include <bits/stdc++.h>
#include <cmath>
#include <cstdint>
#include <utility>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n,m,s,p,q;

    cin>>n>>m>>s>>p>>q;
    int pagesnumber=ceil(n/(double)m);
    vector<pair<set<int>,set<int>>> page(pagesnumber+1,pair<set<int>,set<int>>());
    int minp=INF;
    int maxp=-1;

    

    for(int i=0; i<p; i++){
        //presleceted;
        int t;
        cin>>t;
        page[(t-1)/m+1].first.insert(t);
        minp=min(minp,(t-1)/m+1);
        maxp=max(maxp,(t-1)/m+1);
    }
    
    for(int i=0; i<q; i++){
        //desire;

        int t;
        cin>>t;
        minp=min(minp,(t-1)/m+1);
        maxp=max(maxp,(t-1)/m+1);
        page[(t-1)/m+1].second.insert(t);
    }
    if(p==0&&q==0){
        cout<<0<<endl;
        return;
    }
    int op=0;
    if(s<minp){
        op+=maxp-s;
    }
    if(s>maxp){
        op+=s-minp;
    }
    if(s>=minp&&s<=maxp){
        op+=maxp-minp;
        if(s-minp>maxp-s){
            op+=maxp-s;
        }else{
            op+=s-minp;
        }
    }

    
    // mp.count(key);      // 检查是否存在 (1 or 0)
    // mp.erase(key);      // 删除
    // for (auto const& [k, v] : mp) {  }

    for(int i=minp; i<=maxp; i++){
        int cadidop=INF;
        int dup=0;
        for (auto const& v : page[i].second) { 
            if(page[i].first.count(v)==1){
                dup++;
            }
        }
        cadidop=min((int)cadidop,(int)(page[i].first.size()+page[i].second.size()-2*dup));

        cadidop=min((int)cadidop,(int)(1+page[i].second.size()));
        cadidop=min((int)cadidop,(int)(1+m-page[i].second.size()));

        op+=cadidop;
        
    }

    cout<<op<<endl;

    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

        solve();
    
    return 0;
}