#include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n,k;
    cin>>n>>k;

    vector<vector<int>> rank(k,vector<int>(n));

    for(int i=0;i<k; i++){
        for(int j=0; j<n; j++){
            cin>>rank[i][j];
        }
    }

    if(k==1){
        cout<<"YES"<<endl;
        return;
    }

    vector<int> temp(n);//true n-1

    int t1=rank[0][0];
    for(int i=1; i<n; i++){
        temp[i-1]=rank[0][i];
    }
    for(int i=1; i<n; i++){
        if(rank[1][i]==t1){
            if(i==1){
                if(temp[0]!=rank[1][0]){
                    temp.insert(temp.begin(),t1);
                }else{
                    if(k==2){
                        temp.insert(temp.begin(),t1);
                    }else{
                        for(int k=1; k<n; k++){
                            if(rank[2][k]==t1){
                                temp.insert(temp.begin(),t1);
                                break;
                            }else if(rank[2][k]==rank[1][0]){
                                temp.insert(temp.begin()+1,t1);
                                break;
                            }
                        }
                    }
                }
                //start
            }else{
                for(int j=0; j<temp.size(); j++){
                    if(temp[j]==rank[1][i-1]){
                        if(temp[j+1]!=rank[1][0]){
                            temp.insert(temp.begin()+j+1,t1);
                        }else{
                            // conflict
                            if(k==2){
                                temp.insert(temp.begin()+j+1,t1);
                            }else{
                                for(int k=1; k<n; k++){
                                    if(rank[2][k]==t1){
                                        temp.insert(temp.begin()+j+1,t1);
                                        break;
                                    }else if(rank[2][k]==rank[1][0]){
                                        temp.insert(temp.begin()+j+2,t1);
                                        break;
                                    }
                                }
                            }
                            
                        }
                    }
                }
                
            }
        }
    }

    for(int i=0; i<k; i++){
        int read=1;
        for(int j=0; j<n; j++){
            if(temp[j]==rank[i][0]){
                continue;
            }else{
                if(temp[j]==rank[i][read]){
                    read++;
                }else{
                    cout<<"NO"<<endl;
                    return;
                }
            }
        }
    }

    cout<<"YES"<<endl;

    

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