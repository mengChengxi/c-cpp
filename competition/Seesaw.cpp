#include <algorithm>
#include <bits/stdc++.h>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

struct node{
    double wieght;
    int id;
    int pos;
    int left;
    int right;
    int leftid;
    int righid;
    
    int people;
    

    
};

void solve() {
    int n;
    cin>>n;

    vector<pair<int,int>> poses(n);

    long long torque=0;
    for(int i=0; i<n; i++){
        int pos, w;
        cin>>pos>>w;
        poses[i]={pos,w};
        torque+=(pos*w);
    }

    if(n==1){
        //todo
    }

    sort(poses.begin(),poses.end());

    vector<node> nodes(n);
    nodes[0]={(double)poses[0].second,0,poses[0].first,INF,poses[1].first-poses[0].first,-1,1, 1};
    nodes[n-1]={(double)poses[n-1].second,n-1,poses[n-1].first,poses[n-1].first-poses[n-2].first,INF,n-2,-1, 1};

    for(int i=1; i<n-1; i++){
        nodes[i]={(double)poses[i].second,i,poses[i].first,poses[i].first-poses[i-1].first,poses[i+1].first-poses[i].first,i-1,i+1,1};
    }

    unordered_set< int> valids;

    priority_queue<node> pq;

    for(int i=0; i<n; i++){
        pq.push(nodes[i]);
        valids.insert(i);
    }
    int maxid=n;

    double dis=0;
    while(torque!=0){

        while(valids.count(pq.top().id)==0){
            pq.pop();
        }

        node current=nodes[pq.top().id];
        pq.pop();
        if(torque>0){
            //left

            if(current.wieght*current.left<torque){
                current.wieght=((double)nodes[current.leftid].wieght*nodes[current.leftid].people+current.wieght*current.people)/((double)nodes[current.leftid].people+current.people);

                current.people+=nodes[current.leftid].people;

                torque-=current.wieght*current.people*current.left;
                dis+=current.people*current.left;

                current.leftid=nodes[current.leftid].leftid;
                current.left=nodes[current.leftid].left;
                pq.push(current);
                valids.erase(nodes[current.leftid].id);
                
            }else{
                dis+=(torque/(current.wieght*current.people));
                break;
            }
        }
    }

    


    
   
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
        solve();
    
    return 0;
}