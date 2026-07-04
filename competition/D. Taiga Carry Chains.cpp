#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n,k;
    cin>>n>>k;

    if(k==0){
        cout<<0<<endl;
        return;
    }

    k--;
    vector<int> num(66,0);

    for(int i=0; i<32; i++){
        if((n>>i)%2==1){
            num[i]=1;
        }else{
            num[i]=0;
        }
    }

    int resk=0;

    if(k>32){
        resk=k-32;
        k=32;
    }

    

    int start=0;//exclude
    int end=0;//include

    while(num[start]!=0){
        start++;
    }

    deque<int> puts;

    for(int i=0; i<k; i++){
        while(num[start]!=0){
            start++;
        }
        puts.push_back(start);
        start++;
    }

    int maxl=start-end;

    while(start!=65){
        while(num[start]!=0){
            start++;
        }
        maxl=max(maxl,start-end);
        puts.push_back(start);
        start++;
        end=puts[0]+1;
        puts.pop_front();

        maxl=max(maxl,start-end);
    }

    cout<<maxl+resk<<endl;



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