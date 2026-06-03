#include <bits/stdc++.h>
#include <initializer_list>
#include <unordered_map>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;
    cin>>n;
    vector<int> nums(n);
    for(int i=0; i<n; i++){
        cin>>nums[i];
    }
    
    vector<int> map(n+1,0);
    for(int i=0; i<n; i++){
        map[nums[i]]+=1;
    }

    int longest=0;
    for(int i=0; i<map.size(); i++){
        int c;
        for(int j=0; j<map.size(); j++){
            
            if(map[j]>=map[i]){
                c++;
            }
             
        }
        longest=max(longest,c*map[i]);
    }
    
    
    

    cout<<longest<<endl;
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