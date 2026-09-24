#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n,k;

    cin>>n>>k;
    vector<int> nums(n);

    for(int i=0; i<n; i++){
        cin>>nums[i];
    }

    vector<int> blocks;
    
    int block=1;
    for(int i=1; i<n; i++){
        if(nums[i]!=nums[i-1]){
            blocks.push_back(block);
            block=1;
        }else{
            block++;
        }
    }
    blocks.push_back(block);

    sort(blocks.begin(),blocks.end());

    deque<int> dq;
    for(int i=0; i<blocks.size(); i++){
        dq.push_back(blocks[i]);
    }

    int count=0;
    int changed=1;
    while(dq.size()>0){
        if(k-n>=0&&changed==1){
            if((k-n)%dq.size()==0){
                count++;
                changed=0;
            }
        }

        for(int i=0; i<dq.size(); i++){
            dq[i]--;
            n--;
        }
        while(dq.size()>0&&dq[0]==0){
            
                dq.pop_front();
                changed=1;
            
        }
            
    

    }

    cout<<count<<endl;
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