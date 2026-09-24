#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

// ==========================================
// 【大素数组合数模板】
// 适用场景：p 是大素数（如 1e9+7 或 998244353），且 n 的上限在 10^6 级别。
// ==========================================
const int MOD = 1000000007; // 填入具体模数，如 998244353
const int MAXN = 10000;   // 根据题目 n 的最大范围填写（比如 10^6 + 5）

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
    int n;
    cin>>n;
    long long res=0;

    for(int i=1; i<=n; i++){
        for(int j=0; j<=i; j++){
            int left=i+1+j-1;
            int right=n-left-1;

            if(left>=n){
                left=n;
                right=0;
            }

            if(right<0){
                right=0;
            }
            res=(res+C(left,j)*C(right,i-j)%mod*(i+j+1)%mod)%mod;

        }
    }

    res++;

    
    cout<<res%mod<<endl;
}

int main() {
    init_comb();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int dashabi;
    cin >> dashabi;
    while (dashabi--) {
        solve();
    }
    return 0;
}