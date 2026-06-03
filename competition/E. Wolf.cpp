#include <bits/stdc++.h>
#include <iostream>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair


vector<int> sh;
vector<int> in;

int needsmall;
int needbig;

int usedbig;
int usedsmall;
int f(int l,int r,int k){
    if(l>r){
        return 0;
    }
    int m=(l+r)/2;
    if(sh[m]==k){
        return 1;
    }

    if(m<in[k]){
        if(sh[m]<k){
            usedsmall++;
        }else{
            needsmall++;
        }
        return f(m+1,r,k);
    }else if(m>in[k]){
        if(sh[m]>k){
            usedbig++;
        }else{
            needbig++;
        }
        return f(l,m-1,k);
    }
}


void solve() {
    int n,q;
    cin>>n>>q;
    vector<int> tsh(n);
    sh=tsh;
    for(int i=0;i<n; i++){
        cin>>sh[i];
    }
    vector<int> tin(n+1);
    in=tin;
    for(int i=0;i<n; i++){
        in[sh[i]]=i;
    }

    while(q--){
        int l,r,k;
        needbig=0;
        needsmall=0;
        usedbig=0;
        usedsmall=0;
    
        cin>>l>>r>>k;
        l--;
        r--;
        if(f(l,r,k)==0){
            cout<<-1<<" ";
            continue;
        }

        if(needbig==needsmall){
            cout<<needbig+needsmall<<" ";
        }else if(needbig>needsmall){

            if(needbig>n-k-usedbig){
                cout<<-1<<" ";
            }else{
                cout<<needbig*2<<" ";
            }


        }else{
            if(needsmall>=k-usedsmall){
                cout<<-1<<" ";
            }else{
                cout<<needsmall*2<<" ";
            }
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