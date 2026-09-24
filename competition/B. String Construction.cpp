#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n,k;

   
    cin>>n>>k;

    int on=n;
    vector<int> out;
    int p1=k/2;
    int p2=k-p1;

    if(p1!=0){
        p1++;
    }
    if(p2!=0){
        p2++;//big
    }
   

    n=n-p1-p2;

    if(p1==0){
        if(p2==0){
            for(int i=0; i<on; i++){
                out.push_back(1-(i%2));
            }

        }else{
            out.push_back(1);
            out.push_back(0);
            out.push_back(0);
            for(int i=0; i<on-3; i++){
                out.push_back(1-(i%2));
            }
        }
        
    }else{

        for(int i=0; i<n; i++){
            out.push_back(i%2);
        }

        int big=0;
        if(out.size()!=0){
            big=1-out[out.size()-1];
        }

        for(int i=0; i<p2; i++){
            out.push_back(big);
        }
        for(int i=0; i<p1; i++){
            out.push_back(1-big);
        }
    }


    if(out.size()>on){
        cout<<-1<<endl;
        return;
    }
    for(int i=0 ; i<out.size(); i++){
        cout<<out[i];
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