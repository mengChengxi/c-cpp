#include <bits/stdc++.h>
using namespace std;

inline int get_msb(int x) {
    return x == 0 ? -1 : 31 - __builtin_clz(x);
}

void solve() {
    int n, k;
    cin >> n >> k;
        int V = k ^ n;
    
    vector<int> f(n, 0);
    f[n - 1] = n;
    
    if(V<=n-1) {
        if(n>=2)f[n - 2] = V;
    } else {
        int msb_V=get_msb(V);
        int msb_N=get_msb(n - 1);
         if (msb_V>msb_N) {
            cout << "NO\n";
            return;
        }
        
        f[n-2] = n - 1;
        f[n-3] = V ^ (n - 1);
    }
    
    cout << "YES\n";
    vector<int> p(n, -1);
    vector<bool> used(n, false);
    int prev_f = 0;
    
    for(int i=0; i<n; i++) {
        if (f[i] > prev_f) {
            p[i] = prev_f;
            used[prev_f] = true;
            prev_f = f[i];
        }
    }
    
    int ptr = 0;
    for (int i=0; i<n; i++) {
        if (p[i] == -1) {
            while (used[ptr]) ptr++;
            p[i] = ptr;
            used[ptr] = true;
        }
    }
    
    for (int i=0; i<n; i++) {
        cout << p[i] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}