#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair


struct PairHash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const {
        // 使用 XOR 组合哈希值（简单但容易冲突，工程中建议使用更高级的组合方法）
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 << 1); // 左移一位可以减少对称冲突
    }
};




void solve() {
    int n;
    int m1;
    int m2;

    cin>>n>>m1>>m2;



    unordered_map<std::pair<int, int>, std::string, PairHash> mp;
    mp.reserve(m1+m2);
    
    for(int i=0; i<m1; i++){
        int s,t;
        cin>>s>>t;
        if(s>t){
            mp[{s,t}]=1;
        }else{
            mp[{t,s}]=1;
        }
        
        
    }
    int common=0;
    for(int i=0; i<m2; i++){
        int s,t;
        cin>>s>>t;

        if(s>t){
            if(mp.count({s,t})==1){
                common++;
            }
        }else{
            if(mp.count({t,s})==1){
                common++;
            }
        } 


    }

    cout<<m1+m2-common-common<<endl;






    
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