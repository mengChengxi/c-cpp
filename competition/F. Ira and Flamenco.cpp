#include <algorithm>
#include <bits/stdc++.h>
#include <deque>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

long long fastPower(long long base, long long exp) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

long long modInverse(long long n) {
    return fastPower(n, mod - 2);
}

void solve() {
    int n,m;
    cin>>n>>m;
    vector<int> nums(n);
    for(int i=0; i<n; i++){
        cin>>nums[i];
    }

    if(m==1){
        cout<<n<<endl;
        return;
    }
    unordered_map<int, int> mp;
    mp.reserve(200005); // 预分配空间防止多次 rehash
    // mp[key] = val;      // 插入或修改
    // mp.count(key);      // 检查是否存在 (1 or 0)
    // mp.erase(key);      // 删除
    // for (auto const& [k, v] : mp) {  }
    for(int i=0; i<n; i++){
        if(mp.count(nums[i])==0){
            mp[nums[i]]=1;
        }else{
            mp[nums[i]]++;
        }
    }

    vector<int> newnums;
    for (auto const& [k, v] : mp) {
        newnums.push_back(k);
    }

    nums=newnums;
    sort(nums.begin(),nums.end());

    deque<int> mdancer;

    long long count=0;
    long long oldtc=-1;
    long long oldtcstart=-1;
    

    for(int i=0; i<nums.size(); i++){
        if(mdancer.size()==m){
            long long tc=1;
            if(oldtcstart==-1||oldtcstart!=i-m-1){
                
                for(int j=0; j<m; j++){
                    tc=(tc*mp[mdancer[j]])%mod;
                }
                count=(count+tc)%mod;
                mdancer.pop_front();
            }else{
                
                tc=((oldtc*modInverse(mp[nums[i-m-1]])%mod)*mp[mdancer[m-1]])%mod;
                count=(count+tc)%mod;
                mdancer.pop_front();
            }
            oldtc=tc;
            oldtcstart=i-m;
            
        }
        if(mdancer.size()<m){
            if(mdancer.size()==0){
                mdancer.push_back(nums[i]);
            }else if(mdancer[mdancer.size()-1]!=nums[i]){
                if(mdancer[mdancer.size()-1]+1==nums[i]){
                    mdancer.push_back(nums[i]);
                }else{
                    mdancer.clear();
                    mdancer.push_back(nums[i]);
                }
            }
        
        }
    }
    if(mdancer.size()==m){
        long long tc=1;
        for(int j=0; j<m; j++){
            tc=(tc*mp[mdancer[j]])%mod;
        }
        count=(count+tc)%mod;
        mdancer.pop_front();
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