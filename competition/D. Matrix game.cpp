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

void solve() {
    long long a,b,k;
    cin>>a>>b>>k;

    long long l=(a-1)*k+1;



    long long faca1=1;
    for(int i=1; i<a; i++){
        faca1=(faca1*i)%mod;
    }
    long long faca=(faca1*a)%mod;

    faca1=modInverse(faca1);
    faca=modInverse(faca);


    // ==========================================
    // 【需要你填写的核心参数：MAXP】
    // 含义：题目中可能出现的【最大素数 p】的上限 + 5。
    // 怎么填：
    // 1. 如果题目明确给出了固定的模数（比如 p = 100003），直接填 100005。
    // 2. 如果题目说 p 是一个输入的素数，且 p <= 10^5，那就填 100005。
    // 注意：MAXP 决定了预处理数组的大小。如果 p 很大（比如 10^9），切记不能用卢卡斯！
    // ==========================================
    const int MAXP = 100005; 
    
    long long lucas_fac[MAXP];    // 存储 0 到 p-1 的阶乘取模结果
    long long lucas_invFac[MAXP]; // 存储 0 到 p-1 的阶乘逆元结果
    
    // 内部辅助函数 1：快速幂，用于计算 (base^exp) % p
    long long lucas_qpow(long long base, long long exp, long long p) {
        long long res = 1;
        base %= p;
        while (exp > 0) {
            if (exp & 1) res = res * base % p;
            base = base * base % p;
            exp >>= 1;
        }
        return res;
    }
    
    // 内部辅助函数 2：费马小定理求逆元，计算 1/n 模 p 的值
    long long lucas_inv(long long n, long long p) {
        return lucas_qpow(n, p - 2, p);
    }
    
    // ==========================================
    // 【核心函数 1：全局初始化 lucas_init】
    // 使用方法：必须在处理所有测试数据（while(t--)）之前调用一次！
    // 参数 p：题目给定的模数（必须是素数）。
    // 复杂度：O(p)
    // ==========================================
    void lucas_init(int p) {
        lucas_fac[0] = 1;
        lucas_invFac[0] = 1;
        // 递推计算阶乘
        for (int i = 1; i < p; i++) {
            lucas_fac[i] = lucas_fac[i - 1] * i % p;
        }
        // 逆元递推优化：先求出最大阶乘的逆元，再倒推回去，复杂度从 O(p log p) 优化到 O(p)
        lucas_invFac[p - 1] = lucas_inv(lucas_fac[p - 1], p);
        for (int i = p - 2; i >= 1; i--) {
            lucas_invFac[i] = lucas_invFac[i + 1] * (i + 1) % p;
        }
    }
    
    // 内部辅助函数 3：计算微观组合数 C(n, m) % p，此时要求传进来的 n 和 m 必须严格小于 p
    long long lucas_C(long long n, long long m, long long p) {
        if (m > n || m < 0) return 0; // 特判非法情况：选的物品数不能大于总数，也不能为负
        if (m == 0 || m == n) return 1;
        return lucas_fac[n] * lucas_invFac[m] % p * lucas_invFac[n - m] % p;
    }
    
    // ==========================================
    // 【核心函数 2：查询组合数 lucas_get】
    // 使用方法：在 solve() 里面直接调用此函数获取结果。
    // 变量含义：
    //   - n：总物品数（即组合数 C(n, m) 的上标/总数）。可达 10^18。
    //   - m：选择的物品数（即组合数 C(n, m) 的下标/选择数）。可达 10^18。
    //   - p：模数（必须是素数）。
    // 返回值：C(n, m) % p 的结果
    // 复杂度：O(log_p n)
    // ==========================================
    long long lucas_get(long long n, long long m, long long p) {
        if (p == 2) return (n & m) == m ? 1 : 0;
        if (m == 0) return 1;
        if (n == 0) return 0; 
        // 卢卡斯定理核心递归公式：C(n % p, m % p) * Lucas(n / p, m / p) % p
        return lucas_C(n % p, m % p, p) * lucas_get(n / p, m / p, p) % p;
    }

    // ==========================================
    // 【大素数组合数模板】
    // 适用场景：p 是大素数（如 1e9+7 或 998244353），且 n 的上限在 10^6 级别。
    // ==========================================
    const int MOD = 1000000007; // 填入具体模数，如 998244353
    const int MAXN = 1000005;   // 根据题目 n 的最大范围填写（比如 10^6 + 5）
    
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