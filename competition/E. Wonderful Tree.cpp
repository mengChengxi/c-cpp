#include <bits/stdc++.h>
#include <deque>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

vector<vector<int>> tree;
vector<long long> val;
vector<int> parent;
long long ans=0;

void pushto(int des, int from, long long sum){
    if(from == des) return; // 到了目标节点直接停止，不要修改它
    ans += sum;
    val[from] += sum;
    pushto(des, parent[from], sum);
}
void dfs(int node, int p){
    for(int i=0; i<tree[node].size(); i++){
        if(tree[node][i]==p){
            continue;
        }
        dfs(tree[node][i],node);
    }

    long long need=0;
    for(int i=0; i<tree[node].size(); i++){
        need+=val[tree[node][i]]; // 加上节点的权值 val
    }

    if(val[node]<=need){
        return;
    }
    need=val[node]-need;
    

    deque<int> que;
    int level=1;

    que.push_back(node);
    

    while(que.size()!=0){
        int current=que[0];
        que.pop_front();

        long long childremsum=0;
        if(tree[current].size()==0){
            pushto(node,current,need); // 先把现有的 need 传过去
            need=0;                    // 然后再清零并 return
            return;
        }
        for(int i=0; i<tree[current].size(); i++){
            childremsum+=val[tree[current][i]];
            que.push_back(tree[current][i]);
        }

        if(childremsum-val[current]>0){

            if(childremsum-val[current]<=need){
                need-=(childremsum-val[current]);
                pushto(node,current,(childremsum-val[current]));
            }else{
                pushto(node,current,need); // 只需要补足最后的 need 即可
                need=0;
                return;
            }
        }

        
    }
}

void solve() {
    int n;
    cin>>n;
    ans=0;

    vector<long long> tval(n+1,0);

    val=tval;
    for(int i=0; i<n; i++){
        cin>>val[i+1];
    }

    vector<vector<int>> ttree(n+1);

    vector<int> tparent(n+1,0);
    tree=ttree;
    parent=tparent;
    for(int i=2; i<=n; i++){
        int to;
        cin>>to;

        parent[i]=to;

        tree[to].push_back(i);
        //tree[i].push_back(to);
    }

    dfs(1,0);

    cout<<ans<<endl;


    
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