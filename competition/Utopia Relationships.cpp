#include <bits/stdc++.h>
#include <iterator>
#include <utility>
#include <vector>
using namespace std;
const int mod = 1e9 + 7;
#define mkp make_pair

// 【Dinic 最大流】
const long long INF = 1e18;
const int MAXN = 100005;

struct Edge {
    int to;
    long long cap;
    int rev_idx;
    bool is_forward;
};

std::vector<Edge> adj[MAXN];
int level[MAXN];
int cur[MAXN];

void init_dinic(int n) {
    for (int i = 0; i <= n; i++) {
        adj[i].clear();
    }
}

void add_edge(int u, int v, long long cap) {
    adj[u].push_back({v, cap, (int)adj[v].size(), true});
    adj[v].push_back({u, 0, (int)adj[u].size() - 1, false});
}

bool bfs(int S, int T, int n) {
    for (int i = 0; i <= n; i++) {
        level[i] = -1;
        cur[i] = 0;
    }
    
    std::queue<int> q;
    level[S] = 0;
    q.push(S);
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int i = 0; i < adj[u].size(); i++) {
            Edge &e = adj[u][i];
            if (e.cap > 0 && level[e.to] == -1) {
                level[e.to] = level[u] + 1;
                q.push(e.to);
            }
        }
    }
    return level[T] != -1;
}

long long dfs(int u, int T, long long flow) {
    if (u == T || flow == 0) return flow;
    
    long long total_flow = 0;
    
    for (int &i = cur[u]; i < adj[u].size(); i++) {
        Edge &e = adj[u][i];
        
        if (level[e.to] == level[u] + 1 && e.cap > 0) {
            long long push = dfs(e.to, T, std::min(flow, e.cap));
            
            if (push > 0) {
                e.cap -= push;
                adj[e.to][e.rev_idx].cap += push;
                
                flow -= push;
                total_flow += push;
                
                if (flow == 0) break;
            }
        }
    }
    return total_flow;
}

long long dinic(int S, int T, int n) {
    long long max_flow = 0;
    while (bfs(S, T, n)) {
        max_flow += dfs(S, T, INF);
    }
    return max_flow;
}

// ================= 功能演示 =================
void sample_dinic_usage() {
    int n = 4; // 中间节点数量
    int S = 0, T = n + 1; // 设定源点和汇点
    int total_nodes = T; // 图中最大节点编号
    
    // 1. 初始化（每次运行前必须调用）
    init_dinic(total_nodes);
    
    // 2. 建图: add_edge(u, v, cap)
    add_edge(S, 1, 10);
    add_edge(1, 2, 5);
    add_edge(2, T, 5);
    
    // 3. 运行算法并接收最大流
    long long ans = dinic(S, T, total_nodes);
    std::cout << "最大流: " << ans << "\n";
    
    // 4. 提取具体流量方案
    for (int u = 0; u <= total_nodes; u++) {
        for (int i = 0; i < adj[u].size(); i++) {
            Edge &e = adj[u][i];
            if (!e.is_forward) continue; // 过滤掉算法产生的反向假边
            
            long long actual_flow = adj[e.to][e.rev_idx].cap;
            if (actual_flow > 0) {
                std::cout << "节点 " << u << " -> " << e.to 
                          << " 流过了: " << actual_flow << "\n";
            }
        }
    }
}

void solve() {

    int n,m;

    cin>>n>>m;


    

    
    // int n = 4; // 中间节点数量
    int layer=((n+1)*n)/2;
    int S = 0, T = 2*layer+n+1; // 设定源点和汇点
    int total_nodes = T; // 图中最大节点编号
    
    // 1. 初始化（每次运行前必须调用）
    init_dinic(total_nodes);
    
    vector<pair<int,int>> note(layer+1);

    for(int i=0; i<m; i++){
        int from,to;
        cin>>from>>to;

        if(to>from){
            swap(to,from);
        }

        int id=from*(from-1)/2+to+n;
        int id2=id+layer;
        note[id-n]={from,to};
        add_edge(from, id, 10000);
        add_edge(to, id, 10000);
        add_edge(id, id2, 10000);
    }

    for(int i=0; i<n; i++){
        add_edge(S, i+1, 10000);
    }
    for(int i=n+layer+1; i<n+layer+layer+1; i++){
        add_edge(i, T, 10000);
    }


    // 3. 运行算法并接收最大流
    long long ans = dinic(S, T, total_nodes);
    std::cout << "最大流: " << ans << "\n";

    if(ans!=n*10000){
        cout<<-1<<endl;
        return;
    }

    vector<vector<int>> out(n,vector<int>(n));
    for (int u = 0; u <= total_nodes; u++) {
        for (int i = 0; i < adj[u].size(); i++) {
            Edge &e = adj[u][i];
            if (!e.is_forward) continue; // 过滤掉算法产生的反向假边
            
            long long actual_flow = adj[e.to][e.rev_idx].cap;
            if (actual_flow > 0) {
                if(u<=n+layer&&u>0&&e.to<=n+layer+layer&&e.to>n+layer){
                    //number 
                    out[note[u-n].first-1][note[u-n].second-1]=actual_flow;
                    out[note[u-n].second-1][note[u-n].first-1]=actual_flow;
                }
                
            }
        }
    }

    #define bit(S, i) (((S) >> (i)) & 1)        // 获取 S 的第 i 位是否为 1
    #define set_bit(S, i) ((S) | (1 << (i)))    // 将 S 的第 i 位置为 1
    #define clear_bit(S, i) ((S) & ~(1 << (i))) // 将 S 的第 i 位置为 0
    #define toggle_bit(S, i) ((S) ^ (1 << (i))) // 翻转 S 的第 i 位
    #define lowbit(x) ((x) & -(x))              // 取出最低位的 1（树状数组同款）
    
    // __builtin_popcount(S)：返回 S 在二进制下 1 的个数。如果 S 是 long long，使用 __builtin_popcountll(S)。
    // __builtin_ctz(S)：返回 S 二进制末尾 0 的个数（即最低位的 1 在第几位，可以直接当做数组下标使用）。
    
    // 枚举状态 S 的所有非空子集 sub
    for (int sub = S; sub; sub = (sub - 1) & S) {
        // sub 就是 S 的合法子集
        int remain = S ^ sub; // remain 是 S 中去除 sub 后的剩余集合
        
        // 状态转移，例如：
        // dp[S] = min(dp[S], dp[sub] + dp[remain]);
        
    }

     


    for(int i=0 ;i<n; i++){
        for(int j=0;j<n; j++){
            cout<<out[i][j]<<" ";
        }
        cout<<endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
   
        solve();
    
    return 0;
}