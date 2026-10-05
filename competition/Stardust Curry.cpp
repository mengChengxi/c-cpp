#include <bits/stdc++.h>
#include <iomanip>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n,p;
    cin>>n>>p;

    vector<int> breaks(n);

    long long sumbreak=0;

    for(int i=0; i<n; i++){
        cin>>breaks[i];
        sumbreak+=breaks[i];
    }
    double stress=0;
    for(int i=0; i<n; i++){
        stress+=((double)breaks[i]/sumbreak*p)*((double)breaks[i]/sumbreak*p)/(double)breaks[i];
    }

    cout<<fixed<<setprecision(7)<<stress<<endl;

    


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