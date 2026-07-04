#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;
    cin>>n;
    string s;
    cin>>s;

    vector<int> axis(2*n+4,0);
    long long count=0;

    long long total=0;

    int move0=0;
    int move1=0;
    int center=n+1;
    for(int i=0; i<n; i++){
        if(s[i]=='0'){
            
            total+=(move0+axis[center]);
            move0+=axis[center];
            move1-=axis[center];
            
            //total1-=move1;

            center++;

            total++;
            move0++;
            axis[center-1]++;
            count+=total;

        }else{

            total+=move1;
            move1+=axis[center-1];
            move0-=axis[center-1];
            
            //total0-=move0;

            center--;

            total++;
            move1++;
            axis[center+1]++;
            count+=total;
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

