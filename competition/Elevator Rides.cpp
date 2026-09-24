#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // 优化 I/O 操作
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long x;
    if (!(cin >> n >> x)) return 0;

    vector<long long> w(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }

    // dp 数组大小为 2^n
    // pair<int, long long> = {需要的趟数, 最后一趟占用的重量}
    int limit = 1 << n;
    vector<pair<int, long long>> dp(limit);
    
    // 初始化边界条件：0个人时，视为需要1趟空电梯，占用重量为0
    dp[0] = {1, 0};

    // 遍历所有可能的子集状态
    for (int mask = 1; mask < limit; mask++) {
        dp[mask] = {n + 1, 0}; // 初始化为最大值
        
        for (int i = 0; i < n; i++) {
            // 如果第 i 个人在当前集合 mask 中
            if (mask & (1 << i)) {
                // 提取没有第 i 个人时的最优状态
                auto option = dp[mask ^ (1 << i)];
                
                if (option.second + w[i] <= x) {
                    // 第 i 个人可以和上一批人共用最后一趟电梯
                    option.second += w[i];
                } else {
                    // 第 i 个人需要新开一趟电梯
                    option.first++;
                    option.second = w[i];
                }
                
                // 更新当前 mask 的最优解
                dp[mask] = min(dp[mask], option);
            }
        }
    }

    // 最终答案即为包含所有人的状态 (2^n - 1) 对应的最少趟数
    cout << dp[limit - 1].first << "\n";

    return 0;
}