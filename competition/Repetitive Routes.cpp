#include <bits/stdc++.h>
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

    vector<int> people(2*n);
    vector<int> pos(2*n);

    vector<int> lastoccurpos(2*n+5,-1);
    vector<int> lastoccurpeople(2*n+5,-1);

    for(int i=0; i<2*n; i++){
        cin>>people[i];
        cin>>pos[i];
    }

    FenwickTree bit(2*n+3);
    long long complains=0;
    for(int i=0; i<2*n; i++){

        if(lastoccurpos[pos[i]]==-1){
            lastoccurpos[pos[i]]=i;
            bit.add(i+1,1);
        }else{
            bit.add(lastoccurpos[pos[i]]+1,-1);
            lastoccurpos[pos[i]]=i;
            bit.add(i+1,1);
        }
        

        if(lastoccurpeople[people[i]]==-1){
            lastoccurpeople[people[i]]=i;
        }else{
            int totalstop=i-lastoccurpeople[people[i]]+1;
            int totalkinds=bit.queryRange(lastoccurpeople[people[i]]+1, i+1);
            complains+=(totalstop-totalkinds);

        }


    }

    cout<<complains<<endl;



    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
   
        solve();
    
    return 0;
}



const long long LLINF = 1e18;

struct Edge {
    int u, v;
    long long w;
};

pair<vector<long long>, bool> bellman_ford(int n, int start, const vector<Edge>& edges) {
    vector<long long> dist(n + 1, LLINF);
    dist[start] = 0;

    for (int i = 1; i <= n - 1; i++) {
        bool any_update = false;
        for (const auto& e : edges) {
            if (dist[e.u] < LLINF && dist[e.u] + e.w < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
                any_update = true;
            }
        }
        if (!any_update) break;
    }

    bool has_negative_cycle = false;
    for (const auto& e : edges) {
        if (dist[e.u] < LLINF && dist[e.u] + e.w < dist[e.v]) {
            has_negative_cycle = true;
            break;
        }
    }

    return {dist, has_negative_cycle};
}



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