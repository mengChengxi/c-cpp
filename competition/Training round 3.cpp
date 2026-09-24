#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod =998244353;
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
// ==========================================
// 【大素数组合数模板】
// 适用场景：p 是大素数（如 1e9+7 或 998244353），且 n 的上限在 10^6 级别。
// ==========================================
const int MOD = 998244353; // 填入具体模数，如 998244353
const int MAXN = 10000005;   // 根据题目 n 的最大范围填写（比如 10^6 + 5）

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
    long long n,k,p;

    cin>>n>>k>>p;
    if(n-k*p<0){
        cout<<1<<endl;
        return;
    }
    long long res=0;
    long long prountill=1;
    for(int i=0; i<k ; i++){
        long long y=n-i*p;
        long long pros=fac[y]*fac[n-p]%mod*invFac[y-p]%mod*invFac[n]%mod;
        res=(res+(prountill*(1-pros+mod)%mod))%mod;
        prountill=prountill*pros%mod;
    }

    cout<<res<<endl;
    
}

int main() {
    init_comb();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
        solve();
    
    return 0;
}



struct MathSieve {
    int n;
    std::vector<int> primes, spf;
    
    // [模块 1] 欧拉函数 phi(x): 1~x 中与 x 互质的正整数个数
    // std::vector<long long> phi;
    
    // [模块 2] 莫比乌斯函数 mu(x): 若 x 含平方因子则为 0；否则为 (-1)^k (k 为 x 的不同质因子个数)
    // std::vector<int> mu;
    
    // [模块 3] 约数个数 d(x): x 的所有正约数的个数 (需搭配 cnt 记录最小质因子的指数)
    // std::vector<int> d, cnt;

    // 构造函数：声明对象时自动完成所有预处理，时间复杂度 O(N)
    MathSieve(int _n) : n(_n), spf(_n + 1) /*, phi(_n + 1), mu(_n + 1), d(_n + 1), cnt(_n + 1)*/ {
        // [模块 1] if (_n >= 1) phi[1] = 1;
        // [模块 2] if (_n >= 1) mu[1] = 1;
        // [模块 3] if (_n >= 1) { d[1] = 1; cnt[1] = 0; }
        
        for (int i = 2; i <= n; ++i) spf[i] = i; // 初始化每个数的最小质因数为自己
        
        for (int i = 2; i <= n; ++i) {
            if (spf[i] == i) {
                primes.push_back(i);
                // --- 规则 1：处理质数 ---
                // [模块 1] phi[i] = i - 1;
                // [模块 2] mu[i] = -1;
                // [模块 3] d[i] = 2; cnt[i] = 1;
            }
            for (int p : primes) {
                if (p * i > n) break; // 越界保护
                spf[p * i] = p;       // 记录合数 p * i 的最小质因数 p
                
                if (i % p == 0) {
                    // --- 规则 3：p 已经是 i 的质因子 ---
                    // [模块 1] phi[p * i] = phi[i] * p;
                    // [模块 2] mu[p * i] = 0; // 出现平方因子，毒药生效
                    // [模块 3] d[p * i] = d[i] / (cnt[i] + 1) * (cnt[i] + 2); cnt[p * i] = cnt[i] + 1;
                    break; // 核心：保证每个合数只被其最小质因数筛掉
                } else {
                    // --- 规则 2：p 和 i 互质 ---
                    // [模块 1] phi[p * i] = phi[i] * phi[p];
                    // [模块 2] mu[p * i] = -mu[i];
                    // [模块 3] d[p * i] = d[i] * d[p]; cnt[p * i] = 1;
                }
            }
        }
    }

    // 单次查询 O(log N) 质因数分解模板
    // 返回值格式: vector<pair<质因子, 个数>>
    std::vector<std::pair<int, int>> factorize(int x) {
        std::vector<std::pair<int, int>> factors;
        while (x > 1) {
            int p = spf[x];
            int count = 0;
            while (x % p == 0) {
                count++;
                x /= p;
            }
            factors.push_back({p, count});
        }
        return factors;
    }
};

/* ---------------- 示例用法 ----------------
// 1. 强烈建议：在全局作用域初始化！填入题目数据范围的最大值 N
MathSieve sieve(100005);

void sample() {
    // 2. O(1) 判断质数
    if (sieve.spf[97] == 97) {}

    // 3. O(log N) 快速质因数分解
    auto factors = sieve.factorize(120);
    // 返回: {{2, 3}, {3, 1}, {5, 1}}

    // 4. 遍历所有素数
    // for (int p : sieve.primes) { ... }

    // 5. 解开扩展模块的注释后可直接调用：
    // [模块 1] std::cout << "phi(12) = " << sieve.phi[12] << "\n"; // 4
    // [模块 2] std::cout << "mu(10) = " << sieve.mu[10] << "\n";   // 1
    // [模块 3] std::cout << "d(12) = " << sieve.d[12] << "\n";     // 6
}
------------------------------------------ */