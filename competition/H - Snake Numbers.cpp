#include <bits/stdc++.h>
#include <string>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

string s;
long long memo[20][15];

long long dfs(int pos, int leadingnum, bool is_limit, bool is_lead) {
    if (pos == s.length()) return 1;

    if (!is_limit && !is_lead && memo[pos][leadingnum] != -1) {
        return memo[pos][leadingnum];
    }

    long long res = 0;
    int up = min((is_limit ? (s[pos] - '0') : 9),leadingnum-1 );

    for (int i = 0; i <= up; ++i) {

        if(is_lead){
            if(i==0){
                res+=dfs(pos+1,10,false,true);
            }else{
                res+=dfs(pos+1,i,is_limit&&i==s[pos]-'0',false);
            }
        }else{
            res+=dfs(pos+1,leadingnum,is_limit&&i==s[pos]-'0',false);
        }
    }

    if (!is_limit && !is_lead) {
        memo[pos][leadingnum] = res;
    }

    return res;
}

long long snakenumber(string n){

    s=n;
    memset(memo,-1,sizeof(memo));
    return dfs(0,10,true,true)-9;

}


void solve() {
    long long n,m;
    cin>>n>>m;
    n--;
    string sn=to_string(n);
    string sm=to_string(m);

    cout<<snakenumber(sm)-snakenumber(sn)<<endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int dashabi;
   
        solve();
    
    return 0;
}