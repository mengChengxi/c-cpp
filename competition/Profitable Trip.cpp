#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

int w;
const long long LLINF = 1e18;

struct Edge {
    int u, v;
    long long w;
};

pair<vector<long long>, bool> bellman_ford(int n, int start, const vector<Edge>& edges) {
    vector<long long> dist(n + 1, LLINF);
    dist[start] = 0;

    for (int i = 1; i <= w*n ; i++) {
        bool any_update = false;
        for (const auto& e : edges) {
            if (dist[e.u] < LLINF && dist[e.u] + e.w < dist[e.v]) {
                if(dist[e.v]==LLINF){
                    dist[e.v] = dist[e.u] + e.w;
                }else {
                    int step=dist[e.u] + e.w-dist[e.v];
                    dist[e.v]=-w+(dist[e.v]+w)%step;
                }
                if(dist[e.v] < -w){
                    dist[e.v]=-w;
                }
                any_update = true;
            }
        }
        //if (!any_update) break;
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

void solve() {
    
    int n,m;
    cin>>n>>m>>w;

    vector<Edge> edges;

    for(int i=0; i<m; i++){
        int u,v,t;
        cin>>u>>v>>t;
        edges.push_back({u,v,-t});

    }

    vector<long long> dis=bellman_ford(n,1,edges).first;

    cout<<-dis[n]<<endl;


}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

        solve();
    
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

