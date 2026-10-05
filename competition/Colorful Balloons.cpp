#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;
    cin>>n;
    vector<string> color(n);
    for(int i=0; i<n; i++){
        cin>>color[i];
    }
    string champing;
    int score=0;
    for(int i=0; i<n; i++){
        if(score==0){
            champing=color[i];
            score++;
        }else{
            if(champing==color[i]){
                score++;
            }else{
                score--;
            }
        }
        
    }
    int count=0;
    for(int i=0; i<n; i++){
        
        if(champing==color[i]){
            count++;
        }
                
    }

    if(count>((double)n)/2){
        cout<<champing<<endl;
    }else{
        cout<<"uh-oh"<<endl;
    }

    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    solve();
    
    return 0;
}