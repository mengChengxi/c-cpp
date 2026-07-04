// #include <iostream>
// #include <vector>
// #include <cstring>
// #include <iomanip>

// using namespace std;

// // 打表范围，通常找规律 500 - 1000 就足够暴露所有的周期或位运算特征了
// int MAXN = 1; 
// vector<int> memo;
// vector<int> action;


// // 核心记忆化搜索函数
// int get_sg(int x) {
//     // ==========================================
//     // 【修改区 1：定义终局状态】
//     // ==========================================
//     if (x == 0) return 0; // 例：没有石子时为必败态
    
//     // 记忆化查表
//     if (memo[x] != -1) return memo[x];

//     vector<int> next_sgs;

//     // ==========================================
//     // 【修改区 2：状态转移规则 (游戏的核心逻辑)】
//     // ==========================================
//     // 假设规则：可以拿走 1 个，或者平分剩下的石子（如果 x 是偶数）

//     for(int i=0; i<action.size(); i++)
//     {
//         if(x-action[i]>=0){
//             next_sgs.push_back(get_sg(x-action[i]));
//         }
//     }
//     // ==========================================
//     // 【恒定区：极速 MEX 运算 (千万别改)】
//     // 根据鸽巢原理，如果有 K 个后继状态，mex 绝不会超过 K
//     // ==========================================
//     int k = next_sgs.size();
//     vector<bool> vis(k + 1, false); 
//     for (int v : next_sgs) {
//         if (v <= k) vis[v] = true;
//     }

//     for (int i = 0; ; i++) {
//         if (!vis[i]) return memo[x] = i;
//     }
// }


// void solve() {

//     int n,k;
//     cin>>n>>k;
//     MAXN=n;
//     vector<int> tmemo(n+3,-1);

//     memo=tmemo;
//     vector<int> taction(k);

//     action=taction;
//     for(int i=0; i<k; i++){
//         cin>>action[i];
//     }

//     for(int i=1; i<n+1; i++){
//         if(get_sg(i)==0){
//             cout<<'L';
//         }else{
//             cout<<'W';
//         }
//     }
    
// }

// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
  

//         solve();
    
//     return 0;
// }

// #include <iostream>
// #include <vector>
// #include <cstring>
// #include <iomanip>

// using namespace std;

// // 打表范围，通常找规律 500 - 1000 就足够暴露所有的周期或位运算特征了
// const int MAXN = 1005; 
// int memo[MAXN];

// // 核心记忆化搜索函数
// int get_sg(int x) {
//     // ==========================================
//     // 【修改区 1：定义终局状态】
//     // ==========================================
//     if (x == 0) return 0; // 例：没有石子时为必败态
    
//     // 记忆化查表
//     if (memo[x] != -1) return memo[x];

//     vector<int> next_sgs;

//     // ==========================================
//     // 【修改区 2：状态转移规则 (游戏的核心逻辑)】
//     // ==========================================
//     // 假设规则：可以拿走 1 个，或者平分剩下的石子（如果 x 是偶数）
//     next_sgs.push_back(get_sg(x - 1));
//     if (x % 2 == 0) {
//         next_sgs.push_back(get_sg(x / 2));
//     }

//     // ==========================================
//     // 【恒定区：极速 MEX 运算 (千万别改)】
//     // 根据鸽巢原理，如果有 K 个后继状态，mex 绝不会超过 K
//     // ==========================================
//     int k = next_sgs.size();
//     vector<bool> vis(k + 1, false); 
//     for (int v : next_sgs) {
//         if (v <= k) vis[v] = true;
//     }

//     for (int i = 0; ; i++) {
//         if (!vis[i]) return memo[x] = i;
//     }
// }

// int main() {
//     // 初始化记忆化数组
//     memset(memo, -1, sizeof(memo));

//     int limit = 50; // 你想要观察的前 N 项

//     // 格式化输出，极度对齐，方便肉眼快速捕捉循环节
//     cout << "  x  | SG(x)\n";
//     cout << "-----+------\n";
//     for (int i = 0; i <= limit; i++) {
//         cout << setw(4) << i << " | " << setw(3) << get_sg(i) << "\n";
        
//         // 进阶排版技巧：每 10 行空一行，或者发现疑似周期时强制换行
//         if ((i + 1) % 10 == 0) cout << "-----+------\n"; 
//     }

//     return 0;
// }