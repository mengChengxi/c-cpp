#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;
    cin>>n;
    vector<int> h(n);
    for(int i=0; i<n; i++){
        cin>>h[i];
    }

    int maxn=-1;
    int maxi=-1;
    for(int i=0; i<n; i++){
        if(h[i]>maxn){
            maxi=i;
            maxn=h[i];
        }
    }

    for(int i=0; i<n; i++){
        long long leftsum=0;
        int level=0;
        for(int left=i; ; left=(left-1+n)%n){

            if((left-1+n)%n==maxi){
                break;
            }
            //left=h[i]
            //right = h[(left-1+n)%n]
            if(h[(left-1+n)%n]>level){
                leftsum+=h[(left-1+n)%n];
                level=h[(left-1+n)%n];
            }else{
                leftsum+=level;
            }  
            
        }
        long long  rightsum=0;
        level=0;
        for(int right=i; ; right=(right+1)%n){
            if(right==maxi){
                break;
            }
            
            //right = h[(right+1)%n]
            if(h[right]>level){
                rightsum+=h[right];
                level=h[right];
            }else{
                rightsum+=level;
            }  
            
        }

        cout<<leftsum+rightsum<<" ";
    }
    cout<<endl;

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