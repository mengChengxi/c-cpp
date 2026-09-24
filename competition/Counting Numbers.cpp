#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

long long memo[25][10];
string s;

long long dfs(int pos, int state, bool is_limit, bool is_lead) {
    if (pos == s.length()) return 1; // 边界返回值 (通常是 1 或 !is_lead)

    if (!is_limit && !is_lead && memo[pos][state] != -1) {
        return memo[pos][state];
    }

    long long res = 0;
    int up = is_limit ? (s[pos] - '0') : 9;

    for (int i = 0; i <= up; ++i) {
        if (i==state&&is_lead==false) continue; // 非法条件剪枝

        if (is_lead) {
            if (i == 0) {
                res += dfs(pos + 1, 0, is_limit && (i == up), true);
            } else {
                res += dfs(pos + 1, i, is_limit && (i == up), false);
            }
        } else {
            res += dfs(pos + 1, i, is_limit && (i == up), false);
        }
    }

    if (!is_limit && !is_lead) {
        memo[pos][state] = res;
    }

    return res;
}

long long count_valid(long long x) {
    if (x < 0) return 0;
    s = to_string(x);
    memset(memo, -1, sizeof(memo));
    return dfs(0, 0, true, true);
}

void solve() {
    long long a,b;
    cin>>a>>b;
    long long res=count_valid(b)-count_valid(a-1);
    cout<<res<<endl;


}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

   
        solve();
    
    return 0;
}