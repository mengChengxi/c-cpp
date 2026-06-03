#include <bits/stdc++.h>
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

long long c(long long total, long long m,long long modinversem){
    if(total<m){
        return 0;
    }
    int c=1;
    for(int i=0; i<m; i++){
        c=(c*(total-i))%mod;
    }
    c=(c*(modinversem))%mod;
    return c;
}

// ==========================================
// 【大素数组合数模板】
// 适用场景：p 是大素数（如 1e9+7 或 998244353），且 n 的上限在 10^6 级别。
// ==========================================
const int MOD = 1e9+7; // 填入具体模数，如 998244353
const int MAXN = 2000005;   // 根据题目 n 的最大范围填写（比如 10^6 + 5）

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
void solve() {
    int n,m,k;
    cin>>n>>m>>k;
    vector<int> nums(n+1,0);
    for(int i=0; i<n; i++){
        int tt;
        cin>>tt;
        nums[tt]++;
    }

    long long modinversem=1;
    for(int i=m; i>0; i--){
        modinversem=(modinversem*modInverse(i))%mod;
    }

    vector<int> presum(n+1);
    presum[0]=0;
    for(int i=1; i<n+1; i++){
        presum[i]=presum[i-1]+nums[i];
    }

    

    long long count=0;
    for(int i=1; i<n+1; i++){
        if(nums[i]==0){
            continue;
        }
        if(i+k<=n){
            int total= presum[i+k]-presum[i-1];
            count=(count+C(total,m)-C(total-nums[i],m)+mod)%mod;

        }else{
            int total= presum[n]-presum[i-1];
            count=(count+C(total,m)-C(total-nums[i],m)+mod)%mod;

        }
        

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