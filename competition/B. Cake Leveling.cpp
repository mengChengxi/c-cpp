#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;
    cin>>n;
    vector<int> cakes(n);
    for(int i=0; i<n; i++){
        cin>>cakes[i];
    }

    long long  maxheight=cakes[0];
    long long residue=0;

    cout<<maxheight<<" ";
    for(int i=1; i<n; i++){
        if(cakes[i]>=maxheight){
            residue+=cakes[i]-maxheight;
        }else{
            if(maxheight-cakes[i]<=residue){
                residue-=(maxheight-cakes[i]);
            }else{
                if((maxheight-cakes[i]-residue)%(i+1)==0){
                    int newh=maxheight-(((maxheight-cakes[i]-residue)/(i+1)));
                    int nres=0;
                    maxheight=newh;
                    residue=nres;
                }else{
                    int newh=maxheight-(((maxheight-cakes[i]-residue)/(i+1))+1);
                    int nres=(((maxheight-cakes[i]-residue)/(i+1))+1)*i+residue-(newh-cakes[i]);
                    maxheight=newh;
                    residue=nres;
                }
            }
        }


        cout<<maxheight<<" ";
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