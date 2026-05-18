#include <bits/stdc++.h>
#include <climits>
#include <string>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

int maxd=-1;
int mind=100;
// 修改点 1：将 best 和 inttarget 改为 unsigned long long 防止溢出
unsigned long long best=ULLONG_MAX;
unsigned long long inttarget=0;

void allmax(string c, int need){
    for(int i=0; i<need; i++){
        c+=(char)('0'+maxd);
    }
    if (c.empty()) return; // 安全检查
    
    // 修改点 2：使用 stoull 转换
    unsigned long long val = stoull(c);
    // 修改点 3：无符号整数相减需要判断大小，不能直接用 abs()
    unsigned long long diff = (val > inttarget) ? (val - inttarget) : (inttarget - val);
    best=min(best, diff);
}

void allmin(string c, int need){
    for(int i=0; i<need; i++){
        c+=(char)('0'+mind);
    }
    if (c.empty()) return; // 安全检查
    
    unsigned long long val = stoull(c);
    unsigned long long diff = (val > inttarget) ? (val - inttarget) : (inttarget - val);
    best=min(best, diff);
}

void solve() {
    string target;
    cin>>target;
    // 使用 stoull 转换
    inttarget=stoull(target);

    int n;
    cin>>n;
    int digits[]={0,0,0,0,0,0,0,0,0,0};
    for(int i=0; i<n; i++){
        int d;
        cin>>d;
        digits[d]=1;
    }
    maxd=-1;
    mind=100;
    for(int i=0; i<10; i++){
        if(digits[i]==1){
            maxd=max(maxd,i);
            mind=min(mind,i);
        }
    }
    
    // 重置 best
    best=ULLONG_MAX;

    // 处理长度更长的情况（生成 target.size() + 1 位）
if (mind == 0) {
        // 寻找最小的非零数字 (mind_nz)
        int mind_nz = -1;
        for (int i = 1; i < 10; i++) {
            if (digits[i] == 1) {
                mind_nz = i;
                break;
            }
        }
        if (mind_nz != -1) {
            // 以最小非零数字开头，后续全部补0
            allmin(string(1, '0' + mind_nz), target.size());
        }
    } else {
        // 如果没有0，正常用最小数字开头并补齐
        allmin(string(1, '0' + mind), target.size());
    }
    string fit="";
    for(int i=1; i<=target.size(); i++){
        int m=100;
        int n=-1;
        int newfit=-1;
        for(int j=0; j<10; j++){
            if(digits[j]==1&& j>target[i-1]-'0' ){
                m=min(m,j);
            }
            if(digits[j]==1&& j<target[i-1]-'0' ){
                n=max(n,j);
            }
            
            if(digits[j]==1&& j==target[i-1]-'0' ){
                newfit=j;
            }
        }
        
        if(m!=100){
            allmin(fit+char(m+'0'),target.size()-i);
        }
        if(n!=-1){
            allmax(fit+char(n+'0'),target.size()-i);
        }
        if(fit==""&&n==-1&&target.size()-i>0 ){
            allmax("",target.size()-i);
        }
        if(newfit!=-1){
            fit+=char(newfit+'0');
        }else{
            break;
        }
    }
    
    if(fit==target){
        cout<<0<<'\n';
    }else{
        cout<<best<<'\n';
    }
}

int main() {
    // 关闭同步流以提高 cin/cout 性能
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int dashabi;
    cin >> dashabi;
    while (dashabi--) {
        solve();
    }
    return 0;
}