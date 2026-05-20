#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

long long health_needed(int d, int rest){
    long long intervals=rest+1;
    long long longer = d%intervals;
    long long shorter = intervals-longer;
    long long sl=d/intervals;
    long long ll=sl+1;
    return shorter*((1+sl)*sl/2)+longer*((1+ll)*ll/2);
}

void solve() {
    int h,d;
    cin>>h>>d;

    int left=-1;
    int right=d+1;//[)


    while(left<right-1){
        int mid=(left+right)/2;
        if(health_needed(d,mid)<mid+h){
            right=mid;
        }else{
            left=mid;
        }
    }

    cout<<d+right<<endl;

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