#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair
struct Element{
    int l,r,u,v;
};
void solve() {
    int n;
    cin>>n;


    vector<Element> a(n);
    
    for(int i=0; i<n; i++){
        cin>>a[i].l>>a[i].r>>a[i].u>>a[i].v;
    }
    for(int m=n; m>=1; --m){
        int current_idx =0;

        bool possible=true;


        for(int j=1; j<=m; ++j){
            bool found=false;
            while(current_idx<n){
                bool cond1=(j<a[current_idx].l||j>a[current_idx].r);
                bool cond2=((m-j+1)<a[current_idx].u||(m-j+1)>a[current_idx].v);
                if(cond1&&cond2){
                    found=true;
                    current_idx++;
                    break;
                }
                current_idx++;
            }

            if(!found){
                possible=false;
                break;
            }
        }
        
        if(possible){
            cout<<m<<endl;
            return;
        }
    }
    cout<<0<<endl;
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