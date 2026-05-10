#include <bits/stdc++.h>
#include <climits>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    long long n,h;
    cin>>n>>h;
    vector<int> water(n);
    for(int i=0; i<n; i++){
        int tt;
        cin>>tt;

        water[i]=tt;
    }

    vector<int> height(n);
    vector<int> minheight;
    long long minsum=LLONG_MAX;
    for(int i=0; i<n; i++){
        int leftmax=water[i];
        for(int j=i; j>=0; j--){
            leftmax=max(leftmax,water[j]);
            height[j]=leftmax; 
        }
        int rightmax=water[i];
        for(int j=i; j<n; j++){
            rightmax=max(rightmax,water[j]);
            height[j]=rightmax; 
        }
        long long sum=0;
        for(int i=0; i<n; i++){
            sum+=height[i];
        }
        if(sum<minsum){
            minsum=sum;
            minheight=height;
        }

    }


    long long total=n*h-minsum;

    //cout<<total<<endl;
    long long maxswater=0;
    for(int i=0; i<n; i++){
        long long totalwater=-1;
        int leftmax=water[i];
        int farleft=i;
        int farright=i+1;
        for(int j=i; j>=0; j--){
            if(water[j]==minheight[j]){
                break;
            }
            farleft=j;
            leftmax=max(leftmax,water[j]);
            totalwater+=leftmax; 
        }
        if(totalwater==-1){
            continue;
        }  
        totalwater++;
        int rightmax=water[i];
        for(int j=i+1; j<n; j++){
            if(water[j]==minheight[j]){
                break;
            }
            farright=j+1;
            rightmax=max(rightmax,water[j]);
            totalwater+=rightmax; 
        }
        
        
        long long swater=0;
        for(int i=farleft; i<farright; i++){
            swater+=minheight[i];
        }
        swater-=totalwater;
        maxswater=max(maxswater,swater);


    }
    //cout<<maxswater<<endl;

    cout<<total+maxswater<<endl;
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