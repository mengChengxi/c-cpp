#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

int plusdivide(int n){
    if(n==1){
        return 0;
    }
    return 1+plusdivide( (n+1)/2);
}

int divide(int n){
    if(n==1){
        return 0;
    }
    return 1+plusdivide(n/2);
}


void solve() {
    int n,q;
    cin>>n>>q;
    vector<int> nums(n);
    for(int i=0; i<n; i++){
        cin>>nums[i];
    }

    vector<int> pd(n);
    vector<int> d(n);

    for(int i=0; i<n; i++){
        pd[i]=plusdivide(nums[i]);
        
    }
    for(int i=0; i<n; i++){
        
        d[i]=pd[i]-divide(nums[i]);
    }


    vector<long long> prepd(n+1);
    vector<long long> pred(n+1);

    long long sum=0;
    for(int i=0; i<n+1; i++){
        prepd[i]=sum;
        sum+=pd[i];
    }
    sum=0;
    for(int i=0; i<n+1; i++){
        pred[i]=sum;
        sum+=d[i];
    }

    while(q--){
        int s, e;
        cin >> s >> e;
        
        // 区间内的最大潜能总和
        long long total_pd = prepd[e] - prepd[s-1]; 
        
        // 区间内的“弱点”数量 C
        long long C = pred[e] - pred[s-1]; 
        
        // Poby 能成功砍废 ceil(C/2) 个弱点
        long long ans = total_pd - (C + 1) / 2; 
        
        cout << ans << "\n";
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