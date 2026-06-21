#include <bits/stdc++.h>
#include <iostream>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;
    cin>>n;
    string s;
    cin>>s;

    long long count=0;

    int s1e1=0;
    int s1e0=0;
    int s0e1=0;
    int s0e0=0;
    int u11=0;
    int u00=0;
    int u10=0;
    int u01=0;
    


    for(int i=0; i<n; i++){
        count++;

        if(s[i]=='0'){
            count+=s1e0+s0e0;
        }else{
            count+=s1e1+s0e1;
        }

        if(s[i]=='0'){

            int news1e0=s1e1;
            int news1e1=s0e0;
            int news0e0=s1e0+s0e1+1;
            int news0e1=0;
            int newu11=0;
            int newu00=u01+1;
            int newu10=u11;
            int newu01=0;

            s1e0=news1e0;
            s1e1=news1e1;
            s0e0=news0e0;
            s0e1=news0e1;
            u00=newu00;
            u11=newu11;
            u10=newu10;
            u01=newu01;


        
        }else{

            int news1e0=0;
            int news1e1=s1e0+s0e1+1;
            int news0e0=s1e1;
            int news0e1=s0e0;
            int newu11=u10+1;
            int newu00=0;
            int newu10=0;
            int newu01=u00;


            s1e0=news1e0;
            s1e1=news1e1;
            s0e0=news0e0;
            s0e1=news0e1;
            u00=newu00;
            u11=newu11;
        }

        count+=(s1e1-u11);
        count+=(s0e0-u00);

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