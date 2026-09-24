#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair
// 注意根据题目要求修改 MOD
const int MOD = 1e9 + 7;

struct Matrix {
    int n;
    vector<vector<long long>> mat;
    
    Matrix(int n) : n(n), mat(n, vector<long long>(n, 0)) {}
    
    Matrix operator*(const Matrix& other) const {
        Matrix res(n);
        for (int i = 0; i < n; ++i) {
            for (int k = 0; k < n; ++k) {
                if (mat[i][k] == 0) continue;
                for (int j = 0; j < n; ++j) {
                    res.mat[i][j] = (res.mat[i][j] + mat[i][k] * other.mat[k][j]) % MOD;
                }
            }
        }
        return res;
    }
};

Matrix power(Matrix a, long long b) {
    Matrix res(a.n);
    for (int i = 0; i < a.n; ++i) res.mat[i][i] = 1;
    while (b > 0) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

void sample() {
    // 1. 设定矩阵维度
    int n = 2;
    Matrix A(n);
    
    // 2. 构造状态转移矩阵
    A.mat = {
        {1, 1},
        {1, 0}
    };
    
    // 3. 执行快速幂计算
    long long k = 10;
    Matrix ans = power(A, k);
    
    // 4. 获取结果 (例如 ans.mat[0][0])
    
}

void solve() {
    int m,n;
    cin>>m>>n;


    vector<int> s(m);
    vector<int> l(m);
    for(int i=0; i<m; i++){
        cin>>s[i];
    }
    for(int i=0; i<m; i++){
        cin>>l[i];
    }


    Matrix A(m);
    

    for(int i=0; i<m; i++){
        for(int j=0; j<m ;j++){

            //j-->i
            long long routs=(s[j]*s[i]%mod+l[j]*s[i]%mod+s[j]*l[i]%mod)%mod;
            A.mat[i][j]=routs;
        }
    }
    
    // 3. 执行快速幂计算
    long long k = n;
    Matrix ans = power(A, n);

    long long res=0;

    for(int i=0; i<m; i++){
        res=(res+ans.mat[i][0])%mod;
    }

    cout<<res<<endl;
    

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


        solve();
    
    return 0;
}



