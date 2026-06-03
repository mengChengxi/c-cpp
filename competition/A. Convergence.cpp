#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

void solve() {
    int n;
    cin>>n;
    vector<int> people(n);
    for(int i=0; i<n; i++){
        cin>>people[i];
    }

    sort(people.begin(),people.end());
    int mid=0;
    if(n%2==1){
        mid=n/2;
    

        int count=0;
        for(int i=1; i<=mid; i++){
            if(people[mid+i]!=people[mid-i]){
                break;
            }
            count++;
        }
        cout<<n/2-count<<endl;
        return;
    }else{
        int mid1=n/2;
        int mid2=n/2-1;
        int count=0;
        for(int i=0;i <=mid2; i++){
            if(people[mid1+i]!=people[mid2-i]){
                break;
            }
            count++;
        }
        cout<<n/2-count<<endl;
        return;
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