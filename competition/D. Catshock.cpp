#include <bits/stdc++.h>
#include <random>
#include <utility>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

vector<vector<int>> tree;
vector<int> oe;
//even=0 odd=1
int timecatmoves=0;
int target=0;
vector<pair<int , int>> operation;

void eodfs(int n, int parent, int oddandeven){

    oe[n]=oddandeven;
    for(int i=0; i<tree[n].size(); i++){
        if(tree[n][i]!=parent){
            eodfs(tree[n][i],n,1-oddandeven);
        }
    }

}

void dfs(int n, int parent ){
    
    for(int i=0; i<tree[n].size(); i++){
        if(tree[n][i]!=parent){
            dfs(tree[n][i],n);
        }
    }

    if(n==target){
        return;
    }
    operation.push_back({1,0});
    timecatmoves++;

    if(timecatmoves%2==oe[n]){
        operation.push_back({1,0});
        timecatmoves++;
    }
    operation.push_back({2,n});


}
void solve() {
    operation.clear();
    int n;
    cin>>n;

    target=n;
    vector<vector<int>> ttree(n+1,vector<int>());
    tree=ttree;
    vector<int> toe(n+1);
    oe=toe;

    for(int i=0; i<n-1; i++){
        int f,t;
        cin>>f;
        cin>>t;

        tree[f].push_back(t);
        tree[t].push_back(f);
    }

    eodfs(1, 0, 0);
    timecatmoves=0;

    dfs(n,0);

    cout<<operation.size()<<endl;
    for(int i=0; i<operation.size();i++){
        if(operation[i].first==1){
            cout<<"1\n";
        }else{
            cout<<"2 "<<operation[i].second<<"\n";
        }
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