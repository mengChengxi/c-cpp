#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

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
MathSieve sieve(1000005);

/* ---------------- 示例用法 ----------------
// 1. 强烈建议：在全局作用域初始化！填入题目数据范围的最大值 N


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

void solve() {
    int n;
    cin>>n;
    auto factors = sieve.factorize(n);

    int sum=0;
    for(int i=0; i<factors.size(); i++){
        sum+=factors[i].second;
    }
  
    cout<<factors.size()+sum-1<<endl;

    


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