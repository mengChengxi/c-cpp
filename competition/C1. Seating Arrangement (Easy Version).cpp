#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n, table,seats;
    cin>>n>>table>>seats;

    string people;
    cin>>people;

    long long reserves=0;
    long long reservestable=0;
    long long SpareAnumber=0;
    

    long long count=0;
    //seat>1
    for(int i=0; i<n; i++){
        if(people[i]=='I'){
            if(reservestable<table){
                reserves+=(seats-1);
                reservestable++;
                count++;
            }else{

            }
        }else if(people[i]=='E'){
            if(reserves>0){
                reserves--;
                count++;
            }else{
                if(reservestable==table){

                }else{
                    if(SpareAnumber>0){
                        reservestable++;
                        reserves+=(seats-1);
                        SpareAnumber--;
                        count+=1;
                    }
                }
            }
        }else if(people[i]=='A'){
            if(reserves>0){
                reserves--;
                count++;
                SpareAnumber++;
            }else{
                if(reservestable==table){

                }else{
                    reservestable++;
                    reserves+=(seats-1);
                    count+=1;
                }
            }
            
        }

        
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