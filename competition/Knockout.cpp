#include <bits/stdc++.h>
#include <iomanip>
#include <ios>
#include <string>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

#define bit(S, i) (((S) >> (i)) & 1)        // 获取 S 的第 i 位是否为 1
#define set_bit(S, i) ((S) | (1 << (i)))    // 将 S 的第 i 位置为 1
#define clear_bit(S, i) ((S) & ~(1 << (i))) // 将 S 的第 i 位置为 0
#define toggle_bit(S, i) ((S) ^ (1 << (i))) // 翻转 S 的第 i 位
#define lowbit(x) ((x) & -(x))              // 取出最低位的 1（树状数组同款）

// __builtin_popcount(S)：返回 S 在二进制下 1 的个数。如果 S 是 long long，使用 __builtin_popcountll(S)。
// __builtin_ctz(S)：返回 S 二进制末尾 0 的个数（即最低位的 1 在第几位，可以直接当做数组下标使用）。

// 枚举状态 S 的所有非空子集 sub

int res[]={-1,-1,1,2,3,4,5,6,5,4,3,2,1};

int mode=0;//min  
// 1  max
vector<double> meme(2048,-1);

int getsum(int s){
    int csum=0;
    int digit=1;
    for(int i=9; i>=0; i--){

        if((s&(1<<i))!=0){
            csum+=(i+1)*digit;
            digit*=10;
        }
        
    }

    return csum;

}

double expcon(int s){
    if(meme[s]!=-1){
        return  meme[s];
    }
    int cur=getsum(s);
    vector<double> extreme(13,cur);
    for (int sub = s; sub; sub = (sub - 1) & s) {
        // sub 就是 S 的合法子集
        int remain = s ^ sub; // remain 是 S 中去除 sub 后的剩余集合
        int sum=0;
        for(int i=0; i<10; i++){
            if((sub&(1<<i))!=0){
                sum+=(i+1);
            }
        }
        if(sum>=2&&sum<=12){
            if(extreme[sum]==cur){
                extreme[sum]=(1-mode)*INF;
            }
            if(mode==1){
                extreme[sum]=max(extreme[sum],expcon(remain));
            }else{
                extreme[sum]=min(extreme[sum],expcon(remain));
            }
        }
    }
    double e=0;

    for(int i=2; i<=12; i++){
        e+=res[i]/(double)36*extreme[i];
    }


    return meme[s]=e;
}


void solve() {
    string st;
    cin>>st;
    int s=0;
    for(int i=0; i<st.size(); i++){
        s+=(1<<(st[i]-'0'-1));
    }


    vector<double> tmeme(2048,-1);
    meme=tmeme;

    int r1,r2;
    cin>>r1>>r2;

    bool in=false;
    mode=0;
    double mins=getsum(s);
    int minremove=-1;
    for (int sub = s; sub; sub = (sub - 1) & s) {
        // sub 就是 S 的合法子集
        int remain = s ^ sub; // remain 是 S 中去除 sub 后的剩余集合
        int sum=0;
        for(int i=0; i<10; i++){
            if((sub&(1<<i))!=0){
                sum+=(i+1);
            }
        }
        if(sum==r1+r2){
            if(in==false){
                mins=INF;
                in=true;
            }
            
            if(mins>expcon(remain)){
                minremove=sub;
                mins=expcon(remain);
            }
        }
    }
    

    if(minremove==-1){
        cout<<-1;
    }else{
        for(int i=0; i<10; i++){
            if((minremove&(1<<i))!=0){
                cout<<(char)('1'+i);
            }
        }
        
        
    }
    cout<<" ";
    
    cout<<fixed<<setprecision(5)<<mins<<endl;
    
    mode=1;
     in=false;
    mins=getsum(s);
    vector<double> t2meme(2048,-1);
    meme=t2meme;
    minremove=-1;
    for (int sub = s; sub; sub = (sub - 1) & s) {
        // sub 就是 S 的合法子集
        int remain = s ^ sub; // remain 是 S 中去除 sub 后的剩余集合
        if(sub==8){
            int a=0;
        }
        int sum=0;
        for(int i=0; i<10; i++){
            if((sub&(1<<i))!=0){
                sum+=(i+1);
            }
        }
        if(sum==r1+r2){
            if(in==false){
                mins=-1;
                in=true;
            }
            
            if(mins<expcon(remain)){
                minremove=sub;
                mins=expcon(remain);
            }
        }
    }

    if(minremove==-1){
        cout<<-1;
    }else{
        for(int i=0; i<10; i++){
            if((minremove&(1<<i))!=0){
                cout<<(char)('1'+i);
            }
        }
        
    }
    cout<<' ';
    cout<<fixed<<setprecision(5)<<mins<<endl;

}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
        solve();
    
    return 0;
}