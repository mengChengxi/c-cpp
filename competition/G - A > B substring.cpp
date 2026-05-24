#include <bits/stdc++.h>
#include <unordered_map>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

class FenwickTree {
private:
    vector<long long> tree; // 使用 long long 防爆 int 越界
    int n;
    // 核心位运算内部封装：提取 x 二进制中的最低位 1
    inline int lowbit(int x) {
        return x & (-x);
    }
public:
    // ==========================
    // =====    构造函数区    =====
    // ==========================
    // 方式一：只划定大小的基础构树，时间复杂度 O(N) 仅赋零。
    // 用法：当你有一批动态数据，后续需要你通过 for 循环一个一个手动添加的时候使用。
    // 示例：FenwickTree bit(10);  创建一个内部容量足以覆盖下标 1~10 的全零树
    FenwickTree(int n) {
        this->n = n;
        // 底层自动为你开辟 n+1 空间，外部使用者彻底不用操心理论越界问题
        tree.assign(n + 1, 0); 
    }
    // 方式二：拥有黑科技的 O(N) 极速构树法 (高度推荐)
    // 用法：当你已经拥有了一个完整的原始数组，希望以最快的方式拿它作为树的初始状态时。
    // 示例：
    // vector<int> nums = {4, 6, 2, 8}; 
    // FenwickTree bit(nums);
    FenwickTree(const vector<int>& nums) {
        this->n = nums.size();
        tree.assign(n + 1, 0); 
        
        // 步骤 1: 纯物理搬运，把原数组平移塞进 1-indexed 的内部序号里
        for (int i = 0; i < n; i++) {
            tree[i + 1] = nums[i]; 
        }
        // 步骤 2: 线性黑科技算和。绝不跨级汇报，只把包袱踢给当前的直系父亲，完美 O(N)
        for (int i = 1; i <= n; i++) {
            int parent = i + lowbit(i);
            if (parent <= n) {
                tree[parent] += tree[i];
            }
        }
    }
    // ==========================
    // =====    核心操作区    =====
    // ==========================
    // [增] 单点修改：在虚拟树的第 i 个位置增加 delta 值。时间复杂度 O(logN)
    // 用法注意：
    // - 如果题目告诉你"从位置 1 算起"：直接原汁原味调用 bit.add(idx, val);
    // - 如果你自己在循环 C++ 原生数组 nums：要自发记得加 1 调用 bit.add(i + 1, nums[i]);
    void add(int i, long long delta) {
        while (i <= n) {
            tree[i] += delta;
            i += lowbit(i);  // 更新自身后，往上级爬升同步增加
        }
    }
    // [查-单前缀] 简单前缀查询：求出前 i 个元素的和 (即求原区间 [1, i] 的总和)
    // 用法举例：bit.query(5);  // 代表查询大区间的第 1 项加到第 5 项的总和
    // 时间复杂度 O(logN)
    long long query(int i) {
        long long sum = 0;
        while (i > 0) {
            sum += tree[i];
            i -= lowbit(i);  // 去掉低位的 1，往左侧大跳拼接前缀
        }
        return sum;
    }
    // [查-任意区间] 区间求和：求出绝对区间 [left, right] 之间的累计和
    // 前提：务必保证参数 left <= right，且它们都是从 1 开始计数的抽象下标！
    // 用法举例：
    // - 若题目直给“查第 3 到第 5 个数”: bit.queryRange(3, 5);
    // - 若你在一组 0-indexed 的 nums 数组里查 nums[L] 到 nums[R]：bit.queryRange(L + 1, R + 1);
    long long queryRange(int left, int right) {
        return query(right) - query(left - 1); // 右手大前缀 减去 没用的左手前缀 = 中段纯净数据
    }
};



void solve() {
    int n;
    cin>>n;
    string s;
    cin>>s;

    int a=0;
    int b=0;

    FenwickTree bit(2*n+10);
    bit.add(n + 1, 1);
    long long count=0;
    for(int i=0; i<n; i++){
        if(s[i]=='A'){
            a++;
        }
        if(s[i]=='B'){
            b++;
        }
        count+=bit.query(n+1+a-b-1);
        bit.add(n+1+a-b, 1);
    }

    cout<<count<<endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int dashabi;
   
        solve();
    
    return 0;
}