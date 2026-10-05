#include <bits/stdc++.h>
#include <iomanip>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n,m;
    cin>>n>>m;
    vector<long long> nums(n);

    for(int i=0; i<n; i++){
        cin>>nums[i];
    }

    sort(nums.begin(),nums.end());

    //(av-x)^2=  m*av^2+sigma(x^2)-2*av*sigma(x)

    long long sumxx=0;
    long long sumx=0;
    
    for(int i=0; i<m; i++){
        sumxx+=(nums[i]*nums[i]);
        sumx+=nums[i];
    }
    double avg=(double)sumx/(double)m;

    double minsd=m*avg*avg+sumxx-2*avg*sumx;
    
    int toremove=0;
    for(int i=m; i<n; i++){
        sumxx-=(nums[toremove]*nums[toremove]);
        sumx-=nums[toremove];
        sumxx+=(nums[i]*nums[i]);
        sumx+=nums[i];
        toremove++;
        avg=(double)sumx/(double)m;
        minsd=min(minsd,m*avg*avg+sumxx-2*avg*sumx);
    }

    cout<<fixed<<setprecision(6)<<minsd<<endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
   
        solve();
    
    return 0;
}