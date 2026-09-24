// #include <bits/stdc++.h>
// using namespace std;
// const int INF = 0x3f3f3f3f;
// const int mod = 1e9 + 7;
// #define mkp make_pair


// long long fastPower(long long base, long long exp) {
//     long long res = 1;
//     base %= mod;
//     while (exp > 0) {
//         if (exp % 2 == 1) res = (res * base) % mod;
//         base = (base * base) % mod;
//         exp /= 2;
//     }
//     return res;
// }

// long long modInverse(long long n) {
//     return fastPower(n, mod - 2);
// }

// void solve() {

    
//     int n;

//     cin>>n;
//     vector<int> a(n);
//     vector<int> p(n);

//     int inv=modInverse(10000);

//     for(int i=0; i<n; i++){
//         cin>>a[i];
//     }

//     for(int i=0; i<n; i++){
//         cin>>p[i];
//     }

//     vector<long long> pro(10,0);// probability it is odd;

//     for(int i=0; i<n; i++){
//         for(int j=0; j<10; j++){
//             if((a[i]>>j)%2==0){
                
//             }else{
//                 pro[j]=(pro[j]*(10000l-p[i])%mod*inv%mod+(mod+1l-pro[j])*p[i]%mod*inv%mod)%mod;
//             }
//         }
//     }

//     long long res=0;

//     for(int i=1; i<=10; i++){
//         for(int j=0; j<i; j++){
//             res=(res+(1<<j)*pro[j]%mod*pro[i-j-1]%mod)%mod;
//         }
//     }

//     for(int i=1; i<=10; i++){
//         for(int j=i; j<10 ; j++){
//             res=(res+(1<<j)*pro[j]%mod*pro[9-j+i]%mod)%mod;
//         }
//     }

//     cout<<res<<endl;


// }

// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
//     int dashabi;
//     cin >> dashabi;
//     while (dashabi--) {
//         solve();
//     }
//     return 0;
// }


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9; // 题目最大单个数 2e7，12个加起来最大 2.4e8，1e9 足够且不会溢出
int dp[4096][4096];
int cost[12][12][12];
vector<int> masks[13];

int main() {
    // 优化输入输出流
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // 1. 读取输入：正好对应题目中三层循环的平铺顺序
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
            for (int z = 0; z < n; ++z) {
                cin >> cost[x][y][z];
            }
        }
    }

    // 2. 初始化 DP 数组与状态分组
    for (int i = 0; i < (1 << n); ++i) {
        for (int j = 0; j < (1 << n); ++j) {
            dp[i][j] = INF;
        }
        // 将状态按 1 的个数归类
        masks[__builtin_popcount(i)].push_back(i);
    }

    dp[0][0] = 0; // 初始状态：什么都没选，代价为 0

    // 3. 开始状压 DP (拉取型转移 Pull DP)
    for (int k = 1; k <= n; ++k) {
        int x = k - 1; // 当前正在处理第 x 层 (0-indexed)
        
        // 只遍历 popcount 等于 k 的合法状态
        for (int mask_y : masks[k]) {
            for (int mask_z : masks[k]) {
                int min_val = INF;

                // 快速遍历 mask_y 中为 1 的位
                for (int temp_y = mask_y; temp_y > 0; temp_y &= temp_y - 1) {
                    int y = __builtin_ctz(temp_y);      // 取出最低位的 1 所在的索引
                    int prev_y = mask_y ^ (1 << y);     // 抠掉这个 1，得到前置状态

                    // 快速遍历 mask_z 中为 1 的位
                    for (int temp_z = mask_z; temp_z > 0; temp_z &= temp_z - 1) {
                        int z = __builtin_ctz(temp_z);
                        int prev_z = mask_z ^ (1 << z);

                        // 只有前置状态合法时才进行转移
                        if (dp[prev_y][prev_z] != INF) {
                            min_val = min(min_val, dp[prev_y][prev_z] + cost[x][y][z]);
                        }
                    }
                }
                dp[mask_y][mask_z] = min_val;
            }
        }
    }

    // 4. 输出最终结果
    int full_mask = (1 << n) - 1;
    cout << dp[full_mask][full_mask] << "\n";

    return 0;
}