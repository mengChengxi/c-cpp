#include <bits/stdc++.h>
#include <unordered_map>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n,m,l;
    cin>>n>>m>>l;
    vector<int> actions(n);
    unordered_map<int, int> mp;
    mp.reserve(2*n); // 预分配空间防止多次 rehash
    // mp[key] = val;      // 插入或修改
    // mp.count(key);      // 检查是否存在 (1 or 0)
    // mp.erase(key);      // 删除
    // for (auto const& [k, v] : mp) {  }
    for(int i=0; i<n; i++){
        int tt;
        cin>>tt;
        actions[i]=tt;
        mp[tt]=0;
    }
    m=min(m,n+1);

    vector<int> enemy(m+2,0);
    int target=min(m,n+1);
    for(int i=1; i<=l ; i++){
        int minn=INF;
        int mini=-1;
        //cout<<i<<":"<<endl;
        for(int j=0; j<target; j++){
            if(enemy[j]<minn){
                minn=enemy[j];
                mini=j;
            }
            ///cout<<enemy[j]<<" ";

        }
        //cout<<endl;
        enemy[mini]++;
        if(mp.count(i)==1){
            if(n<enemy.size()&&enemy[n-1]!=0){
                enemy[n-1]=enemy[n];
                enemy[n]=0;
            }
            else{
                enemy[0]=0;
            }
            
            
            n--;
            target=min(m,n+1);
            //cout<<"kill"<<" ";
        }


    }
    cout<<enemy[0]<<endl;

    
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