#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;
    cin>>n;
    string s;
    cin>>s;

    long long maxn=0;

    for(int i=1; i<n-1; i++){
        if(s[i]=='1'&&s[i-1]=='0'&&s[i+1]=='0'){
            int right=i+1;
            long long right0=0;
            while(right<n&&s[right]=='0'){
                right0+=right;
                right++;
            }

            int left=i-1;
            long long left0=0;
            while(left>=0&&s[left]=='0'){
                left0+=(n-left-1);
                left--;
            }

            maxn=max(maxn,left0+right0+1);
        }
    }

    
    for(int i=0; i<n; i++){
        if(s[i]=='0'){

            
            long long above=0;
            long long below=0;

            if(i==0){
                above=-1;
            }
            while(i<n&&s[i]=='0'){
                above+=i;
                below+=(n-i-1);

                i++;
            }

            if(i==n){
                below--;
            }
            maxn=max(maxn,above+1);
            maxn=max(maxn,below+1);
        }
    }  
    if(maxn==0){
        if(s!="0"){
            maxn=1;
        }
    }
    cout<<maxn<<endl;
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

const int MAXV = 10000000;
std::vector<int> primes;
std::vector<int> spf(MAXV + 1);

// 必须在 main 函数开头调用此初始化函数
// 时间复杂度: O(MAXV)
void build_spf(int n = MAXV) {
    for (int i = 2; i <= n; ++i) spf[i] = i;
    for (int i = 2; i <= n; ++i) {
        if (spf[i] == i) primes.push_back(i);
        for (int p : primes) {
            if (p * i > n) break;
            spf[p * i] = p;
            if (i % p == 0) break; // 保证每个合数只被其最小质因数筛掉
        }
    }
}

// 单次查询 O(log n) 质因数分解模板
// 空间换时间：依赖预处理的 spf 数组
// 返回值格式: vector<pair<质因子, 个数>>
std::vector<std::pair<int, int>> factorize(int n) {
    std::vector<std::pair<int, int>> factors;
    while (n > 1) {
        int p = spf[n];
        int count = 0;
        while (n % p == 0) {
            count++;
            n /= p;
        }
        factors.push_back({p, count});
    }
    return factors;
}

struct MathSieve {
    int n;
    std::vector<int> primes;
    std::vector<int> spf; 
    
    // [可选扩展] 欧拉函数 phi(x): 求 1 到 x 中与 x 互质的整数个数
    // 取消下面相关代码的注释即可开启 O(N) 预处理
    // std::vector<long long> phi;

    // 构造函数：声明对象时自动完成所有预处理，时间复杂度 O(N)
    MathSieve(int _n) : n(_n), spf(_n + 1) /*, phi(_n + 1)*/ {
        // if (_n >= 1) phi[1] = 1;
        
        for (int i = 2; i <= n; ++i) spf[i] = i; // 初始化每个数的最小质因数为自己
        
        for (int i = 2; i <= n; ++i) {
            if (spf[i] == i) { // 如果最小质因数是自己，说明是质数
                primes.push_back(i);
                // phi[i] = i - 1; // 规则 1：质数 p 的 phi 值为 p-1
            }
            for (int p : primes) {
                if (p * i > n) break; // 越界保护
                spf[p * i] = p;       // 记录合数 p * i 的最小质因数 p
                
                if (i % p == 0) {
                    // phi[p * i] = phi[i] * p; // 规则 3：p 已经是 i 的质因数，无新质因子引入
                    break; // 核心：保证每个合数只被其最小质因数筛掉
                } else {
                    // phi[p * i] = phi[i] * phi[p]; // 规则 2：p 和 i 互质，利用积性函数性质
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
// 1. 初始化：预处理 100005 以内的数据
MathSieve sieve(100005);

void sample_usage() {

    // 2. O(1) 判断质数
    if (sieve.spf[97] == 97) {}

    // 3. O(log N) 快速质因数分解
    auto factors = sieve.factorize(120);
    // 返回: {{2, 3}, {3, 1}, {5, 1}}

    // 4. 遍历所有素数
    // for (int p : sieve.primes) { ... }

    // 5. 解开 phi 的注释后可直接调用：
    // std::cout << sieve.phi[12] << "\n";
}
------------------------------------------ */