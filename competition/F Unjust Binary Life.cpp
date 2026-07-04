#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n; 
    cin>>n;
    string up;
    cin>>up;
    string left;
    cin>>left;

    vector<int> dif(4*n+20,0);

    int ones=0;
    int zeros=0;

    int become1=0;
    int become0=0;
    long long change=0;
    for(int i=0; i<n; i++){
        if(left[i]=='0'){
            zeros++;
        }else{
            ones++;
        }

        change+=min(ones,zeros);
        
        if(zeros-ones>0){
            become0+=1;
        }else{
            become1+=1;
        }
        
        dif[zeros-ones+n+2]++;
    }

    //right 0more become1;
    //center will become 1;
    int center=n+2;

    long long count=0;
    for(int i=0; i<n; i++){
        if(up[i]=='0'){
            change+=(become1-dif[center]);
            become1-=dif[center];
            become0+=dif[center];
            center--;
        }else{
            change+=become0;
            become0-=dif[center+1];
            become1+=dif[center+1];
            center++;
            

        }
        count+=change;
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