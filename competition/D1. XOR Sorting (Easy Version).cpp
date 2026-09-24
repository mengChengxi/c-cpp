#include <bits/stdc++.h>
#include <utility>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n,q;
    cin>>n>>q;

    vector<int> nums(n);
    for(int i=0; i<n; i++){
        cin>>nums[i];
    }

    vector<int> snums=nums;
    sort(snums.begin(),snums.end());


    vector<pair<int, int>> trie;
    trie.push_back({-1,-1});
    for(int i=0; i<n; i++){
        if(nums[i]!=snums[i]){
            int current=0;
            for(int j=22; j>=0; j++){
                int next=(i>>j)%2;
                if(next==1){
                    if(trie.size()-1<trie[current].first){
                        trie[current].first=trie.size();
                        trie.push_back({-1,-1});
                    }else{
                        current=trie[current].first;
                    }
                }else{
                    if(trie.size()-1<trie[current].second){
                        trie[current].second=trie.size();
                        trie.push_back({-1,-1});
                    }else{
                        current=trie[current].second;
                    }
                }
            }
        }
    }
    for(int i=0; i<n; i++){
        if(nums[i]!=snums[i]){
            int current=0;
            int maxv=0;
            for(int j=22; j>=0; j++){
                if((i>>j)%2==1){
                    if(trie[current].second!=-1){
                        current=trie[current].second;
                        maxv+=(1<<j);
                    }else{
                        current=trie[current].first;
                    }
                }else{
                    if(trie[current].first!=-1){
                        current=trie[current].first;
                        maxv+=(1<<j);
                    }else{
                        current=trie[current].second;
                    }
                    
                }
            }
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