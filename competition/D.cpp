#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;
    cin>>n;
    vector<int> degree(n+3,0);

    vector<int> tree(n+3,0);
    for(int i=0; i<n-1; i++){
        cin>>tree[i+2];
    }
    
    int first=0;
    int second=0;

    int f=-1;
    for(int i=0; i<n-1; i++){
        degree[tree[i+2]]++;
        degree[i+2]++;


        int newfirst=0;
        int newsecond=0;

        if(first==tree[i+2]){
            newfirst=first;
            if(degree[i+2]>degree[second]){
                newsecond=i+2;
            }else{
                newsecond=second;
            }
        }else if(second==tree[i+2]){
            if(degree[second]>degree[first]){
                newsecond=first;
                newfirst=second;
            }else{
                newfirst=first;
                newsecond=second;
            }

        }else if(degree[tree[i+2]]>degree[first]){
            newfirst=tree[i+2];

            if(degree[first]<degree[i+2]){
                newsecond=i+2;
            }else{
                newsecond=first;
            }
            
        }else if(degree[tree[i+2]]==degree[first]){
            if(degree[second]==degree[first]){
                if(f==1){
                    newfirst=first;
                    newsecond=tree[i+2];
                }else{
                    newfirst=first;
                    newsecond=second;
                }
            }else{
                newfirst=first;
                newsecond=tree[i+2];
            }
            
        }else{
            newfirst=first;
            if(degree[tree[i+2]]>degree[second]){
                newsecond=tree[i+2];
            }else if(degree[tree[i+2]]==degree[second]){
                if(f==1){
                    newsecond=tree[i+2];
                }else{
                    newsecond=second;
                }
            }else{
                newsecond=second;
            }

        }

        if(tree[newsecond]==newfirst||tree[newfirst]==newsecond){
            f=1;
        }else{
            f=0;
        }

        first=newfirst;
        second=newsecond;

        cout<<degree[first]+degree[second]-1-f<<" ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}