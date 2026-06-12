#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

vector<long long> x;
vector<long long> y;
vector<long long> r;

vector<vector<int>> g;
vector<int> isvisted;

long long dfs(int n,int prev){
    //self:1-prev
    isvisted[n]=1-prev;

    long long sum=0;
    if(prev==1){
        sum=-1;
    }else{
        sum=1;
    }
    for(int i=0; i<g[n].size(); i++){
        if(isvisted[g[n][i]]!=1-prev){

            if(isvisted[g[n][i]]==-1){
                isvisted[g[n][i]]=prev;
                long long res=dfs(g[n][i],1-prev);
                if(res==-INF||sum==-INF){
                    sum=-INF;
                    
                }else{
                    sum+=res;
                }
                

            }
            //good;

        }else{
            sum= -INF;
        }
    }
    return sum;

}

void solve() {
    int n;
    cin>>n;
    vector<long long> tx(n);
    vector<long long> ty(n);
    vector<long long> tr(n);

    x=tx;
    y=ty;
    r=tr;

    for(int i=0; i<n; i++){
        cin>>x[i];
        cin>>y[i];
        cin>>r[i];
    }

    vector<vector<int>> tg(n);
    vector<int> tisvisted(n,-1);
    g=tg;
    isvisted=tisvisted;
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])==(r[i]+r[j])*(r[i]+r[j])){
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }

    for(int i=0; i<n; i++){
        if(isvisted[i]==-1){
            long long res=dfs(i,1);
            if(res!=-INF&&res!=0){
                cout<<"YES"<<endl;
                return;
            }
        }
    }

    cout<<"NO"<<endl;

    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
  
        solve();
    
    return 0;
}