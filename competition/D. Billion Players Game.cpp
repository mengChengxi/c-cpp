#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n,l,r;
    cin>>n>>l>>r;
    long long maxscore=0;
    int left=0;
    int right=0;
    deque<int> middle;
    for(int i=0; i<n; i++){
        int t;
        cin>>t;
        if(t<=l){
            left++;
            maxscore+=(l-t);
            continue;
        }
        if(t>=r){
            right++;
            maxscore+=(t-r);

            continue;
        }
        middle.push_back(t);
    }


    sort(middle.begin(), middle.end());

    while(1){
        int sl=-1;
        int rl=-1;
        if(left>0){
            left--;
            sl=l;
        }else{
            if(middle.size()>0){
                sl=middle[0];
                middle.pop_front();
            }
        }
        if(right>0){
            right--;
            rl=r;
        }else{
            if(middle.size()>0){
                rl=middle[middle.size()-1];
                middle.pop_back();
            }
        }

        if(sl!=-1&&rl!=-1){
            maxscore+=(rl-sl);
        }else{
            break;
        }
    }
    cout<<maxscore<<endl;

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