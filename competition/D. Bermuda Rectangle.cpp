#include <bits/stdc++.h>
using namespace std;
const int INF=0x3f3f3f3f;
const int mod=1e9+7;
#define mkp make_pair

void solve(){
    long long s;
    int q;
    cin>>s>>q;

    vector<long long> len;
    len.push_back(0);
    for(long long i=1; i*i<=s; i++){
        if(s%i==0){
            len.push_back(i);

            if(i*i!=s){
                len.push_back(s/i);
            }


        }
    }
    
    sort(len.begin(),len.end());

    vector<long long> prelen(len.size());
    prelen[0]=0;

    for(int i=1; i<len.size(); i++){
        prelen[i]=prelen[i-1] + (len[i]-len[i-1])* (s/len[i]);
    }

    while(q--){
        long long w,l;
        cin>>w>>l;
        
        w=min(w,s);
        l=min(l,s);

        long long res=0;
        
        auto it=upper_bound(len.begin(),len.end(),s/l);

        int index=distance(len.begin(),it);
        index--;

        if(w<=len[index]){
            res=w*l;
        }else{

            auto it2=lower_bound(len.begin(),len.end(),w);
            int k=distance(len.begin(),it2);

            res=len[index]*l+prelen[k-1]-prelen[index]+(w-len[k-1])*(s/len[k]);
        }

        cout<<res<<endl;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int dashabi;
    cin>>dashabi;
    while(dashabi--){
        solve();
    }
    return 0;
}