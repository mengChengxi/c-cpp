#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;
    cin>>n;
    vector<int  > nums(n);
    for(int i=0; i<n; i++)
    {
        cin>>nums[i];
    }

    int maxi=0;

    for(int i=0; i<n; i++){
        if(nums[i]==n){
            maxi=i;
            break;
        }
    }

    int left=maxi;
    int right=maxi;
    int current=n;
    for(int i=0; i<n-1; i++){
        current--;
        if(left>0){
            if(nums[left-1]==current){
                left--;
                continue;
            }
        }
        if(right<n){
            if(nums[right+1]==current){
                right++;
                continue;
            }
        }
        

        cout<<"NO"<<endl;
        return;
    }
    cout<<"YES"<<endl;



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