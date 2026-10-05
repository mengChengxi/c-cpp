#include <algorithm>
#include <bits/stdc++.h>

using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 998244353;
#define mkp make_pair

// ==========================================
// 【大素数组合数模板】
// 适用场景：p 是大素数（如 1e9+7 或 998244353），且 n 的上限在 10^6 级别。
// ==========================================
const int MOD = 998244353; // 填入具体模数，如 998244353
const int MAXN = 100005;   // 根据题目 n 的最大范围填写（比如 10^6 + 5）

long long fac[MAXN];
long long invFac[MAXN];

// 快速幂求逆元
long long qpow(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp & 1) res = res * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return res;
}

// ==========================================
// 【全局初始化 init_comb】
// 极其重要：必须在 main 函数开头调用一次！(O(N))
// ==========================================
void init_comb() {
    fac[0] = 1;
    invFac[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fac[i] = fac[i - 1] * i % MOD;
    }
    // 先算最大阶乘的逆元
    invFac[MAXN - 1] = qpow(fac[MAXN - 1], MOD - 2);
    // 倒推算其他逆元
    for (int i = MAXN - 2; i >= 1; i--) {
        invFac[i] = invFac[i + 1] * (i + 1) % MOD;
    }
}

// ==========================================
// 【O(1) 查询组合数】
// 返回值：C(n, m) % MOD
// ==========================================
long long C(long long n, long long m) {
    if (m > n || m < 0) return 0;
    if (m == 0 || m == n) return 1;
    // 公式：n! * (m!)^-1 * ((n-m)!)^-1 % MOD
    return fac[n] * invFac[m] % MOD * invFac[n - m] % MOD;
}

struct block{
    long long area;
    long long length;
    long long width;
    bool operator<(block &other){
        return area<other.area;
    }
};
void solve() {
    int n;
    cin>>n;
    vector<block> blocks(n);

    for(int i=0; i<n; i++){
        long long l,w;
        cin>>l>>w;
        if(w>l){
            swap(l,w);
        }
        long long area=l*w;
        blocks[i]={area,l,w};

    }

    sort(blocks.begin(),blocks.end());

    long long count=1;
    for(int i=0; i<n-1; i++){
        int type=0;

        if(blocks[i].length<=blocks[i+1].length&&blocks[i].width<=blocks[i+1].width){
            type++;
        }
        if(blocks[i].length<=blocks[i+1].width&&blocks[i].width<=blocks[i+1].length){
            type++;
        }

        if(type==0){
            cout<<0<<endl;
            return;
        }
    }
    long long last=-1;
    long long lastcount=1;
    for(int i=0; i<n; i++){
        if(blocks[i].area!=last){
            count=count*fac[lastcount]%mod;
            lastcount=1;
            last=blocks[i].area;
        }else{
            lastcount++;
        }
    }
    count=count*fac[lastcount]%mod;


    for(int i=0; i<n-1; i++){
        if(blocks[i].area!=blocks[i+1].area){
            if(blocks[i].length==blocks[i].width){
                count=(count*(blocks[i+1].length-blocks[i].length+1))%mod*(blocks[i+1].width-blocks[i].length+1)%mod;
                continue;
            }
            long long ways=0;
            if(blocks[i].length<=blocks[i+1].length&&blocks[i].width<=blocks[i+1].width){
                ways=ways+(blocks[i+1].length-blocks[i].length+1)%mod*(blocks[i+1].width-blocks[i].width+1)%mod;
            }
            if(blocks[i].length<=blocks[i+1].width&&blocks[i].width<=blocks[i+1].length){
                ways=(ways+(blocks[i+1].width-blocks[i].length+1)%mod*(blocks[i+1].length-blocks[i].width+1)%mod)%mod;
            }

            count=count*ways%mod;
            
        }
    }
    if(blocks[n-1].length!=blocks[n-1].width){
        count=count*2%mod;
    }

    cout<<count<<endl;

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    init_comb();
    int dashabi;
    cin >> dashabi;
    while (dashabi--) {
        solve();
    }
    return 0;
}