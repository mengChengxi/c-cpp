#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair
struct Node {
    int next[26];
    bool is_end;
    int number_under;
    Node() {
        for (int i = 0; i < 26; ++i) {
            next[i] = 0;
        }
        is_end = false;
        number_under=0;
    }
};

// 初始化或重置指定的字典树（在使用任何新建的字典树前必须调用）
void init(vector<Node>& trie) {
    trie.clear();
    trie.emplace_back(); // 下标 0 作为根节点
}

void insert(vector<Node>& trie, const string& word) {
    int p = 0;
    for (char c : word) {
        int u = c - 'a';
        if (trie[p].next[u] == 0) {
            trie[p].next[u] = trie.size();
            trie.emplace_back();
        }
        
        p = trie[p].next[u];
    }
    trie[p].is_end = true;
}

int search(const vector<Node>& trie, const string& word) {
    if (trie.empty()) return false; // 边界保护
    int p = 0;
    for (char c : word) {
        int u = c - 'a';
        if (trie[p].next[u] == 0) {
            return 0;
        }
        p = trie[p].next[u];
    }
    return trie[p].number_under;
}

bool startsWith(const vector<Node>& trie, const string& prefix) {
    if (trie.empty()) return false; // 边界保护
    int p = 0;
    for (char c : prefix) {
        int u = c - 'a';
        if (trie[p].next[u] == 0) {
            return false;
        }
        p = trie[p].next[u];
    }
    return true;
}


vector<Node> front;
vector<Node> eend;
vector<Node> mid;



int dfs(vector<Node>& trie,int curr){
    int sum=0;
    if(trie[curr].is_end==true){
        sum++; 
    }
    for(int i=0; i<26 ; i++){
        if(trie[curr].next[i]!=0){
            sum+=dfs(trie,trie[curr].next[i]);
        }
    }
    trie[curr].number_under=sum;
    return sum;
}

void solve() {
    int n,q;
    cin>>n>>q;

    
    init(front);   init(eend);   init(mid);



    for(int i=0; i<n; i++){
        string s;
        cin>>s;

        
            
        string rs;
        for(int i=s.size()-1; i>=0; i--){
            rs.push_back(s[i]);
        }

        string ms;

        for(int i=0; i<s.size(); i++){
            ms.push_back(s[i]);
            ms.push_back(s[s.size()-1-i]);
        }

        insert(front, s);
        insert(eend, rs);
        insert(mid, ms);
    

        
    }

    dfs(front,0);
    dfs(eend,0);
    dfs(mid,0);

    for(int i=0; i<q; i++){
        string type,p,s;
        cin>>type>>p>>s;

        string rs;
        for(int i=s.size()-1; i>=0; i--){
            rs.push_back(s[i]);
        }

        string ms;

        for(int i=0; i<s.size(); i++){
            ms.push_back(p[i]);
            ms.push_back(s[s.size()-1-i]);
        }


        int allp=search(front,p);
        int alls=search(eend,rs);

        int overlap=search(mid,ms);

        if(type=="OR"){
            cout<<allp+alls-overlap<<endl;
        }else if(type=="AND"){
            cout<<overlap<<endl;
        }else{
            cout<<allp+alls-overlap-overlap<<endl;
        }


    }

    
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