#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n, q;
    cin>>n>>q;

    string a;
    string b;
    cin>>a;
    cin>>b;

    vector<int> pre11(n);
    vector<int> pre10(n);
    vector<int> pre01(n);
    vector<int> pre00(n);

    pre00[0]=0;
    pre01[0]=0;
    pre10[0]=0;
    pre11[0]=0;

    if(a[0]=='0'&&b[0]=='0'){
        pre00[0]++;
    }
    if(a[0]=='1'&&b[0]=='0'){
        pre10[0]++;
    }
    if(a[0]=='0'&&b[0]=='1'){
        pre01[0]++;
    }
    if(a[0]=='1'&&b[0]=='1'){
        pre11[0]++;
    }

    

    for(int i=1; i<n; i++){
        pre01[i]=pre01[i-1];
        pre00[i]=pre00[i-1];
        pre10[i]=pre10[i-1];
        pre11[i]=pre11[i-1];
        if(a[i]=='0'&&b[i]=='0'){
            pre00[i]++;
        }
        if(a[i]=='1'&&b[i]=='0'){
            pre10[i]++;
        }
        if(a[i]=='0'&&b[i]=='1'){
            pre01[i]++;
        }
        if(a[i]=='1'&&b[i]=='1'){
            pre11[i]++;
        }
    }

    while (q--) {
        int l,r;
        cin>>l>>r;

        int t00,t01,t10,t11;

        if(l==1){
            r--;
            t00=pre00[r];
            t01=pre01[r];
            t10=pre10[r];
            t11=pre11[r];
        }else{
            r--;

            l-=2;

            t00=pre00[r]-pre00[l];
            t01=pre01[r]-pre01[l];
            t10=pre10[r]-pre10[l];
            t11=pre11[r]-pre11[l];
        }

        if(t00+t11>=abs(t01-t10)){
            cout<<"YES"<<endl;
        }else{
             cout<<"NO"<<endl;
        }


    }


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


multiset<long long> ms;
