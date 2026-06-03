#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

long long memo[1005][12][12];
string s;

long long dfs(int pos, int prev1,int prev2, bool is_limit, bool is_lead) {
    if (pos == s.length()) {
        if(prev1==11){
            return 1;
        }else{
            return 0;
        }

        
    } // 边界返回值 (通常是 1 或 !is_lead)

    if (!is_limit && !is_lead && memo[pos][prev1][prev2] != -1) {
        return memo[pos][prev1][prev2];
    }

    long long res = 0;
    int up = is_limit ? (s[pos] - '0') : 9;

    for (int i = 0; i <= up; ++i) {
        // if (invalid_condition) continue; // 非法条件剪枝

        if (is_lead) {
            if (i == 0) {
                res =(res+ dfs(pos + 1, 10,10, is_limit && (i == up), true))%mod;
            } else {
                res = (res+ dfs(pos + 1, i,10, is_limit && (i == up), false))%mod;
            }
        } else {
            if(prev1==11){
                res =(res+ dfs(pos + 1, 11,11, is_limit && (i == up), false))%mod;
            }else if(i==prev1||i==prev2){
                res =(res+ dfs(pos + 1, 11,11, is_limit && (i == up), false))%mod;
            }else{
                res =(res+ dfs(pos + 1, i,prev1, is_limit && (i == up), false))%mod;
            }
            
        }
    }
    res%=mod;

    if (!is_limit && !is_lead) {
        memo[pos][prev1][prev2] = res;
    }

    return res;
}

long long count_valid(string x) {
    
    s = x;
    memset(memo, -1, sizeof(memo));
    return dfs(0, 10,10, true, true);
}

void solve() {
    string l;
    string r;
    cin>>l>>r;
    long long res=(count_valid(r)-count_valid(l)+mod)%mod;
    for(int i=0; i<l.size(); i++){
        if(i-1>=0&&l[i]==l[i-1]){
            res+=1;
            break;
        }
        if(i-2>=0&&l[i]==l[i-2]){
            res+=1;
            break;
        }

    }
    cout<<res%mod<<endl;
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
        solve();
    
    return 0;
}