#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 1e9 + 7;
#define mkp make_pair

long long subs(long long left, long long right, long long leftlimit, long long rightlimit, long long n){
    
    long long extend=2*n-(right-left+1);
    if (extend < 0) return 0;
    long long minmargin=min(left-leftlimit-1,rightlimit-right-1);
    long long maxmargin=max(left-leftlimit-1,rightlimit-right-1);
    if(left-leftlimit-1+rightlimit-right-1<extend){
        return (left-leftlimit)*(rightlimit-right);
    }else if(maxmargin<extend){
        int dif=((rightlimit-leftlimit-1)-2*n);
        return (left-leftlimit)*(rightlimit-right)-(1+dif)*dif/2;
    }else if(minmargin<extend){
        return (1+(minmargin+1))*(minmargin+1)/2+(minmargin+1)*(extend-minmargin);
    }else{
        return (1+(extend+1))*(extend+1)/2;
    }

}

void solve() {

    //cout<<subs(2,3,-100,5,3)<<endl;
    int n;
    cin>>n;
    
    vector<int> nums(n);
    for(int i=0; i<n; i++){
        cin>>nums[i];
    }

    vector<int> pos(n);

    for(int i=0; i<n; i++){
        pos[nums[i]]=i;
    }

    long long count=0;

    int left=INF;
    int right=-INF;
    for(int i=0; i<n-1; i++){
        left=min(left,pos[i]);
        right=max(right,pos[i]);
        if(pos[i+1]<=right&&pos[i+1]>=left){
            continue;
        }
        if(pos[i+1]>right){
            count+=subs(left, right, -1, pos[i+1], i+1);
        }
        if(pos[i+1]<left){
            count+=subs(left, right, pos[i+1], n, i+1);
        }

    }

    cout<<count+1<<endl;


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