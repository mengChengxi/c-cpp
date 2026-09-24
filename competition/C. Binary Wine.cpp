#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair



void solve() {
    int n,q;
    cin>>n>>q;

    // 线性基数组，30位足够覆盖 10^9 (10^9 < 2^{30})
    // 核心原理：在 GF(2) 域上维护一个与原数组张成空间相同的极大线性无关组（基）
    vector<long long> basis(30, 0);
    
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        
        // 将 x 插入线性基（本质是高斯消元求行阶梯矩阵）
        for (int j = 29; j >= 0; j--) {
            if ((x >> j) & 1) {
                if (!basis[j]) {
                    // 找到一个最高位在第 j 位的独立基向量，存入主元并结束当前元素的消元
                    basis[j] = x;
                    break;
                }
                // basis[j] 已被占据，利用异或（初等行变换）消去 x 第 j 位的 1
                x ^= basis[j];
            }
        }
        // 若 x 最终下沉变为 0，说明 x 可以由已有基向量线性组合得到，属于冗余元素
    }
    
    // 贪心求最大异或和
    long long max_xor = 0;
    // 贪心原理：二进制中，高位的 1 权值 (2^j) 严格大于所有低位全为 1 的权值总和 (2^j - 1)
    // 因为 basis[j] 的最高位必定为 j，只要异或后能让 max_xor 的第 j 位变成 1，整体数值必将严格递增
    for (int j = 29; j >= 0; j--) {
        if ((max_xor ^ basis[j]) > max_xor) {
            max_xor ^= basis[j];
        }
    }
    
    //cout << max_xor << "\n";


    while (q--) {
        int t;
        cin>>t;

        if(t<max_xor){
            cout<<0<<endl;
        }else{
            cout<<t-max_xor<<endl;
        }
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

// === 术语定义 ===
// 割点 (Cut Vertex): 无向图中一旦删去，图的连通块数量就会增加的点。
// v-BCC (点双连通分量): 没有割点的无向连通子图。
// === 使用方法 ===
// 1. 割点归属：割点可以同时属于多个 v-BCC，因此不能用单一 belong 数组。
// 2. 特殊收网：发现 low[v] >= dfn[u] 立即弹栈，且割点 u 不出栈！
// 3. 根节点特判：DFS 起点必须有两个以上独立子树才是真正割点。

const int N = 100005;
vector<int> adj[N];
int dfn[N], low[N], timer;
int st[N], top;
bool is_cut[N];
vector<vector<int>> vbcc;
int vbcc_cnt;

void tarjan_vbcc(int u, int root) {
    dfn[u] = low[u] = ++timer;
    st[++top] = u;
    int child_count = 0;

    if (u == root && adj[u].empty()) { // 孤立点特判
        vbcc_cnt++;
        vbcc.push_back({u});
        return;
    }

    for (int v : adj[u]) {
        if (!dfn[v]) {
            child_count++;
            tarjan_vbcc(v, root);
            low[u] = min(low[u], low[v]);

            if (low[v] >= dfn[u]) {
                is_cut[u] = true; // 涉嫌割点
                vbcc_cnt++;
                vector<int> current_vbcc;
                int x;
                do {
                    x = st[top--];
                    current_vbcc.push_back(x);
                } while (x != v); // 注意：只弹到儿子 v 为止
                current_vbcc.push_back(u); // 割点 u 加进去，但不出栈
                vbcc.push_back(current_vbcc);
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }

    // 树根特判
    if (u == root && child_count < 2) {
        is_cut[u] = false;
    }
}

void sample_vbcc(int n) {
    // 多测初始化基建
    memset(dfn, 0, (n + 1) * sizeof(int));
    memset(low, 0, (n + 1) * sizeof(int));
    memset(is_cut, 0, (n + 1) * sizeof(bool));
    timer = top = vbcc_cnt = 0;
    vbcc.clear();
    for (int i = 0; i <= n; i++) adj[i].clear();

    // TODO: 建无向图逻辑...

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            top = 0; // 点双特殊清空栈
            tarjan_vbcc(i, i);
        }
    }
}