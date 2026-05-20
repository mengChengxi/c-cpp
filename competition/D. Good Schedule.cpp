#include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;
    cin>>n;
    vector<int> a(n);
    vector<int> b(n);
    for(int i=0; i<n; i++){
        cin>>a[i];
    }
    for(int i=0; i<n; i++){
        cin>>b[i];
    }

    long long count=0;

    vector<int> last(n+3,0);
    int sum=0;
    for(int i=0; i<n; i++){
        if(a[i]==b[i]){
            
            
            
            last[0]++;
            sum++;
            count+=sum;
            last[a[i]]+=last[a[i]-1];
            last[a[i]-1]=0;

        }else{
            
            sum-=last[a[i]-1];
            last[a[i]-1]=0;
            
            sum-=last[b[i]-1];
            last[b[i]-1]=0;

            if(a[i]!=1&&b[i]!=1){
                last[0]++;
                sum++;
            }
            

            count+=sum;
            

        }
    }

    cout<<count<<endl;
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